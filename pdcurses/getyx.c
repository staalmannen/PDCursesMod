/* PDCurses */

#include <curspriv.h>
#include <assert.h>

/*man-start**************************************************************

getyx
-----

### Synopsis

    void getyx(WINDOW *win, int y, int x);
    void getparyx(WINDOW *win, int y, int x);
    void getbegyx(WINDOW *win, int y, int x);
    void getmaxyx(WINDOW *win, int y, int x);

    void getsyx(int y, int x);
    void setsyx(int y, int x);

    int getbegy(const WINDOW *win);
    int getbegx(const WINDOW *win);
    int getcury(const WINDOW *win);
    int getcurx(const WINDOW *win);
    int getpary(const WINDOW *win);
    int getparx(const WINDOW *win);
    int getmaxy(const WINDOW *win);
    int getmaxx(const WINDOW *win);

### Description

   The getyx() macro (defined in curses.h -- the prototypes here are
   merely illustrative) puts the current cursor position of the
   specified window into y and x. getbegyx() and getmaxyx() return the
   starting coordinates and size of the specified window, respectively.
   getparyx() returns the starting coordinates of the parent's window,
   if the specified window is a subwindow; otherwise it sets y and x to
   -1. These are all macros.

   getsyx() gets the coordinates of the virtual screen cursor, and
   stores them in y and x. If leaveok() is TRUE, it returns -1, -1. If
   lines have been removed with ripoffline(), then getsyx() includes
   these lines in its count; so, the returned y and x values should only
   be used with setsyx().

   setsyx() sets the virtual screen cursor to the y, x coordinates. If
   either y or x is -1, leaveok() is set TRUE, else it's set FALSE.

   getsyx() and setsyx() are meant to be used by a library routine that
   manipulates curses windows without altering the position of the
   cursor. Note that getsyx() is defined only as a macro.

   getbegy(), getbegx(), getcurx(), getcury(), getmaxy(), getmaxx(),
   getpary(), and getparx() return the appropriate coordinate or size
   values, or ERR in the case of a NULL window.

### Portability
                             X/Open  ncurses  NetBSD
    getyx                       Y       Y       Y
    getparyx                    Y       Y       Y
    getbegyx                    Y       Y       Y
    getmaxyx                    Y       Y       Y
    getsyx                      -       Y       Y
    setsyx                      -       Y       Y
    getbegy                     -       Y       Y
    getbegx                     -       Y       Y
    getcury                     -       Y       Y
    getcurx                     -       Y       Y
    getpary                     -       Y       Y
    getparx                     -       Y       Y
    getmaxy                     -       Y       Y
    getmaxx                     -       Y       Y

**man-end****************************************************************/

int getbegy(const WINDOW *win)
{
    PDC_LOG(("getbegy() - called\n"));

    assert( win);
    return win ? win->_begy : ERR;
}

int getbegx(const WINDOW *win)
{
    PDC_LOG(("getbegx() - called\n"));

    assert( win);
    return win ? win->_begx : ERR;
}

int getcury(const WINDOW *win)
{
    PDC_LOG(("getcury() - called\n"));

    assert( win);
    return win ? win->_cury : ERR;
}

int getcurx(const WINDOW *win)
{
    PDC_LOG(("getcurx() - called\n"));

    assert( win);
    return win ? win->_curx : ERR;
}

int getpary(const WINDOW *win)
{
    PDC_LOG(("getpary() - called\n"));

    assert( win);
    return win ? win->_pary : ERR;
}

int getparx(const WINDOW *win)
{
    PDC_LOG(("getparx() - called\n"));

    assert( win);
    return win ? win->_parx : ERR;
}

int getmaxy(const WINDOW *win)
{
    PDC_LOG(("getmaxy() - called\n"));

    assert( win);
    return win ? win->_maxy : ERR;
}

int getmaxx(const WINDOW *win)
{
    PDC_LOG(("getmaxx() - called\n"));

    assert( win);
    return win ? win->_maxx : ERR;
}

void setsyx(int y, int x)
{
    PDC_LOG(("setsyx() - called\n"));

    if (curscr)
    {
        curscr->_leaveit = y == -1 || x == -1;

        if (!curscr->_leaveit)
            wmove(curscr, y, x);
    }
}
