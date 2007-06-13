# Makefile for PDCurses library for SDL

PDCURSES_SRCDIR	= ..

osdir		= .
srcdir		= $(PDCURSES_SRCDIR)/pdcurses
demodir		= $(PDCURSES_SRCDIR)/demos

PDCURSES_CURSES_H	=$(PDCURSES_SRCDIR)/curses.h
PDCURSES_CURSPRIV_H	=$(PDCURSES_SRCDIR)/curspriv.h
PDCURSES_HEADERS	=$(PDCURSES_CURSES_H) $(PDCURSES_CURSPRIV_H)
PDCURSES_SDL_H		=$(osdir)/pdcsdl.h

CFLAGS		= -O2

CPPFLAGS	= -I$(PDCURSES_SRCDIR) `sdl-config --cflags`

BUILD		= gcc -c $(CFLAGS) $(CPPFLAGS)

LINK		= gcc
LDFLAGS		= $(LIBCURSES) `sdl-config --libs`

RANLIB		= ranlib

LIBCURSES	= libpdcurses.a

LIB_DEPS        = -L$(PDCURSES_SRCDIR)/sdl1 -lpdcurses

PDCLIBS		= $(LIBCURSES)

DEMOS		= firework newdemo ptest rain testcurs tuidemo worm xmas
DEMOOBJS	= firework.o newdemo.o ptest.o rain.o testcurs.o tui.o \
tuidemo.o worm.o xmas.o

#########################################################################
all:	$(PDCLIBS) $(DEMOS)

clean:
	-rm -rf *.o trace $(PDCLIBS) $(DEMOS)

demos:	$(DEMOS)

#------------------------------------------------------------------------

LIBOBJS = addch.o addchstr.o addstr.o attr.o beep.o bkgd.o border.o \
clear.o color.o delch.o deleteln.o deprec.o getch.o getstr.o getyx.o \
inch.o inchstr.o initscr.o inopts.o insch.o insstr.o instr.o kernel.o \
keyname.o mouse.o move.o outopts.o overlay.o pad.o panel.o printw.o \
refresh.o scanw.o scr_dump.o scroll.o slk.o termattr.o terminfo.o \
touch.o util.o window.o debug.o

PDCOBJS = pdcclip.o pdcdisp.o pdcgetsc.o pdckbd.o pdcscrn.o pdcsetsc.o \
pdcutil.o

$(LIBCURSES) : $(LIBOBJS) $(PDCOBJS)
	ar rv $@ $?
	-$(RANLIB) $@

$(LIBOBJS) $(PDCOBJS) : $(PDCURSES_HEADERS)
$(PDCOBJS) : $(PDCURSES_SDL_H)
$(DEMOOBJS) : $(PDCURSES_CURSES_H)
$(DEMOS) : $(LIBCURSES)
terminfo.o: $(TERM_HEADER)

addch.o: $(srcdir)/addch.c
	$(BUILD) $(srcdir)/addch.c

addchstr.o: $(srcdir)/addchstr.c
	$(BUILD) $(srcdir)/addchstr.c

addstr.o: $(srcdir)/addstr.c
	$(BUILD) $(srcdir)/addstr.c

attr.o: $(srcdir)/attr.c
	$(BUILD) $(srcdir)/attr.c

beep.o: $(srcdir)/beep.c
	$(BUILD) $(srcdir)/beep.c

bkgd.o: $(srcdir)/bkgd.c
	$(BUILD) $(srcdir)/bkgd.c

border.o: $(srcdir)/border.c
	$(BUILD) $(srcdir)/border.c

clear.o: $(srcdir)/clear.c
	$(BUILD) $(srcdir)/clear.c

color.o: $(srcdir)/color.c
	$(BUILD) $(srcdir)/color.c

delch.o: $(srcdir)/delch.c
	$(BUILD) $(srcdir)/delch.c

deleteln.o: $(srcdir)/deleteln.c
	$(BUILD) $(srcdir)/deleteln.c

deprec.o: $(srcdir)/deprec.c
	$(BUILD) $(srcdir)/deprec.c

getch.o: $(srcdir)/getch.c
	$(BUILD) $(srcdir)/getch.c

