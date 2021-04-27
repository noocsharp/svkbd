#define KEYS 55

static Key keys_en[KEYS] = {
	{ "Esc", "", XKB_KEY_Escape, 1 },
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
	{ "'", "\"", XKB_KEY_apostrophe, 1 },

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
	{ "/", "?", XKB_KEY_slash, 1 },
	{ "Tab", 0, XKB_KEY_Tab, 1 },

	{ 0 }, /* New row */

	{ "z", 0, XKB_KEY_z, 1 },
	{ "x", 0, XKB_KEY_x, 1 },
	{ "c", 0, XKB_KEY_c, 1 },
	{ "v", 0, XKB_KEY_v, 1 },
	{ "b", 0, XKB_KEY_b, 1 },
	{ "n", 0, XKB_KEY_n, 1 },
	{ "m", 0, XKB_KEY_m, 1 },
	{ ",", "<", XKB_KEY_comma, 1 },
	{ ".", ">", XKB_KEY_period, 1 },
	{ "⌫Bksp", 0, XKB_KEY_BackSpace, 2 },

	{ 0 }, /* New row */
	{ "↺", 0, XKB_KEY_Cancel, 1},
	{ "Shift", 0, XKB_KEY_Shift_L, 2 },
	{ "Ctrl", 0, XKB_KEY_Control_L, 1 },
	{ "Alt", 0, XKB_KEY_Alt_L, 1 },
	{ "", 0, XKB_KEY_space, 2 },
	{ "↓", 0, XKB_KEY_Down, 1 },
	{ "↑", 0, XKB_KEY_Up, 1 },
	{ "↲ Enter", 0, XKB_KEY_Return, 2 },
};

