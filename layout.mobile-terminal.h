#define KEYS 46
static Key keys_en[KEYS] = {
	{ "Tab",  0, XKB_KEY_Tab, 2 },
	{ "←",  0, XKB_KEY_Left, 2 },
	{ "↑",  0, XKB_KEY_Up, 2 },
	{ "↓",  0, XKB_KEY_Down, 2 },
	{ "→",  0, XKB_KEY_Right, 2 },

	{ 0 }, /* New row */

	{ "q", "Q", XKB_KEY_q, 1 },
	{ "w", "W", XKB_KEY_w, 1 },
	{ "e", "E", XKB_KEY_e, 1 },
	{ "r", "R", XKB_KEY_r, 1 },
	{ "t", "T", XKB_KEY_t, 1 },
	{ "y", "Y", XKB_KEY_y, 1 },
	{ "u", "U", XKB_KEY_u, 1 },
	{ "i", "I", XKB_KEY_i, 1 },
	{ "o", "O", XKB_KEY_o, 1 },
	{ "p", "P", XKB_KEY_p, 1 },

	{ 0 }, /* New row */

	{ "a", "A", XKB_KEY_a, 1 },
	{ "s", "S", XKB_KEY_s, 1 },
	{ "d", "D", XKB_KEY_d, 1 },
	{ "f", "F", XKB_KEY_f, 1 },
	{ "g", "G", XKB_KEY_g, 1 },
	{ "h", "H", XKB_KEY_h, 1 },
	{ "j", "J", XKB_KEY_j, 1 },
	{ "k", "K", XKB_KEY_k, 1 },
	{ "l", "L", XKB_KEY_l, 1 },

	{ 0 }, /* New row */

	{ "⇧", 0, XKB_KEY_Shift_L, 1 },
	{ "z", "Z", XKB_KEY_z, 1 },
	{ "x", "X", XKB_KEY_x, 1 },
	{ "c", "C", XKB_KEY_c, 1 },
	{ "v", "V", XKB_KEY_v, 1 },
	{ "b", "B", XKB_KEY_b, 1 },
	{ "n", "N", XKB_KEY_n, 1 },
	{ "m", "M", XKB_KEY_m, 1 },
	{ "↺", 0, XKB_KEY_Cancel, 1},

	{ 0 }, /* New row */
	{ "⟵", 0, XKB_KEY_BackSpace, 2 },
	{ " ", 0, XKB_KEY_space, 5 },
	{ "↩", 0, XKB_KEY_Return, 2 },
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

	{ "|", "\"", XKB_KEY_apostrophe, 1 },
	{ "`", "~", XKB_KEY_grave, 1 },
	{ "-", "_", XKB_KEY_minus, 1 },
	{ "=", "+", XKB_KEY_plus, 1 },
	{ "[", "{", XKB_KEY_bracketleft, 1 },
	{ "]", "}", XKB_KEY_bracketright, 1 },
	{ ",", "<", XKB_KEY_comma, 1 },
	{ ".", ">", XKB_KEY_period, 1 },
	{ "/", "?", XKB_KEY_slash, 1 },
	{ "\\", "|", XKB_KEY_backslash, 1 },
	{ ";",":", XKB_KEY_colon, 1 },
	{ "'", "\"", XKB_KEY_apostrophe, 2 },

	{ 0 }, /* New row */

	{ "⇧", 0, XKB_KEY_Shift_L, 1 },
	{ "", 0, XKB_KEY_Shift_L, 7 },
	{ "↺", 0, XKB_KEY_Cancel, 1},

	{ 0 }, /* New row */
	{ "⟵", 0, XKB_KEY_BackSpace, 2 },
	{ " ", 0, XKB_KEY_space, 5 },
	{ "↩", 0, XKB_KEY_Return, 2 },
};

static Key keys_control[KEYS] = {
	{ "NUL", "\x00", XKB_KEY_XF86Terminal, 2 },
	{ "SOH", "\x01", XKB_KEY_XF86Terminal, 2 },
	{ "STX", "\x02", XKB_KEY_XF86Terminal, 2 },
	{ "ETX", "\x03", XKB_KEY_XF86Terminal, 2 },
	{ "EOT", "\x04", XKB_KEY_XF86Terminal, 2 },

	{ 0 },

	{ "LF", "\x0A", XKB_KEY_XF86Terminal, 2 },
	{ "VT", "\x0B", XKB_KEY_XF86Terminal, 2 },
	{ "FF", "\x0C", XKB_KEY_XF86Terminal, 2 },
	{ "CR", "\x0D", XKB_KEY_XF86Terminal, 2 },
	{ "SO", "\x0E", XKB_KEY_XF86Terminal, 2 },

	{ 0 }, /* New row */

	{ "DC4", "\x14", XKB_KEY_XF86Terminal, 2 },
	{ "NAK", "\x15", XKB_KEY_XF86Terminal, 2 },
	{ "SYN", "\x16", XKB_KEY_XF86Terminal, 2 },
	{ "ETB", "\x17", XKB_KEY_XF86Terminal, 2 },
	{ "CAN", "\x18", XKB_KEY_XF86Terminal, 2 },

	{ 0 }, /* New row */

	{ "EM",  "\x19", XKB_KEY_XF86Terminal, 2 },
	{ "SUB", "\x1A", XKB_KEY_XF86Terminal, 2 },
	{ "ESC", "\x1B", XKB_KEY_XF86Terminal, 2 },
	{ "FS",  "\x1C", XKB_KEY_XF86Terminal, 2 },
	{ "GS",  "\x1D", XKB_KEY_XF86Terminal, 2 },

	{ 0 }, /* New row */

	{ "↺", 0, XKB_KEY_Cancel, 1},
	{ "RS", "\x1E", XKB_KEY_XF86Terminal, 2 },
	{ "US", "\x1F", XKB_KEY_XF86Terminal, 2 },
};

#define OVERLAYS 1
static Key overlay[OVERLAYS] = {
	{ 0, 0, XKB_KEY_Cancel },
};

#define LAYERS 3
static char* layer_names[LAYERS] = {
	"en",
	"symbols",
	"terminal",
};

static Key* available_layers[LAYERS] = {
	keys_en,
	keys_symbols,
	keys_control,
};
