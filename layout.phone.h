#define KEYS 18

static Key keys_dialer[KEYS] = {
	{ "1", 0, XKB_KEY_1, 1 },
	{ "2", 0, XKB_KEY_2, 1 },
	{ "3", 0, XKB_KEY_3, 1 },

	{ 0 },

	{ "4", 0, XKB_KEY_4, 1 },
	{ "5", 0, XKB_KEY_5, 1 },
	{ "6", 0, XKB_KEY_6, 1 },

	{ 0 },

	{ "7", 0, XKB_KEY_7, 1 },
	{ "8", 0, XKB_KEY_8, 1 },
	{ "9", 0, XKB_KEY_9, 1 },

	{ 0 },

	{ "*", 0, XKB_KEY_space, 1 },
	{ "0", 0, XKB_KEY_0, 1 },
	{ "#", 0, XKB_KEY_period, 1 },

	{ 0 },

	{ "⟵", 0, XKB_KEY_BackSpace, 2 },
	{ "↲", 0, XKB_KEY_Return, 2},
};

#define OVERLAYS 1

static Key overlay[OVERLAYS] = {
	{0, 0, XKB_KEY_Cancel },
};

#define LAYERS 1

static char* layer_names[LAYERS] = {
	"dialer",
};

static Key* available_layers[LAYERS] = {
	keys_dialer,
};

Buttonmod buttonmods[] = {
};