#define OVERLAYS 197
static Key overlay[OVERLAYS] = {
	{ 0, 0, XKB_KEY_a }, //Overlay for a
	//---
	{ "à", 0, XKB_KEY_agrave },
	{ "á", 0, XKB_KEY_aacute },
	{ "â", 0, XKB_KEY_acircumflex },
	{ "ä", 0, XKB_KEY_adiaeresis },
	{ "ą", 0, XKB_KEY_aogonek },
	{ "ã", 0, XKB_KEY_atilde },
	{ "ā", 0, XKB_KEY_amacron },
	{ "ă", 0, XKB_KEY_abreve },
	{ "å", 0, XKB_KEY_aring },
	{ "æ", 0, XKB_KEY_ae },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//--
	{ 0, 0, XKB_KEY_e }, //Overlay for e (first item after boundary defines the trigger)
	//---
	{ "è", 0, XKB_KEY_egrave },
	{ "é", 0, XKB_KEY_eacute },
	{ "ê", 0, XKB_KEY_ecircumflex },
	{ "ë", 0, XKB_KEY_ediaeresis },
	{ "ę", 0, XKB_KEY_eogonek },
	{ "ē", 0, XKB_KEY_emacron },
	{ "ė", 0, XKB_KEY_eabovedot },
	{ 0, 0, XKB_KEY_Cancel },
	//--
	{ 0, 0, XKB_KEY_y }, //New overlay
	//---
	{ "ỳ", 0, XKB_KEY_ygrave },
	{ "ý", 0, XKB_KEY_yacute },
	{ "ŷ", 0, XKB_KEY_ycircumflex },
	{ "ÿ", 0, XKB_KEY_ydiaeresis },
	{ 0, 0, XKB_KEY_Cancel },
	//--
	{ 0, 0, XKB_KEY_u }, //New overlay
	//---
	{ "ù", 0, XKB_KEY_ugrave },
	{ "ú", 0, XKB_KEY_uacute },
	{ "û", 0, XKB_KEY_ucircumflex },
	{ "ü", 0, XKB_KEY_udiaeresis },
	{ "ų", 0, XKB_KEY_uogonek },
	{ "ū", 0, XKB_KEY_umacron },
	{ "ů", 0, XKB_KEY_uring},
	{ "ŭ", 0, XKB_KEY_ubreve},
	{ "ű", 0, XKB_KEY_udoubleacute },
	{ 0, 0, XKB_KEY_Cancel },
	//--
	{ 0, 0, XKB_KEY_i }, //New overlay
	//---
	{ "ì", 0, XKB_KEY_igrave },
	{ "í", 0, XKB_KEY_iacute },
	{ "î", 0, XKB_KEY_icircumflex },
	{ "ï", 0, XKB_KEY_idiaeresis },
	{ "į", 0, XKB_KEY_iogonek },
	{ "ī", 0, XKB_KEY_imacron },
	{ "ı", 0, XKB_KEY_idotless },
	{ 0, 0, XKB_KEY_Cancel },
	//--
	{ 0, 0, XKB_KEY_o }, //New overlay
	//---
	{ "ò", 0, XKB_KEY_ograve },
	{ "ó", 0, XKB_KEY_oacute },
	{ "ô", 0, XKB_KEY_ocircumflex },
	{ "ö", 0, XKB_KEY_odiaeresis },
	{ "ǫ", 0, XKB_KEY_ogonek },
	{ "õ", 0, XKB_KEY_otilde },
	{ "ō", 0, XKB_KEY_omacron },
	{ "ø", 0, XKB_KEY_oslash },
	{ "ő", 0, XKB_KEY_odoubleacute },
	{ "œ", 0, XKB_KEY_oe },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//--
	{ 0, 0, XKB_KEY_d }, //New overlay
	//---
	{ "ď", 0, XKB_KEY_dcaron },
	{ "ð", 0, XKB_KEY_eth },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//--
	{ 0, 0, XKB_KEY_c }, //New overlay
	//---
	{ "ç", 0, XKB_KEY_ccedilla },
	{ "ĉ", 0, XKB_KEY_ccircumflex },
	{ "č", 0, XKB_KEY_ccaron },
	{ "ć", 0, XKB_KEY_cacute },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//--
	{ 0, 0, XKB_KEY_s }, //New overlay
	//---
	{ "ş", 0, XKB_KEY_scedilla },
	{ "ŝ", 0, XKB_KEY_scircumflex },
	{ "š", 0, XKB_KEY_scaron },
	{ "ś", 0, XKB_KEY_sacute },
	{ "ß", 0, XKB_KEY_ssharp },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//---
	{ 0, 0, XKB_KEY_z }, //New overlay
	//---
	{ "ž", 0, XKB_KEY_zcaron },
	{ "ż", 0, XKB_KEY_zabovedot },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//--
	{ 0, 0, XKB_KEY_n }, //New overlay
	//---
	{ "ñ", 0, XKB_KEY_ntilde },
	{ "ń", 0, XKB_KEY_nacute },
	{ "ň", 0, XKB_KEY_ncaron },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//
	{ 0, 0, XKB_KEY_t }, //New overlay
	//---
	{ "ț", 0, XKB_KEY_tcedilla },
	{ "ť", 0, XKB_KEY_tcaron },
	{ "þ", 0, XKB_KEY_thorn },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//----
	{ 0, 0, XKB_KEY_g }, //New overlay
	//---
	{ "ĝ", 0, XKB_KEY_gcircumflex },
	{ "ğ", 0, XKB_KEY_gbreve },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//
	{ 0, 0, XKB_KEY_h }, //New overlay
	//---
	{ "ĥ", 0, XKB_KEY_hcircumflex },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//
	{ 0, 0, XKB_KEY_j }, //New overlay
	//---
	{ "ĵ", 0, XKB_KEY_jcircumflex },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//--
	{ 0, 0, XKB_KEY_l }, //New overlay
	//---
	{ "ł", 0, XKB_KEY_lstroke },
	{ "ľ", 0, XKB_KEY_lcaron },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//--
	{ 0, 0, XKB_KEY_r }, //New overlay
	//---
	{ "ř", 0, XKB_KEY_rcaron },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//---
	{ 0, 0, XKB_KEY_Cyrillic_softsign }, //New overlay
	//---
	{ "ъ", 0, XKB_KEY_Cyrillic_hardsign },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//---
	{ 0, 0, XKB_KEY_Cyrillic_ie }, //New overlay
	//---
	{ "ё", 0, XKB_KEY_Cyrillic_io },
	{ "э", 0, XKB_KEY_Cyrillic_e },
	{ "Є", 0, XKB_KEY_Ukrainian_ie },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//---
	{ 0, 0, XKB_KEY_Cyrillic_i }, //New overlay
	//---
	{ "і", 0, XKB_KEY_Ukrainian_i },
	{ "ї", 0, XKB_KEY_Ukrainian_yi },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//---
	{ 0, 0, XKB_KEY_Cyrillic_u }, //New overlay
	//---
	{ "ў", 0, XKB_KEY_Byelorussian_shortu },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//---
	{ 0, 0, XKB_KEY_Cyrillic_shorti }, //New overlay
	//---
	{ "ј", 0, XKB_KEY_Cyrillic_je },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//---
	{ 0, 0, XKB_KEY_Cyrillic_el }, //New overlay
	//---
	{ "љ", 0, XKB_KEY_Cyrillic_lje },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//---
	{ 0, 0, XKB_KEY_Cyrillic_en }, //New overlay
	//---
	{ "њ", 0, XKB_KEY_Cyrillic_nje },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//---
	{ 0, 0, XKB_KEY_Cyrillic_tse }, //New overlay
	//---
	{ "џ", 0, XKB_KEY_Cyrillic_dzhe },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//---
	{ 0, 0, XKB_KEY_Cyrillic_che }, //New overlay
	//---
	{ "ћ", 0, XKB_KEY_Serbian_tshe },
	{ "ђ", 0, XKB_KEY_Serbian_dje },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//---
	{ "🙂", 0, 0x101f642 }, //emoji overlay
	//---
	{ "😀", 0, 0x101f600 },
	{ "😁", 0, 0x101f601 },
	{ "😂", 0, 0x101f602 },
	{ "😃", 0, 0x101f603 },
	{ "😄", 0, 0x101f604 },
	{ "😅", 0, 0x101f605 },
	{ "😆", 0, 0x101f606 },
	{ "😇", 0, 0x101f607 },
	{ "😈", 0, 0x101f608 },
	{ "😉", 0, 0x101f609 },
	{ "😊", 0, 0x101f60a },
	{ "😋", 0, 0x101f60b },
	{ "😌", 0, 0x101f60c },
	{ "😍", 0, 0x101f60d },
	{ "😎", 0, 0x101f60e },
	{ "😏", 0, 0x101f60f },
	{ "😐", 0, 0x101f610 },
	{ "😒", 0, 0x101f612 },
	{ "😓", 0, 0x101f613 },
	{ "😛", 0, 0x101f61b },
	{ "😮", 0, 0x101f62e },
	{ "😟", 0, 0x101f61f },
	{ "😟", 0, 0x101f620 },
	{ "😢", 0, 0x101f622 },
	{ "😭", 0, 0x101f62d },
	{ "😳", 0, 0x101f633 },
	{ "😴", 0, 0x101f634 },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
	//--
	{ "/?", 0, XKB_KEY_slash }, //punctuation overlay
	//--
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
	{ "¡", 0, XKB_KEY_exclamdown, 1 },
	{ "?", 0, XKB_KEY_questiondown, 1 },
	{ "°", 0, XKB_KEY_degree, 1 },
	{ "£", 0, XKB_KEY_sterling, 1 },
	{ "€", 0, XKB_KEY_EuroSign, 1 },
	{ "¥", 0, XKB_KEY_yen, 1 },
	{ ";", ":", XKB_KEY_colon, 1 },
	{ 0, 0, XKB_KEY_Cancel }, /* XKB_KEY_Cancel signifies  overlay boundary */
};

