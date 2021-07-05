/* See LICENSE file for copyright and license details. */
#include <poll.h>
#include <sys/time.h>

#include <ctype.h>
#include <float.h>
#include <locale.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <wayland-client.h>
#include <wld/wayland.h>
#include <wld/wld.h>
#include <swc.h>
#include <xkbcommon/xkbcommon.h>
#include <linux/input-event-codes.h>

#include "drw.h"
#include "util.h"
#include "swc-client-protocol.h"
#include "input-method-unstable-v2-client-protocol.h"

/* macros */
#define LENGTH(x)		 (sizeof x / sizeof x[0])
#define STRINGTOKEYSYM(X) (XStringToxkb_keysym_t(X))
#define TEXTW(X)		  (drw_fontset_getwidth(drw, (X)))

/* enums */
enum {
	SchemeNorm, SchemeNormABC, SchemeNormABCShift, SchemeNormShift, SchemePress,
	SchemePressShift, SchemeHighlight, SchemeHighlightShift, SchemeOverlay,
	SchemeOverlayShift, SchemeLast
};

/* typedefs */
typedef struct {
	char *label;
	char *label2;
	xkb_keysym_t keysym;
	unsigned int width;
	char *str;
	xkb_keysym_t modifier;
	int x, y, w, h;
	bool pressed;
	bool highlighted;
	bool isoverlay;
} Key;

typedef struct {
	xkb_keysym_t mod;
	unsigned int button;
} Buttonmod;

/* function declarations */
static void printdbg(const char *fmt, ...);
static void cleanup(void);
static void countrows();
static int countkeys(Key *layer);
static void drawkeyboard(void);
static void drawkey(Key *k);
static Key *findkey(int x, int y);
static void press(Key *k);
static double get_press_duration();
static void run(void);
static void setup(void);
static void simulate_keypress(xkb_keysym_t keysym);
static void simulate_keyrelease(xkb_keysym_t keysym);
static void showoverlay(int idx);
static void hideoverlay();
static void cyclelayer();
static void setlayer();
static void togglelayer();
static void unpress(Key *k);
static void updatekeys();
static void printkey(Key *k, xkb_keysym_t mod);

/* variables */
static Drw *drw;
static Clr* scheme[SchemeLast];
static bool running = true, isdock = false;
static struct timeval pressbegin;
static int currentlayer = 0;
static int enableoverlays = 1;
static int currentoverlay = -1; /* -1 = no overlay */
static int pressonrelease = 1;
static xkb_keysym_t overlaykeysym = 0; /* keysym for which the overlay is presented */
static int releaseprotect = 0; /* set to 1 after overlay is shown, protecting against immediate release */
static int tmp_keycode = 1;
static int rows = 0, ww = 0, wh = 0, wx = 0, wy = 0;
static int simulateoutput = 1; /* simulate key presses for X */
static int printoutput = 0; /* print key pressed to stdout */
static char *name = "svkbd";
static int debug = 0;
static int numlayers = 0;
static int numkeys = 0;

static char *colors[10][2]; /* 10 schemes, 2 colors each */
static char *fonts[] = { 0 };

static xkb_keysym_t ispressingkeysym;

bool ispressing = false;
bool sigtermd = false;

static struct {
	int x, y;
} ptrstate;

#define MAX_POINTS 32

/* we assume that the slot id is at maximum the number of fingers on the screen */
static struct {
	int x, y;
	Key *k;
} touchstate[MAX_POINTS];

static int mon = -1;
static struct wl_display *dpy;
static struct wl_compositor *compositor;
static struct wl_pointer *pointer;
static struct wl_touch *touch;
static struct wl_seat *seat;
static struct wl_surface *surface;
static struct wl_registry *reg;
static struct swc_panel_manager *panelman;
static struct swc_panel *panel;
static struct zwp_input_method_manager_v2 *immanager;
static struct zwp_input_method_v2 *im;