getstr.o: $(srcdir)/getstr.c
	$(BUILD) $(srcdir)/getstr.c

getyx.o: $(srcdir)/getyx.c
	$(BUILD) $(srcdir)/getyx.c

inch.o: $(srcdir)/inch.c
	$(BUILD) $(srcdir)/inch.c

inchstr.o: $(srcdir)/inchstr.c
	$(BUILD) $(srcdir)/inchstr.c

initscr.o: $(srcdir)/initscr.c
	$(BUILD) $(srcdir)/initscr.c

inopts.o: $(srcdir)/inopts.c
	$(BUILD) $(srcdir)/inopts.c

insch.o: $(srcdir)/insch.c
	$(BUILD) $(srcdir)/insch.c

insstr.o: $(srcdir)/insstr.c
	$(BUILD) $(srcdir)/insstr.c

instr.o: $(srcdir)/instr.c
	$(BUILD) $(srcdir)/instr.c

kernel.o: $(srcdir)/kernel.c
	$(BUILD) $(srcdir)/kernel.c

keyname.o: $(srcdir)/keyname.c
	$(BUILD) $(srcdir)/keyname.c

mouse.o: $(srcdir)/mouse.c
	$(BUILD) $(srcdir)/mouse.c

move.o: $(srcdir)/move.c
	$(BUILD) $(srcdir)/move.c

outopts.o: $(srcdir)/outopts.c
	$(BUILD) $(srcdir)/outopts.c

overlay.o: $(srcdir)/overlay.c
	$(BUILD) $(srcdir)/overlay.c

pad.o: $(srcdir)/pad.c
	$(BUILD) $(srcdir)/pad.c

panel.o: $(srcdir)/panel.c $(PDCURSES_SRCDIR)/panel.h
	$(BUILD) $(srcdir)/panel.c

printw.o: $(srcdir)/printw.c
	$(BUILD) $(srcdir)/printw.c

refresh.o: $(srcdir)/refresh.c
	$(BUILD) $(srcdir)/refresh.c

scanw.o: $(srcdir)/scanw.c
	$(BUILD) $(srcdir)/scanw.c

scr_dump.o: $(srcdir)/scr_dump.c
	$(BUILD) $(srcdir)/scr_dump.c

scroll.o: $(srcdir)/scroll.c
	$(BUILD) $(srcdir)/scroll.c

slk.o: $(srcdir)/slk.c
	$(BUILD) $(srcdir)/slk.c

termattr.o: $(srcdir)/termattr.c
	$(BUILD) $(srcdir)/termattr.c

terminfo.o: $(srcdir)/terminfo.c
	$(BUILD) $(srcdir)/terminfo.c

touch.o: $(srcdir)/touch.c
	$(BUILD) $(srcdir)/touch.c

util.o: $(srcdir)/util.c
	$(BUILD) $(srcdir)/util.c

window.o: $(srcdir)/window.c
	$(BUILD) $(srcdir)/window.c

debug.o: $(srcdir)/debug.c
	$(BUILD) $(srcdir)/debug.c


pdcclip.o: $(osdir)/pdcclip.c
	$(BUILD) $(osdir)/pdcclip.c

pdcdisp.o: $(osdir)/pdcdisp.c
	$(BUILD) $(osdir)/pdcdisp.c

pdcgetsc.o: $(osdir)/pdcgetsc.c
	$(BUILD) $(osdir)/pdcgetsc.c

pdckbd.o: $(osdir)/pdckbd.c
	$(BUILD) $(osdir)/pdckbd.c

pdcscrn.o: $(osdir)/pdcscrn.c
	$(BUILD) $(osdir)/pdcscrn.c

pdcsetsc.o: $(osdir)/pdcsetsc.c
	$(BUILD) $(osdir)/pdcsetsc.c

pdcutil.o: $(osdir)/pdcutil.c
	$(BUILD) $(osdir)/pdcutil.c

#------------------------------------------------------------------------

firework: firework.o
	$(LINK) firework.o -o $@ $(LDFLAGS)

newdemo: newdemo.o
	$(LINK) newdemo.o -o $@ $(LDFLAGS)