static Key keys_symbols[KEYS] = {
	{ "Esc", 0, XKB_KEY_Escape, 1 },
	{ "F1", 0, XKB_KEY_F1, 1 },
	{ "F2", 0, XKB_KEY_F2, 1 },
	{ "F3", 0, XKB_KEY_F3, 1 },
	{ "F4", 0, XKB_KEY_F4, 1 },
	{ "F5", 0, XKB_KEY_F5, 1 },
	{ "F6", 0, XKB_KEY_F6, 1 },
	{ "F7", 0, XKB_KEY_F7, 1 },
	{ "F8", 0, XKB_KEY_F8, 1 },
	{ "F9", 0, XKB_KEY_F9, 1 },
	{ "F10", 0, XKB_KEY_F10, 1 },
	{ 0 }, /* New row */

	{ "'\"", 0, XKB_KEY_apostrophe, 1 },
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

	{ ".", ">", XKB_KEY_period, 1 },
	{ ",", "<", XKB_KEY_comma, 1 },
	{ "`", "~", XKB_KEY_grave, 1 },
	{ "-", "_", XKB_KEY_minus, 1 },
	{ "=", "+", XKB_KEY_plus, 1 },
	{ "\\", "|", XKB_KEY_backslash, 1 },
	{ ";", ":", XKB_KEY_colon, 1 },
	{ "/", "?", XKB_KEY_slash, 1 },
	{ "[", "{", XKB_KEY_bracketleft, 1 },
	{ "]", "}", XKB_KEY_bracketright, 1 },
	{ "Del", 0, XKB_KEY_Delete, 1 },

	{ 0 }, /* New row */

	{ "abc", 0, XKB_KEY_Mode_switch, 1 },
	{ "☺", 0, 0x101f642, 1 },
	{ "⇤", 0, XKB_KEY_Home, 1 },
	{ "←", 0, XKB_KEY_Left, 1 },
	{ "→", 0, XKB_KEY_Right, 1 },
	{ "⇥", 0, XKB_KEY_End, 1 },
	{ "⇊", 0, XKB_KEY_Next, 1 },
	{ "⇈", 0, XKB_KEY_Prior, 1 },
	{ "Tab", 0, XKB_KEY_Tab, 1 },
	{ "⌫Bksp", 0, XKB_KEY_BackSpace, 2 },

	{ 0 }, /* New row */
	{ "↺", 0, XKB_KEY_Cancel, 1},
	{ "Shift", 0, XKB_KEY_Shift_L, 2 },
	{ "Ctrl", 0, XKB_KEY_Control_L, 1 },
	{ "Alt", 0, XKB_KEY_Alt_L, 1 },
	{ "", 0, XKB_KEY_space, 2 },
	{ "↓", 0, XKB_KEY_Down, 1 },
	{ "↑", 0, XKB_KEY_Up, 1 },
	{ "↲ Enter", 0, XKB_KEY_Return, 2 },
};

