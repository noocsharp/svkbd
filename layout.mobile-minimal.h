#define KEYS 44
static Key keys_en[KEYS] = {
	{ "q", 0, XKB_KEY_q, 1 },
	{ "w", 0, XKB_KEY_w, 1 },
	{ "e", 0, XKB_KEY_e, 1 },
	{ "r", 0, XKB_KEY_r, 1 },
	{ "t", 0, XKB_KEY_t, 1 },
	{ "y", 0, XKB_KEY_y, 1 },
	{ "u", 0, XKB_KEY_u, 1 },
	{ "i", 0, XKB_KEY_i, 1 },
	{ "o", 0, XKB_KEY_o, 1 },
	{ "p", 0, XKB_KEY_p, 1 },

	{ 0 }, /* New row */

	{ "a", 0, XKB_KEY_a, 1 },
	{ "s", 0, XKB_KEY_s, 1 },
	{ "d", 0, XKB_KEY_d, 1 },
	{ "f", 0, XKB_KEY_f, 1 },
	{ "g", 0, XKB_KEY_g, 1 },
	{ "h", 0, XKB_KEY_h, 1 },
	{ "j", 0, XKB_KEY_j, 1 },
	{ "k", 0, XKB_KEY_k, 1 },
	{ "l", 0, XKB_KEY_l, 1 },
	{ ";",":", XKB_KEY_colon, 1 },
	/*{ "'", XKB_KEY_apostrophe, 2 },*/

	{ 0 }, /* New row */

	{ "Shft", 0, XKB_KEY_Shift_L, 1 },
	{ "z", 0, XKB_KEY_z, 1 },
	{ "x", 0, XKB_KEY_x, 1 },
	{ "c", 0, XKB_KEY_c, 1 },
	{ "v", 0, XKB_KEY_v, 1 },
	{ "b", 0, XKB_KEY_b, 1 },
	{ "n", 0, XKB_KEY_n, 1 },
	{ "m", 0, XKB_KEY_m, 1 },
	/*{ "/?", XKB_KEY_slash, 1 },*/

	{ 0 }, /* New row */
	{ "⇍ Bksp", 0, XKB_KEY_BackSpace, 2 },
	{ "↺", 0, XKB_KEY_Cancel, 1},
	{ "", 0, XKB_KEY_space, 2 },
	{ "↲ Enter", 0, XKB_KEY_Return, 2 },
};

static Key keys_symbols[KEYS] = {
	{ "1", "!", XKB_KEY_1, 1 },
	{ "2", "@", XKB_KEY_2, 1 },
	{ "3", "#", XKB_KEY_3, 1 },
	{ "4", "$", XKB_KEY_4, 1 },
	{ "5", "%", XKB_KEY_5, 1 },
	{ "6", "^", XKB_KEY_6, 1 },
	{ "7", "&", XKB_KEY_7, 1 },
	{ "8", "*", XKB_KEY_8, 1 },
	{ "9", "(", XKB_KEY_9, 1 },
	{ "0", ")", XKB_KEY_0, 1 },

	{ 0 }, /* New row */

	{ "'", "\"", XKB_KEY_apostrophe, 1 },
	{ "`", "~", XKB_KEY_grave, 1 },
	{ "-", "_", XKB_KEY_minus, 1 },
	{ "=", "+", XKB_KEY_plus, 1 },
	{ "[", "{", XKB_KEY_bracketleft, 1 },
	{ "]", "}", XKB_KEY_bracketright, 1 },
	{ ",", "<", XKB_KEY_comma, 1 },
	{ ".", ">", XKB_KEY_period, 1 },
	{ "/", "?", XKB_KEY_slash, 1 },
	{ "\\", "|", XKB_KEY_backslash, 1 },

	{ 0 }, /* New row */

	{ "", 0, XKB_KEY_Shift_L|XKB_KEY_bar, 1 },
	{ "⇍ Bksp", 0, XKB_KEY_BackSpace, 2 },

	{ 0 }, /* New row */
	{ "↺", 0, XKB_KEY_Cancel, 1},
	{ "Shft", 0, XKB_KEY_Shift_L, 1 },
	{ "", 0, XKB_KEY_space, 2 },
	{ "↲ Enter", 0, XKB_KEY_Return, 2 },
};

#define OVERLAYS 1
static Key overlay[OVERLAYS] = {
	{ 0, 0, XKB_KEY_Cancel },
};

#define LAYERS 2
static char* layer_names[LAYERS] = {
	"en",
	"symbols",
};

static Key* available_layers[LAYERS] = {
	keys_en,
	keys_symbols,
};
