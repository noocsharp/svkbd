LAYOUT = mobile-intl

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib

PKG_CONFIG = pkg-config

PIXMANINC = /usr/include/pixman-1
SWCPROTO = /usr/share/swc/swc.xml
VKPROTO = protocols/virtual-keyboard-unstable-v1.xml

# includes and libs
INCS = -I. -I./layouts -I${X11INC} \
	`$(PKG_CONFIG) --cflags fontconfig` \
	`$(PKG_CONFIG) --cflags freetype2` \
	`$(PKG_CONFIG) --cflags pixman-1`
LIBS = -L${X11LIB} -lX11 -lwayland-client -lxkbcommon -lwld -lswc \
	`$(PKG_CONFIG) --libs fontconfig` \
	`$(PKG_CONFIG) --libs freetype2` \
	`$(PKG_CONFIG) --libs pixman-1`

# use system flags
SVKBD_CFLAGS = ${CFLAGS} ${INCS}
SVKBD_LDFLAGS = ${LDFLAGS} ${LIBS}
SVKBD_CPPFLAGS = ${CPPFLAGS} -D_DEFAULT_SOURCE -DVERSION=\"VERSION\" -DLAYOUT=\"layout.${LAYOUT}.h\"