static Key keys_functions[KEYS] = {

	{ "Esc", 0, XKB_KEY_Escape, 1 },
	{ "▶", 0, XKB_KEY_XF86AudioPlay, 1 },
	{ "●", 0, XKB_KEY_XF86AudioRecord, 1 },
	{ "■", 0, XKB_KEY_XF86AudioStop, 1 },
	{ "◂◂", 0, XKB_KEY_XF86AudioPrev, 1 },
	{ "▸▸", 0, XKB_KEY_XF86AudioNext, 1 },
	{ "♫M", 0, XKB_KEY_XF86AudioMute, 1 },
	{ "♫-", 0, XKB_KEY_XF86AudioLowerVolume, 1 },
	{ "♫+", 0, XKB_KEY_XF86AudioRaiseVolume, 1 },
	{ "☀-", 0, XKB_KEY_XF86MonBrightnessDown, 1 },
	{ "☀+", 0, XKB_KEY_XF86MonBrightnessUp, 1 },

	{ 0 }, /* New row */

	{ "≅", 0, XKB_KEY_KP_Insert, 1 },
	{ "Del", 0, XKB_KEY_Delete, 1 },
	{ "⇤", 0, XKB_KEY_Home, 1 },
	{ "←", 0, XKB_KEY_Left, 1 },
	{ "→", 0, XKB_KEY_Right, 1 },
	{ "⇥", 0, XKB_KEY_End, 1 },
	{ "⇊", 0, XKB_KEY_Next, 1 },
	{ "⇈", 0, XKB_KEY_Prior, 1 },
	{ "Tab", 0, XKB_KEY_Tab, 1 },
	{ "⌫Bksp", 0, XKB_KEY_BackSpace, 2 },

	{ 0 }, /* New row */
	{ "↺", 0, XKB_KEY_Cancel, 1},
	{ "Shift", 0, XKB_KEY_Shift_L, 2 },
	{ "Ctrl", 0, XKB_KEY_Control_L, 1 },
	{ "Alt", 0, XKB_KEY_Alt_L, 1 },
	{ "", 0, XKB_KEY_space, 2 },
	{ "↓", 0, XKB_KEY_Down, 1 },
	{ "↑", 0, XKB_KEY_Up, 1 },
	{ "↲ Enter", 0, XKB_KEY_Return, 2 },

	{ 0 }, /* Last item (double 0) */
	{ 0 }, /* Last item (double 0) */
};