/* Input Method */
#define MAX_SURROUNDING_TEXT 4000
static char surrounding_text[MAX_SURROUNDING_TEXT];
static char surrounding_text2[MAX_SURROUNDING_TEXT];
static uint32_t cursor;
static uint32_t cursor2;
static uint32_t anchor;
static uint32_t anchor2;
static uint32_t cause;
static uint32_t cause2;
static uint32_t hint;
static uint32_t hint2;
static uint32_t purpose;
static uint32_t purpose2;
static bool active;
static bool active2;
static uint32_t serial = 0;

/* configuration, allows nested code to access above variables */
#include "config.h"
#ifndef LAYOUT
#error "make sure to define LAYOUT"
#endif
#include LAYOUT

static Key keys[KEYS] = { NULL };
static Key* layers[LAYERS];

void
cleanup(void)
{
	int i;

	for (i = 0; i < SchemeLast; i++)
		free(scheme[i]);
	drw_sync(drw);
	drw_free(drw);
}

void
countrows(void)
{
	int i;

	for (i = 0, rows = 1; i < numkeys; i++) {
		if (keys[i].keysym == 0) {
			rows++;
			if ((i > 0) && (keys[i-1].keysym == 0)) {
				rows--;
				break;
			}
		}
	}
}

int
countkeys(Key *layer)
{
	int i, nkeys = 0;

	for (i = 0; i < KEYS; i++) {
		if (i > 0 && layer[i].keysym == 0 && layer[i - 1].keysym == 0) {
			nkeys--;
			break;
		}
		nkeys++;
	}

	return nkeys;
}

void
drawkeyboard(void)
{
	int i;
	warn("drawing keyboard...");
	wld_set_target_surface(drw->renderer, drw->surface);

	for (i = 0; i < numkeys; i++) {
		if (keys[i].keysym != 0)
			drawkey(&keys[i]);
	}
	drw_map(drw, surface, 0, 0, ww, wh);
}

void
drawkey(Key *k)
{
	int x, y, w, h;
	const char *l;

	wld_set_target_surface(drw->renderer, drw->surface);
	int use_scheme = SchemeNorm;

	if (k->pressed)
		use_scheme = SchemePress;
	else if (k->highlighted)
		use_scheme = SchemeHighlight;
	else if (k->isoverlay)
		use_scheme = SchemeOverlay;
	else if ((k->keysym == XKB_KEY_Return) ||
			((k->keysym >= XKB_KEY_a) && (k->keysym <= XKB_KEY_z)) ||
			((k->keysym >= XKB_KEY_Cyrillic_io) && (k->keysym <= XKB_KEY_Cyrillic_hardsign)))
		use_scheme = SchemeNormABC;
	else
		use_scheme = SchemeNorm;

	drw_setscheme(drw, scheme[use_scheme]);
	drw_rect(drw, k->x, k->y, k->w, k->h, 1, 1);

	if (k->keysym == XKB_KEY_KP_Insert) {
		if (enableoverlays) {
			l = "≅";
		} else {
			l = "≇";
		}
	} else if (k->label) {
		l = k->label;
	} else {
		warn("key missing label");
	}
	h = drw->fonts[0].wld->height + 10;
	y = k->y + (k->h / 2) - (h / 2);
	w = TEXTW(l);
	x = k->x + (k->w / 2) - (w / 2);
	drw_text(drw, x, y, w, h, 0, l, 0);
	if (k->label2) {
		if (use_scheme == SchemeNorm)
			use_scheme = SchemeNormShift;
		else if (use_scheme == SchemeNormABC)
			use_scheme = SchemeNormABCShift;
		else if (use_scheme == SchemePress)
			use_scheme = SchemePressShift;
		else if (use_scheme == SchemeHighlight)
			use_scheme = SchemeHighlightShift;
		else if (use_scheme == SchemeOverlay)
			use_scheme = SchemeOverlayShift;
		drw_setscheme(drw, scheme[use_scheme]);
		x += w;
		//y -= 15;
		l = k->label2;
		w = TEXTW(l);
		drw_text(drw, x, y, w, h, 0, l, 0);
	}
}

Key *
findkey(int x, int y) {
	int i;

	for (i = 0; i < numkeys; i++) {
		if (keys[i].keysym && x > keys[i].x &&
				x < keys[i].x + keys[i].w &&
				y > keys[i].y && y < keys[i].y + keys[i].h) {
			return &keys[i];
		}
	}
	return NULL;
}

