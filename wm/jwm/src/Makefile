CC = musl-gcc
CFLAGS = -I/usr/include/freetype2 -fno-link-libatomic -I/tmp/kyronix-x11-include -I/usr/include/libpng16   -DLOCALEDIR=\"/usr/local/share/locale\"
CPPFLAGS = 
LDFLAGS = -Wl,--rpath-link,/usr/lib64 -L/usr/lib64 -lX11 -lpng16 -ljpeg -lXrender -lX11 -lXpm -lXext -lXmu -lXinerama  
BINDIR = $(DESTDIR)/usr/local/bin

VPATH=.:os

OBJECTS = action.o background.o binding.o border.o button.o client.o \
   clientlist.o clock.o color.o command.o confirm.o cursor.o debug.o \
   default.o desktop.o dock.o event.o error.o font.o grab.o gradient.o \
   group.o help.o hint.o icon.o image.o lex.o main.o match.o menu.o misc.o \
   move.o outline.o pager.o parse.o place.o popup.o render.o resize.o \
   root.o screen.o settings.o spacer.o status.o swallow.o taskbar.o \
   timing.o tray.o traybutton.o winmenu.o

EXE = jwm

.SUFFIXES: .o .h .c

all: $(EXE)

install: all
	install -d $(BINDIR)
	install $(EXE) $(BINDIR)/$(EXE)

install-strip: install
	strip $(BINDIR)/$(EXE)

uninstall:
	rm -f $(BINDIR)/$(EXE)

$(EXE): $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS) $(LDFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $<

$(OBJECTS): *.h ../config.h

clean:
	rm -f $(OBJECTS) $(EXE) core