static Key keys_navigation[KEYS] = {
	{ "Esc", 0, XKB_KEY_Escape, 1 },
	{ "⇤", 0, XKB_KEY_Home, 1 },
	{ "↑", 0, XKB_KEY_Up, 1 },
	{ "⇥", 0, XKB_KEY_End, 1 },
	{ "⇈", 0, XKB_KEY_Prior, 1 },
	{ 0 }, /* New row */

	{ "Shift", 0, XKB_KEY_Shift_L, 1 },
	{ "←", 0, XKB_KEY_Left, 1 },
	{ "", 0, XKB_KEY_space, 1 },
	{ "→", 0, XKB_KEY_Right, 1 },
	{ "⇊", 0, XKB_KEY_Next, 1 },

	{ 0 }, /* New row */

	{ "↺", 0, XKB_KEY_Cancel, 1},
	{ "⌫Bksp", 0, XKB_KEY_BackSpace, 1 },
	{ "↓", 0, XKB_KEY_Down, 1 },
	{ "Tab", 0, XKB_KEY_Tab, 1 },
	{ "↲ Enter", 0, XKB_KEY_Return, 1},
  { 0 }, /* Last item (double 0) */
  { 0 }, /* Last item (double 0) */
};


static Key keys_ru[KEYS] = {
	{ "Esc", 0, XKB_KEY_Escape, 1 },
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

	{ "й", 0, XKB_KEY_Cyrillic_shorti, 1 },
	{ "ц", 0, XKB_KEY_Cyrillic_tse, 1 },
	{ "у", 0, XKB_KEY_Cyrillic_u, 1 },
	{ "к", 0, XKB_KEY_Cyrillic_ka, 1 },
	{ "е", 0, XKB_KEY_Cyrillic_ie, 1 },
	{ "н", 0, XKB_KEY_Cyrillic_en, 1 },
	{ "г", 0, XKB_KEY_Cyrillic_ghe, 1 },
	{ "ш", 0, XKB_KEY_Cyrillic_sha, 1 },
	{ "щ", 0, XKB_KEY_Cyrillic_shcha, 1 },
	{ "з", 0, XKB_KEY_Cyrillic_ze, 1 },
	{ "х", 0, XKB_KEY_Cyrillic_ha, 1 },

	{ 0 }, /* New row */

	{ "ф", 0, XKB_KEY_Cyrillic_ef, 1 },
	{ "ы", 0, XKB_KEY_Cyrillic_yeru, 1 },
	{ "в", 0, XKB_KEY_Cyrillic_ve, 1 },
	{ "а", 0, XKB_KEY_Cyrillic_a, 1 },
	{ "п", 0, XKB_KEY_Cyrillic_pe, 1 },
	{ "р", 0, XKB_KEY_Cyrillic_er, 1 },
	{ "о", 0, XKB_KEY_Cyrillic_o, 1 },
	{ "л", 0, XKB_KEY_Cyrillic_el, 1 },
	{ "д", 0, XKB_KEY_Cyrillic_de, 1 },
	{ "ж", 0, XKB_KEY_Cyrillic_zhe, 1 },
	{ "ю", 0, XKB_KEY_Cyrillic_yu, 1 },

	{ 0 }, /* New row */

	{ "123", 0, XKB_KEY_Mode_switch, 1 },
	{ "я", 0, XKB_KEY_Cyrillic_ya, 1 },
	{ "ч", 0, XKB_KEY_Cyrillic_che, 1 },
	{ "с", 0, XKB_KEY_Cyrillic_es, 1 },
	{ "м", 0, XKB_KEY_Cyrillic_em, 1 },
	{ "и", 0, XKB_KEY_Cyrillic_i, 1 },
	{ "т", 0, XKB_KEY_Cyrillic_te, 1 },
	{ "ь", 0, XKB_KEY_Cyrillic_softsign, 1 },
	{ "б", 0, XKB_KEY_Cyrillic_be, 1 },
	{ "⌫Bksp", 0, XKB_KEY_BackSpace, 2 },

	{ 0 }, /* New row */
	{ "↺", 0, XKB_KEY_Cancel, 1},
	{ "Shift", 0, XKB_KEY_Shift_L, 2 },
	{ "Ctrl", 0, XKB_KEY_Control_L, 1 },
	{ "Alt", 0, XKB_KEY_Alt_L, 1 },
	{ "", 0, XKB_KEY_space, 2 },
	{ "↓", 0, XKB_KEY_Down, 1 },
	{ "↑", 0, XKB_KEY_Up, 1 },
	{ "↲ Enter", 0, XKB_KEY_Return, 2 },
};