int
hasoverlay(xkb_keysym_t keysym)
{
	int begin, i;

	begin = 0;
	for (i = 0; i < OVERLAYS; i++) {
		if (overlay[i].keysym == XKB_KEY_Cancel) {
			begin = i + 1;
		} else if (overlay[i].keysym == keysym) {
			return begin + 1;
		}
	}
	return -1;
}

void
record_press_begin(xkb_keysym_t ks)
{
	/* record the begin of the press, don't simulate the actual keypress yet */
	gettimeofday(&pressbegin, NULL);
	ispressingkeysym = ks;
}


/* TODO replace with something saner */
bool
IsModifierKey(int ks)
{
	return (ks >= XKB_KEY_Shift_L && ks <= XKB_KEY_Hyper_R);
}

void
press(Key *k)
{
	fprintf(stderr, "pressed key %s\n", k->label);
	k->pressed = true;
}

void
printkey(Key *k, xkb_keysym_t mod)
{
	int i, shift;

	shift = (mod == XKB_KEY_Shift_L) || (mod == XKB_KEY_Shift_R) || (mod == XKB_KEY_Shift_Lock);
	if (!shift) {
		for (i = 0; i < numkeys; i++) {
			if ((keys[i].pressed) && ((keys[i].keysym == XKB_KEY_Shift_L) ||
				(keys[i].keysym == XKB_KEY_Shift_R) || (keys[i].keysym == XKB_KEY_Shift_Lock))) {
				shift = true;
				break;
			}
		}
	}
	printdbg("Printing key %ld (shift=%d)\n", k->keysym, shift);
	if (k->keysym == XKB_KEY_Cancel)
		return;

	xkb_keysym_t *keysym = &(k->keysym);

	char buffer[32];
	xkb_keysym_t ignore;
	int l = xkb_keysym_get_name(*keysym, buffer, sizeof(buffer));
	buffer[l] = '\0';
	printdbg("Print buffer: [%s] (length=%d)\n", &buffer, l);
	printf("%s", buffer);
}

void
simulate_keypress(xkb_keysym_t keysym)
{
}

void
simulate_keyrelease(xkb_keysym_t keysym)
{
}

double
get_press_duration(void)
{
	struct timeval now;

	gettimeofday(&now, NULL);

	return (double) ((now.tv_sec * 1000000L + now.tv_usec) -
		   (pressbegin.tv_sec * 1000000L + pressbegin.tv_usec)) /
		   (double) 1000000L;
}

void
unpress(Key *k)
{
	warn("sending...\n");
	int i;

	if (k != NULL) {
		switch(k->keysym) {
		case XKB_KEY_Cancel:
			cyclelayer();
			return;
		case XKB_KEY_script_switch:
			togglelayer();
			return;
		case XKB_KEY_KP_Insert:
			enableoverlays = !enableoverlays;
			return;
		case XKB_KEY_Break:
			running = false;
			return;
		case XKB_KEY_BackSpace:
			zwp_input_method_v2_delete_surrounding_text(im, 1, 0);
			break;
		case XKB_KEY_Return:
			zwp_input_method_v2_commit_string(im, "\n");
			break;
		default:
			zwp_input_method_v2_commit_string(im, k->label);
			break;
		}
		zwp_input_method_v2_commit(im, serial);
		serial += 1;

		k->pressed = false;
		fprintf(stderr, "unpress of %s, %d\n", k->label, k->pressed);
	}

}

static void
regglobal(void *d, struct wl_registry *r, uint32_t name, const char *interface, uint32_t version)
{
	if (strcmp(interface, "wl_compositor") == 0)
		compositor = wl_registry_bind(r, name, &wl_compositor_interface, 1);
	else if (strcmp(interface, "wl_seat") == 0)
		seat = wl_registry_bind(r, name, &wl_seat_interface, 1);
	else if (strcmp(interface, "swc_panel_manager") == 0)
		panelman = wl_registry_bind(r, name, &swc_panel_manager_interface, 1);
	else if (strcmp(interface, "zwp_input_method_manager_v2") == 0)
		immanager = wl_registry_bind(r, name, &zwp_input_method_manager_v2_interface, 1);
}