ptest: ptest.o
	$(LINK) ptest.o -o $@ $(LDFLAGS)

rain: rain.o
	$(LINK) rain.o -o $@ $(LDFLAGS)

testcurs: testcurs.o
	$(LINK) testcurs.o -o $@ $(LDFLAGS)

tuidemo: tuidemo.o tui.o
	$(LINK) tui.o tuidemo.o -o $@ $(LDFLAGS)

worm: worm.o
	$(LINK) worm.o -o $@ $(LDFLAGS)

xmas: xmas.o
	$(LINK) xmas.o -o $@ $(LDFLAGS)


firework.o: $(demodir)/firework.c
	$(BUILD) $(demodir)/firework.c

newdemo.o: $(demodir)/newdemo.c
	$(BUILD) $(demodir)/newdemo.c

ptest.o: $(demodir)/ptest.c $(PDCURSES_SRCDIR)/panel.h
	$(BUILD) $(demodir)/ptest.c

rain.o: $(demodir)/rain.c
	$(BUILD) $(demodir)/rain.c

testcurs.o: $(demodir)/testcurs.c
	$(BUILD) $(demodir)/testcurs.c

tui.o: $(demodir)/tui.c $(demodir)/tui.h
	$(BUILD) $(demodir)/tui.c

tuidemo.o: $(demodir)/tuidemo.c
	$(BUILD) $(demodir)/tuidemo.c

worm.o: $(demodir)/worm.c
	$(BUILD) $(demodir)/worm.c

xmas.o: $(demodir)/xmas.c
	$(BUILD) $(demodir)/xmas.c

#
# This section provides for compiling and linking the
# ncurses test programs.
#
ncurses_testdir	= $(HOME)/ncurses-5.6/test

NCURSES_TESTS	= bs gdc hanoi knight tclock ncurses

ncurses_tests: $(NCURSES_TESTS)

ncurses_clean:
	-rm -f *.o trace $(NCURSES_TESTS)

NCFLAGS		= -I. -I$(ncurses_testdir)

bs: bs.o $(LIBCURSES)
	$(LINK) bs.o -o $@ $(LDFLAGS)

gdc: gdc.o $(LIBCURSES)
	$(LINK) gdc.o -o $@ $(LDFLAGS)

hanoi: hanoi.o $(LIBCURSES)
	$(LINK) hanoi.o -o $@ $(LDFLAGS)

knight: knight.o $(LIBCURSES)
	$(LINK) knight.o -o $@ $(LDFLAGS)

tclock: tclock.o $(LIBCURSES)
	$(LINK) tclock.o -o $@ $(LDFLAGS) -lm

view: view.o $(LIBCURSES)
	$(LINK) view.o -o $@ $(LDFLAGS)

ncurses: ncurses.o $(LIBCURSES)
	$(LINK) ncurses.o -o $@ $(LDFLAGS)

bs.o: $(ncurses_testdir)/bs.c $(PDCURSES_CURSES_H)
	$(BUILD) $(NCFLAGS) $(ncurses_testdir)/bs.c

gdc.o: $(ncurses_testdir)/gdc.c $(PDCURSES_CURSES_H)
	$(BUILD) $(NCFLAGS) $(ncurses_testdir)/gdc.c

hanoi.o: $(ncurses_testdir)/hanoi.c $(PDCURSES_CURSES_H)
	$(BUILD) $(NCFLAGS) $(ncurses_testdir)/hanoi.c

knight.o: $(ncurses_testdir)/knight.c $(PDCURSES_CURSES_H)
	$(BUILD) $(NCFLAGS) $(ncurses_testdir)/knight.c

tclock.o: $(ncurses_testdir)/tclock.c $(PDCURSES_CURSES_H)
	$(BUILD) $(NCFLAGS) $(ncurses_testdir)/tclock.c

view.o: $(ncurses_testdir)/view.c $(PDCURSES_CURSES_H)
	$(BUILD) $(NCFLAGS) $(ncurses_testdir)/view.c

ncurses.o: $(ncurses_testdir)/ncurses.c $(PDCURSES_CURSES_H)
	$(BUILD) $(NCFLAGS) $(ncurses_testdir)/ncurses.c