static Key keys_dialer[KEYS] = {
	{ "Esc", 0, XKB_KEY_Escape, 1 },
	{ "1", "!" , XKB_KEY_1, 1 },
	{ "2", "@", XKB_KEY_2, 1 },
	{ "3", "#", XKB_KEY_3, 1 },
	{ "⌫Bksp", 0, XKB_KEY_BackSpace, 2 },
	{ 0 }, /* New row */

	{ "Shift", 0, XKB_KEY_Shift_L, 1 },
	{ "4", "$", XKB_KEY_4, 1 },
	{ "5", "%", XKB_KEY_5, 1 },
	{ "6", "^", XKB_KEY_6, 1 },
	{ "-", "_", XKB_KEY_minus, 1 },
	{ ",", "<", XKB_KEY_comma, 1 },
	{ 0 }, /* New row */

	{ "abc", 0, XKB_KEY_Mode_switch, 1 },
	{ "7", "&", XKB_KEY_7, 1 },
	{ "8", "*", XKB_KEY_8, 1 },
	{ "9", "(", XKB_KEY_9, 1 },
	{ "=", "+", XKB_KEY_equal, 1 },
	{ "/", "?", XKB_KEY_slash, 1 },
	{ 0 }, /* New row */

	{ "↺", 0, XKB_KEY_Cancel, 1},
	{ "", 0, XKB_KEY_space, 1 },
	{ "0", ")", XKB_KEY_0, 1 },
	{ ".", ">", XKB_KEY_period, 1 },
	{ "↲ Enter", 0, XKB_KEY_Return, 2},
	{ 0 }, /* New row */
	{ 0 }, /* Last item (double 0) */
};

#define LAYERS 5
static char* layer_names[LAYERS] = {
	"en",
	"symbols",
	"navigation",
	"dialer",
	"ru",
};

static Key* available_layers[LAYERS] = {
	keys_en,
	keys_symbols,
	keys_navigation,
	keys_dialer,
	keys_ru
};


Buttonmod buttonmods[] = {
		{ XKB_KEY_Shift_L, BTN_RIGHT },
		{ XKB_KEY_Alt_L, BTN_MIDDLE },
};