static void
regglobalremove(void *d, struct wl_registry *reg, uint32_t name)
{
}

static const struct wl_registry_listener reglistener = { regglobal, regglobalremove };

static void
pointerenter(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface, wl_fixed_t sx, wl_fixed_t sy)
{
	ptrstate.x = wl_fixed_to_int(sx);
	ptrstate.y = wl_fixed_to_int(sy);
}

static void
pointerleave(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface)
{
	if (currentoverlay != -1)
		hideoverlay();
	ispressingkeysym = 0;
	unpress(NULL);
}

static void
pointermotion(void *data, struct wl_pointer *wl_pointer, uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
	ptrstate.x = wl_fixed_to_int(sx);
	ptrstate.y = wl_fixed_to_int(sy);
	int i;
	int lostfocus = -1;
	int gainedfocus = -1;

	for (i = 0; i < numkeys; i++) {
		if (keys[i].keysym && ptrstate.x > keys[i].x
				&& ptrstate.x < keys[i].x + keys[i].w
				&& ptrstate.y > keys[i].y
				&& ptrstate.y < keys[i].y + keys[i].h) {
			if (!keys[i].highlighted) {
				if (ispressing) {
					gainedfocus = i;
				} else {
					keys[i].highlighted = true;
					drawkeyboard();
				}
			}
			continue;
		} else if (keys[i].highlighted) {
			keys[i].highlighted = false;
			drawkeyboard();
		}
	}

	for (i = 0; i < numkeys; i++) {
		if (!IsModifierKey(keys[i].keysym) && keys[i].pressed && lostfocus != gainedfocus) {
			printdbg("Pressed key lost focus: %ld\n", keys[i].keysym);
			lostfocus = i;
			ispressingkeysym = 0;
			keys[i].pressed = false;
		}
	}

	if ((lostfocus != -1) && (gainedfocus != -1) && (lostfocus != gainedfocus)) {
		printdbg("Clicking new key that gained focus\n");
		press(&keys[gainedfocus]);
		keys[gainedfocus].pressed = true;
		keys[gainedfocus].highlighted = true;
	}
}

void
pointerbutton(void *data, struct wl_pointer *wl_pointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state)
{
	Key *k;
	int i;

	ispressing = true;

	switch (state) {
	case WL_POINTER_BUTTON_STATE_PRESSED:
		if ((k = findkey(ptrstate.x, ptrstate.y)))
			press(k);

		break;
	
	case WL_POINTER_BUTTON_STATE_RELEASED:
		if ((k = findkey(ptrstate.x, ptrstate.y)))
			unpress(k);
		break;
	}
}


static const struct wl_pointer_listener pointerlistener = { pointerenter, pointerleave, pointermotion, pointerbutton };

void
touchdown(void *data, struct wl_touch *wl_touch, uint32_t serial, uint32_t time, struct wl_surface *surface, int32_t id, wl_fixed_t x, wl_fixed_t y)
{
	Key *k;

	ispressing = true;
	touchstate[id].x = wl_fixed_to_int(x);
	touchstate[id].y = wl_fixed_to_int(y);

	if ((k = findkey(touchstate[id].x, touchstate[id].y)))
		press(k);

	touchstate[id].k = k;
}

void
touchup(void *data, struct wl_touch *wl_touch, uint32_t serial, uint32_t time, int32_t id)
{
	/*
	Key *k;
	if ((k = findkey(touchstate[id].x, touchstate[id].y)))
		unpress(k);
	touchstate[id].x = DBL_MIN;
	touchstate[id].y = DBL_MIN;
	touchstate[id].k = NULL;
	*/
	unpress(touchstate[id].k);
	touchstate[id].x = -1;
	touchstate[id].y = -1;
	touchstate[id].k = NULL;
}

void
touchmotion(void *data, struct wl_touch *wl_touch, uint32_t time, int32_t id, wl_fixed_t x, wl_fixed_t y)
{
	Key *k;
	touchstate[id].x = wl_fixed_to_int(x);
	touchstate[id].y = wl_fixed_to_int(y);

	int i;
	int lostfocus = -1;
	int gainedfocus = -1;

	if ((k = findkey(touchstate[id].x, touchstate[id].y))) {
		if (k == touchstate[id].k)
			return;

		if (touchstate[id].k)
			touchstate[id].k->pressed = false;

		press(k);
		touchstate[id].k = k;
	} else if (touchstate[id].k) {
		touchstate[id].k->pressed = false;
		touchstate[id].k = NULL;
	}
}

void
touchframe(void *data, struct wl_touch *wl_touch)
{
	drawkeyboard();
}

void
touchcancel(void *data, struct wl_touch *wl_touch)
{
	int i;
	for (i = 0; i < numkeys; i++)
		keys[i].pressed = false;

	for (i = 0; i < MAX_POINTS; i++) {
		touchstate[i].x = -1;
		touchstate[i].y = -1;
		touchstate[i].k = NULL;
	}
	drawkeyboard();
	fprintf(stderr, "cancel!\n");
}

static const struct wl_touch_listener touchlistener = { touchdown, touchup, touchmotion, touchframe , touchcancel};

void
imactivate(void *data, struct zwp_input_method_v2 *input_method)
{
	surrounding_text2[0] = '\0';
	cause2 = 0;
	hint2 = 0;
	purpose2 = 0;
	active2 = true;
}

void
imdeactivate(void *data, struct zwp_input_method_v2 *input_method)
{
	active2 = false;
}

void
imdone(void *data, struct zwp_input_method_v2 *input_method)
{
	memcpy(surrounding_text2, surrounding_text, sizeof(surrounding_text));
	cause = cause2;
	hint = hint2;
	purpose = purpose2;
	active = active2;
}

void
imsurrounding_text(void *data, struct zwp_input_method_v2 *input_method, const char *text, uint32_t tcursor, uint32_t tanchor)
{
	memcpy(surrounding_text2, text, strlen(text));
	cursor2 = tcursor;
	anchor2 = tanchor;
}

void
imtext_change_cause(void *data, struct zwp_input_method_v2 *input_method, uint32_t tcause)
{
	cause2 = tcause;
}

void
imcontent_type(void *data, struct zwp_input_method_v2 *input_method, uint32_t thint, uint32_t tpurpose)
{
	hint2 = thint;
	purpose2 = tpurpose;
}

void
imunavailable(void *data, struct zwp_input_method_v2 *input_method)
{
	zwp_input_method_v2_destroy(im);
	zwp_input_method_manager_v2_destroy(immanager);
}

static const struct zwp_input_method_v2_listener imlistener = {
	.activate = imactivate,
	.deactivate = imdeactivate,
	.surrounding_text = imsurrounding_text,
	.text_change_cause = imtext_change_cause,
	.content_type = imcontent_type,
	.done = imdone,
	.unavailable = imunavailable
};

static void
panel_docked(void *data, struct swc_panel *panel, uint32_t length)
{
	ww = length;
}

static const struct swc_panel_listener panellistener = { .docked = &panel_docked };

void
run(void)
{
	struct pollfd fds[2];
	struct timeval tv;
	double duration = 0.0;
	int overlayidx = -1;
	int i, r;

	fds[0].fd = wl_display_get_fd(dpy);
	fds[0].events = POLLIN;

	/* TODO use timer_create to create timer for long presses */
	fds[1].fd = -1;
	fds[1].events = POLLIN;
	tv.tv_sec = 0;
	tv.tv_usec = scan_rate;

	while (running) {
		if (poll(fds, sizeof(fds) / sizeof(fds[0]), -1) == -1) {
			fprintf(stderr, "poll failed\n");
			break;
		}

		if (fds[0].revents & POLLIN) {
			if (wl_display_dispatch(dpy) == -1) {
				warn("failed to dispatch display:");
				break;
			}
		}

		if (0) {
			/* time-out expired without anything interesting happening, check for long-presses */
			if (ispressing && ispressingkeysym) {
				duration = get_press_duration();
				if (debug >= 2)
					printdbg("%f\n", duration);
				overlayidx = hasoverlay(ispressingkeysym);
				duration = get_press_duration();
				if ((overlayidx != -1) && (duration >= overlay_delay)) {
					printdbg("press duration %f, activating overlay\n", duration);
					showoverlay(overlayidx);
					pressbegin.tv_sec = 0;
					pressbegin.tv_usec = 0;
					ispressingkeysym = 0;
				} else if ((overlayidx == -1) && (duration >= repeat_delay)) {
					printdbg("press duration %f, activating repeat\n", duration);
					simulate_keyrelease(ispressingkeysym);
					simulate_keypress(ispressingkeysym);
				}
			}
		}
		if (r == -1 || sigtermd) {
			/* an error occurred or we received a signal */
			/* E.g. Generally in scripts we want to call SIGTERM on svkbd in which case
					if the user is holding for example the enter key (to execute
					the kill or script that does the kill), that causes an issue
					since then X doesn't know the keyup is never coming.. (since
					process will be dead before finger lifts - in that case we
					just trigger out fake up presses for all keys */
			printdbg("signal received, releasing all keys");
			running = false;
		}

		wl_display_flush(dpy);
	}
}

void
setup(void)
{
	int i, j, rh;

	drw = drw_create(dpy);

	if (!compositor || !seat || !panelman)
		exit(1);

	pointer = wl_seat_get_pointer(seat);
	wl_pointer_add_listener(pointer, &pointerlistener, NULL);

	touch = wl_seat_get_touch(seat);
	wl_touch_add_listener(touch, &touchlistener, NULL);

	for (i = 0; i < MAX_POINTS; i++) {
		touchstate[i].x = touchstate[i].y = -1;
	}

	wl_display_roundtrip(dpy);

	if (!pointer || !touch)
		exit(1);

	im = zwp_input_method_manager_v2_get_input_method(immanager, seat);
	zwp_input_method_v2_add_listener(im, &imlistener, NULL);

	wl_display_roundtrip(dpy);

	if (!im)
		exit(1);

	/* Apply defaults to font and colors */
	if (!fonts[0])
		fonts[0] = estrdup(defaultfonts[0]);
	for (i = 0; i < SchemeLast; ++i) {
		for (j = 0; j < 2; ++j) {
			if (!colors[i][j])
				colors[i][j] = estrdup(defaultcolors[i][j]);
		}
	}

	if (!drw_fontset_create(drw, (const char **) fonts, LENGTH(fonts)))
		die("no fonts could be loaded");
	free(fonts[0]);

	/* init appearance */
	for (j = 0; j < SchemeLast; j++)
		scheme[j] = drw_scm_create(drw, (const char **) colors[j], 2);

	for (j = 0; j < SchemeLast; ++j) {
		free(colors[j][ColFg]);
		free(colors[j][ColBg]);
	}

	drw_setscheme(drw, scheme[SchemeNorm]);

	surface = wl_compositor_create_surface(compositor);
	panel = swc_panel_manager_create_panel(panelman, surface);
	swc_panel_add_listener(panel, &panellistener, NULL);
	swc_panel_dock(panel, SWC_PANEL_EDGE_BOTTOM, NULL, 0);
	wl_display_roundtrip(dpy);

	/* init appearance */
	countrows();
	/* TODO calculate row height properly */
	rh = drw->fonts[0].wld->height + 15;
	if (!ww)
	   exit(1);
	if (!wh)
		wh = rh * rows;


	for (i = 0; i < numkeys; i++)
		keys[i].pressed = 0;

	drw_resize(drw, surface, ww, wh);
	swc_panel_set_strut(panel, wh, 0, ww);
	updatekeys();
	drawkeyboard();
	wl_display_roundtrip(dpy);
}

void
updatekeys(void)
{
	int i, j;
	int x = 0, y = 0, h, base, r = rows;

	h = (wh - 1) / rows;
	for (i = 0; i < numkeys; i++, r--) {
		for (j = i, base = 0; j < numkeys && keys[j].keysym != 0; j++)
			base += keys[j].width;
		for (x = 0; i < numkeys && keys[i].keysym != 0; i++) {
			keys[i].x = x;
			keys[i].y = y;
			keys[i].w = keys[i].width * (ww - 1) / base;
			keys[i].h = r == 1 ? wh - y - 1 : h;
			x += keys[i].w;
		}
		if (base != 0)
			keys[i - 1].w = ww - 1 - keys[i - 1].x;
		y += h;
	}
}

void
usage(char *argv0)
{
	fprintf(stderr, "usage: %s [-hdnovDOR] [-g geometry] [-fn font] [-l layers] [-s initial_layer]\n", argv0);
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "  -d		 - Set Dock Window Type\n");
	fprintf(stderr, "  -D		 - Enable debug\n");
	fprintf(stderr, "  -O		 - Disable overlays\n");
	fprintf(stderr, "  -R		 - Disable press-on-release\n");
	fprintf(stderr, "  -n		 - Do not simulate key presses for X\n");
	fprintf(stderr, "  -o		 - Print to standard output\n");
	fprintf(stderr, "  -l		 - Comma separated list of layers to enable\n");
	fprintf(stderr, "  -s		 - Layer to select on program start\n");
	fprintf(stderr, "  -H [int]   - Height fraction, one key row takes 1/x of the screen height\n");
	fprintf(stderr, "  -fn [font] - Set font (Xft, e.g: DejaVu Sans:bold:size=20)\n");
	fprintf(stderr, "  -g		 - Set the window position or size using the X geometry format\n");
	exit(1);
}

void
setlayer(void)
{
	numkeys = countkeys(layers[currentlayer]);
	memcpy(&keys, layers[currentlayer], sizeof(Key) * numkeys);
	countrows();
}

void
cyclelayer(void)
{
	currentlayer++;
	if (currentlayer >= numlayers)
		currentlayer = 0;
	printdbg("Cycling to layer %d\n", currentlayer);
	setlayer();
	updatekeys();
	drawkeyboard();
}

void
togglelayer(void)
{
	if (currentlayer > 0) {
		currentlayer = 0;
	} else if (numlayers > 1) {
		currentlayer = 1;
	}
	printdbg("Toggling layer %d\n", currentlayer);
	setlayer();
	updatekeys();
	drawkeyboard();
}

void
showoverlay(int idx)
{
	int i, j;

	printdbg("Showing overlay %d\n", idx);

	/* unpress existing key (visually only) */
	for (i = 0; i < numkeys; i++) {
		if (keys[i].pressed && !IsModifierKey(keys[i].keysym)) {
			keys[i].pressed = 0;
			break;
		}
	}

	for (i = idx, j=0; i < OVERLAYS; i++, j++) {
		if (overlay[i].keysym == XKB_KEY_Cancel) {
			break;
		}
		while (keys[j].keysym == 0)
			j++;
		if (overlay[i].width > 1)
			j += overlay[i].width - 1;
		keys[j].label = overlay[i].label;
		keys[j].label2 = overlay[i].label2;
		keys[j].keysym = overlay[i].keysym;
		keys[j].modifier = overlay[i].modifier;
		keys[j].isoverlay = true;
	}
	currentoverlay = idx;
	overlaykeysym = ispressingkeysym;
	releaseprotect = 1;
	updatekeys();
	drawkeyboard();
}

void
hideoverlay(void)
{
	printdbg("Hiding overlay, overlay was #%d\n", currentoverlay);
	currentoverlay = -1;
	overlaykeysym = 0;
	currentlayer--;
	cyclelayer();
}

void
sigterm(int signo)
{
	running = false;
	sigtermd = true;
	printdbg("SIGTERM received\n");
}

void
init_layers(char *layer_names_list, const char *initial_layer_name)
{
	char *s;
	int j, found;

	if (layer_names_list == NULL) {
		numlayers = LAYERS;
		memcpy(&layers, &available_layers, sizeof(available_layers));
		if (initial_layer_name != NULL) {
			for (j = 0; j < LAYERS; j++) {
				if (strcmp(layer_names[j], initial_layer_name) == 0) {
					currentlayer = j;
					break;
				}
			}
		}
	} else {
		s = strtok(layer_names_list, ",");
		while (s != NULL) {
			if (numlayers + 1 > LAYERS)
				die("too many layers specified");
			found = 0;
			for (j = 0; j < LAYERS; j++) {
				if (strcmp(layer_names[j], s) == 0) {
					fprintf(stderr, "Adding layer %s\n", s);
					layers[numlayers] = available_layers[j];
					if (initial_layer_name != NULL && strcmp(layer_names[j], initial_layer_name) == 0) {
						currentlayer = numlayers;
					}
					found = 1;
					break;
				}
			}
			if (!found) {
				fprintf(stderr, "Undefined layer: %s\n", s);
				exit(3);
			}
			numlayers++;
			s = strtok(NULL, ",");
		}
	}
	setlayer();
}

void
printdbg(const char *fmt, ...)
{
	if (!debug)
		return;

	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fflush(stderr);
}

int
main(int argc, char *argv[])
{
	char *initial_layer_name = NULL;
	char *layer_names_list = NULL;
	char *tmp;
	int i, xr, yr, bitm;
	unsigned int wr, hr;

	signal(SIGTERM, sigterm);

	if (OVERLAYS <= 1) {
		enableoverlays = 0;
	} else {
		if ((tmp = getenv("SVKBD_ENABLEOVERLAYS")))
			enableoverlays = atoi(tmp);
	}
	if ((tmp = getenv("SVKBD_LAYERS")))
		layer_names_list = estrdup(tmp);

	if ((tmp = getenv("SVKBD_HEIGHTFACTOR")))
		heightfactor = atoi(tmp);

	if ((tmp = getenv("SVKBD_PRESSONRELEASE"))) /* defaults to 1 */
		pressonrelease = atoi(tmp);

	/* parse command line arguments */
	for (i = 1; argv[i]; i++) {
		if (!strcmp(argv[i], "-v")) {
			die("svkbd-"VERSION);
		} else if (!strcmp(argv[i], "-d")) {
			isdock = true;
		} else if (!strncmp(argv[i], "-g", 2)) {
			if (i >= argc - 1)
				usage(argv[0]);

			/* TODO implement */
		} else if (!strcmp(argv[i], "-fn")) { /* font or font set */
			if (i >= argc - 1)
				usage(argv[0]);
			fonts[0] = estrdup(argv[++i]);
		} else if (!strcmp(argv[i], "-D")) {
			debug = 1;
		} else if (!strcmp(argv[i], "-h")) {
			usage(argv[0]);
		} else if (!strcmp(argv[i], "-O")) {
			enableoverlays = 0;
		} else if (!strcmp(argv[i], "-o")) {
			printoutput = 1;
		} else if (!strcmp(argv[i], "-n")) {
			simulateoutput = 0;
		} else if (!strcmp(argv[i], "-R")) {
			pressonrelease = 0;
		} else if (!strcmp(argv[i], "-l")) {
			if (i >= argc - 1)
				usage(argv[0]);
			free(layer_names_list);
			layer_names_list = estrdup(argv[++i]);
		} else if (!strcmp(argv[i], "-s")) {
			if (i >= argc - 1)
				usage(argv[0]);
			initial_layer_name = argv[++i];
		} else if (!strcmp(argv[i], "-H")) {
			if (i >= argc - 1)
				usage(argv[0]);
			heightfactor = atoi(argv[++i]);
		} else {
			fprintf(stderr, "Invalid argument: %s\n", argv[i]);
			usage(argv[0]);
		}
	}

	if (printoutput)
		setbuf(stdout, NULL); /* unbuffered output */

	if (heightfactor <= 0)
		die("height factor must be a positive integer");

	init_layers(layer_names_list, initial_layer_name);

	if (!setlocale(LC_CTYPE, ""))
		fprintf(stderr, "warning: no locale support");
	if (!(dpy = wl_display_connect(NULL)))
		die("cannot open display");
	if (!(reg = wl_display_get_registry(dpy)))
		die("cannot get registry");
	wl_registry_add_listener(reg, &reglistener, NULL);
	wl_display_roundtrip(dpy);
	setup();
	run();
	cleanup();
	wl_display_disconnect(dpy);
	free(layer_names_list);

	return 0;
}
