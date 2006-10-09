/************************************************************************ 
 * This file is part of PDCurses. PDCurses is public domain software;	*
 * you may use it for any purpose. This software is provided AS IS with	*
 * NO WARRANTY whatsoever.						*
 *									*
 * If you use PDCurses in an application, an acknowledgement would be	*
 * appreciated, but is not mandatory. If you make corrections or	*
 * enhancements to PDCurses, please forward them to the current		*
 * maintainer for the benefit of other users.				*
 *									*
 * No distribution of modified PDCurses code may be made under the name	*
 * "PDCurses", except by the current maintainer. (Although PDCurses is	*
 * public domain, the name is a trademark.)				*
 *									*
 * See the file maintain.er for details of the current maintainer.	*
 ************************************************************************/

#include "pdcos2.h"

#if defined(CURSES__32BIT__) || defined(__IBMC__) || defined(__TURBOC__)
# include <signal.h>
#else
# define INCL_DOSSIGNALS
# define INCL_NOCOMMON
# include <bsedos.h>
#endif

#ifdef EMXVIDEO
# include <termios.h>
static int tahead = -1;
#else
static KBDINFO kbdinfo;		/* default keyboard mode */
#endif

RCSID("$Id: pdckbd.c,v 1.40 2006/10/09 00:11:14 wmcbrine Exp $");

/************************************************************************
 *   Table for key code translation of function keys in keypad mode	*
 *   These values are for strict IBM keyboard compatibles only		*
 ************************************************************************/

static int kptab[] =
{
	/* Normal Function Keys */
	0x3b, KEY_F(1), 0x3c, KEY_F(2), 0x3d, KEY_F(3), 0x3e, KEY_F(4),
	0x3f, KEY_F(5), 0x40, KEY_F(6), 0x41, KEY_F(7), 0x42, KEY_F(8),
	0x43, KEY_F(9), 0x44, KEY_F(10),

	/* Normal Keypad */
	0x47, KEY_HOME,  0x48, KEY_UP,    0x49, KEY_PPAGE, 0x4b, KEY_LEFT, 
	0x4c, KEY_B2,    0x4d, KEY_RIGHT, 0x4f, KEY_END,   0x50, KEY_DOWN, 
	0x51, KEY_NPAGE, 0x52, KEY_IC,   0x53, KEY_DC,

	/* Shifted Keypad */
	0xb0, KEY_SHOME, 0xb1, KEY_SUP,    0xb2, KEY_SPREVIOUS,
	0xb3, KEY_SLEFT, 0xb4, KEY_SRIGHT, 0xb5, KEY_SEND,
	0xb6, KEY_SDOWN, 0xb7, KEY_SNEXT,  0xb8, KEY_SIC,  0xb9, KEY_SDC,

	/* Shft-Function Keys */
	0x54, KEY_F(13), 0x55, KEY_F(14), 0x56, KEY_F(15), 0x57, KEY_F(16),
	0x58, KEY_F(17), 0x59, KEY_F(18), 0x5a, KEY_F(19), 0x5b, KEY_F(20),
	0x5c, KEY_F(21), 0x5d, KEY_F(22),

	/* Ctl-Function Keys */
	0x5e, KEY_F(25), 0x5f, KEY_F(26), 0x60, KEY_F(27), 0x61, KEY_F(28),
	0x62, KEY_F(29), 0x63, KEY_F(30), 0x64, KEY_F(31), 0x65, KEY_F(32),
	0x66, KEY_F(33), 0x67, KEY_F(34),

	/* Alt-Function Keys */
	0x68, KEY_F(37), 0x69, KEY_F(38), 0x6a, KEY_F(39), 0x6b, KEY_F(40),
	0x6c, KEY_F(41), 0x6d, KEY_F(42), 0x6e, KEY_F(43), 0x6f, KEY_F(44),
	0x70, KEY_F(45), 0x71, KEY_F(46),

	/* Control-Keypad */
	0x77, CTL_HOME,  0x84, CTL_PGUP,  0x73, CTL_LEFT,
	0x74, CTL_RIGHT, 0x75, CTL_END,   0x76, CTL_PGDN,

	/* Alt-Numbers */
	0x78, ALT_1, 0x79, ALT_2, 0x7a, ALT_3, 0x7b, ALT_4, 0x7c, ALT_5,
	0x7d, ALT_6, 0x7e, ALT_7, 0x7f, ALT_8, 0x80, ALT_9, 0x81, ALT_0,

	/* Extended codes */
	0x85, KEY_F(11), 0x86, KEY_F(12), 0x87, KEY_F(23), 0x88, KEY_F(24),
	0x89, KEY_F(35), 0x8a, KEY_F(36), 0x8b, KEY_F(47), 0x8c, KEY_F(48),
	0x03, 0, /* NULL */

#ifdef NUMKEYPAD
	0xff, (int)'/',     0x0d, (int)'\n',
	0xfa, (int)'*',     0xfd, (int)'-',      0xfb, (int)'+',
#else
	0xff, PADSLASH,     0x0d, PADENTER,      
	0xfa, PADSTAR,      0xfd, PADMINUS,      0xfb, PADPLUS,
#endif

	0x0a, CTL_PADENTER,
	0xa6, ALT_PADENTER, 0x53, (int)'.',      0xfc, CTL_ENTER,
	0x93, CTL_DEL,      0x8f, CTL_PADCENTER, 0x90, CTL_PADPLUS,
	0x8e, CTL_PADMINUS, 0x95, CTL_PADSLASH,  0x96, CTL_PADSTAR,
	0x4e, ALT_PADPLUS,  0x4a, ALT_PADMINUS,  0xa4, ALT_PADSLASH,
	0x37, ALT_PADSTAR,  0x92, CTL_INS,       0xa2, ALT_INS,
	0xa3, ALT_DEL,      0x8d, CTL_UP,        0x91, CTL_DOWN,
	0x94, CTL_TAB,      0xa5, ALT_TAB,       0x82, ALT_MINUS,
	0x83, ALT_EQUAL,    0x99, ALT_PGUP,      0xa1, ALT_PGDN,
	0x9f, ALT_END,      0x98, ALT_UP,        0xa0, ALT_DOWN,
	0x9d, ALT_RIGHT,    0x9b, ALT_LEFT,      0x1c, ALT_ENTER,
	0x97, ALT_HOME,     0x01, ALT_ESC,       0x0e, ALT_BKSP,
	0x29, ALT_BQUOTE,   0x1a, ALT_LBRACKET,  0x1b, ALT_RBRACKET,
	0x27, ALT_SEMICOLON,0x28, ALT_FQUOTE,    0x33, ALT_COMMA,
	0x34, ALT_STOP,     0x35, ALT_FSLASH,    0x2b, ALT_BSLASH,

	/* Alt-Alphabet */
	0x1e, ALT_A, 0x30, ALT_B, 0x2e, ALT_C, 0x20, ALT_D,
	0x12, ALT_E, 0x21, ALT_F, 0x22, ALT_G, 0x23, ALT_H,
	0x17, ALT_I, 0x24, ALT_J, 0x25, ALT_K, 0x26, ALT_L,
	0x32, ALT_M, 0x31, ALT_N, 0x18, ALT_O, 0x19, ALT_P,
	0x10, ALT_Q, 0x13, ALT_R, 0x1f, ALT_S, 0x14, ALT_T,
	0x16, ALT_U, 0x2f, ALT_V, 0x11, ALT_W, 0x2d, ALT_X,
	0x15, ALT_Y, 0x2c, ALT_Z, 0x0f, KEY_BTAB, 0x100, -1
};

/* End of kptab[] */

unsigned long pdc_key_modifiers = 0L;

/*man-start**************************************************************

  PDC_get_input_fd()    - Get file descriptor used for PDCurses input

  PDCurses Description:
	This is a private PDCurses routine.

	This routine will return the file descriptor that PDCurses reads
	its input from. It can be used for select().

  PDCurses Return Value:
	Returns a file descriptor.

  Portability:
	PDCurses  int PDC_get_input_fd(void);

**man-end****************************************************************/

unsigned long PDC_get_input_fd(void)
{
	PDC_LOG(("PDC_get_input_fd() - called\n"));

	return (unsigned long)fileno(stdin);
}

#ifndef EMXVIDEO

void PDC_get_keyboard_info(void)
{
	PDC_LOG(("PDC_get_keyboard_info() - called\n"));

	kbdinfo.cb = sizeof(kbdinfo);
	KbdGetStatus(&kbdinfo, 0);

	PDC_LOG(("PDC_get_keyboard_info(). cb: %x, fsMask: %x, "
		"chTurnAround: %x, fsInterim: %x, fsState: %x\n",
		kbdinfo.cb, kbdinfo.fsMask, kbdinfo.chTurnAround, 
		kbdinfo.fsInterim, kbdinfo.fsState));
}

void PDC_set_keyboard_default(void)
{
	PDC_LOG(("PDC_set_keyboard_default(). cb: %x, fsMask: %x, "
		"chTurnAround: %x, fsInterim: %x, fsState: %x\n",
		kbdinfo.cb, kbdinfo.fsMask, kbdinfo.chTurnAround, 
		kbdinfo.fsInterim, kbdinfo.fsState));

	KbdSetStatus(&kbdinfo, 0);
}

#endif /* ifndef EMXVIDEO */

void PDC_set_keyboard_binary(bool on)
{
	PDC_LOG(("PDC_set_keyboard_binary() - called\n"));

#ifndef EMXVIDEO
	PDC_LOG(("PDC_set_keyboard_binary() - before. cb: %x, fsMask: %x, "
		"chTurnAround: %x, fsInterim: %x, fsState: %x\n",
		kbdinfo.cb, kbdinfo.fsMask, kbdinfo.chTurnAround, 
		kbdinfo.fsInterim, kbdinfo.fsState));

	if (on)
	{
		kbdinfo.fsMask &= ~KEYBOARD_ASCII_MODE;
		kbdinfo.fsMask |= KEYBOARD_BINARY_MODE;
	}
	else
	{
		kbdinfo.fsMask &= ~KEYBOARD_BINARY_MODE;
		kbdinfo.fsMask |= KEYBOARD_ASCII_MODE;
	}

	KbdSetStatus(&kbdinfo, 0);

	PDC_LOG(("PDC_set_keyboard_binary() - after. cb: %x, fsMask: %x, "
		"chTurnAround: %x, fsInterim: %x, fsState: %x\n",
		kbdinfo.cb, kbdinfo.fsMask, kbdinfo.chTurnAround, 
		kbdinfo.fsInterim, kbdinfo.fsState));
#endif
}

/*man-start**************************************************************

  PDC_check_bios_key()  - Check BIOS key data area for input

  PDCurses Description:
	This is a private PDCurses routine.

	This routine will check the BIOS for any indication that
	keystrokes are pending.

  PDCurses Return Value:
	Returns 1 if a keyboard character is available, 0 otherwise.

  Portability:
	PDCurses  bool PDC_check_bios_key(void);

**man-end****************************************************************/

bool PDC_check_bios_key(void)
{
#if !defined(_MSC_VER) && !defined(EMXVIDEO)
	KBDKEYINFO keyInfo = {0};
#endif
	PDC_LOG(("PDC_check_bios_key() - called\n"));

#ifdef EMXVIDEO
	if (tahead == -1)		/* Nothing typed yet */
	{                    
		tahead = _read_kbd(0, 0, 0);

		/* Read additional */

		if (tahead == 0)	
			tahead = _read_kbd(0, 1, 0) << 8;
	}

	return (tahead != -1);
#else
# ifndef _MSC_VER
	KbdPeek(&keyInfo, 0);   /* peek at keyboard  */
	return (keyInfo.fbStatus != 0);
# else
	return kbhit();
# endif
#endif
}         

/*man-start**************************************************************

  PDC_get_bios_key() - Returns the next key available from the BIOS.

  PDCurses Description:
	This is a private PDCurses routine.

	Returns the next key code struck at the keyboard. If the low 8
	bits are 0, the upper bits contain the extended character
	code. If bit 0-7 are non-zero, the upper bits = 0.

  PDCurses Return Value:
	This function returns OK on success and ERR on error.

  Portability:
	PDCurses  int PDC_get_bios_key(void);

**man-end****************************************************************/

int PDC_get_bios_key(void)
{
	int ascii, scan, key;
#ifndef EMXVIDEO
	KBDKEYINFO keyInfo = {0};
#endif
	PDC_LOG(("PDC_get_bios_key() - called\n"));

#ifdef EMXVIDEO
	if (tahead == -1)
	{
		tahead = _read_kbd(0, 1, 0);

		/* Read additional */

		if (tahead == 0)
			tahead = _read_kbd(0, 1, 0) << 8;
	}

	ascii = tahead & 0xff;
	scan  = tahead >> 8;
	pdc_key_modifiers = 0L;

	tahead = -1;
#else
	KbdCharIn(&keyInfo, IO_WAIT, 0);	/* get a character */

	ascii = keyInfo.chChar;
	scan = keyInfo.chScan;
	pdc_key_modifiers = 0L;

	if (SP->save_key_modifiers)
	{
		if (keyInfo.fsState & KBDSTF_ALT)
			pdc_key_modifiers |= PDC_KEY_MODIFIER_ALT;

		if (keyInfo.fsState & KBDSTF_CONTROL)
			pdc_key_modifiers |= PDC_KEY_MODIFIER_CONTROL;

		if (keyInfo.fsState & KBDSTF_NUMLOCK_ON)
			pdc_key_modifiers |= PDC_KEY_MODIFIER_NUMLOCK;

		if (keyInfo.fsState & KBDSTF_LEFTSHIFT
		    || keyInfo.fsState & KBDSTF_RIGHTSHIFT)
			pdc_key_modifiers |= PDC_KEY_MODIFIER_SHIFT;
	}
#endif
	if (scan == 0x1c && ascii == 0x0a)  /* ^Enter */
		key = (int)0xfc00;
	else if ((scan == 0x03 && ascii == 0x00)  /* ^@ - Null */
		|| (scan == 0xe0 && ascii == 0x0d)  /* PadEnter */
		|| (scan == 0xe0 && ascii == 0x0a)) /* ^PadEnter */
			key = ascii << 8;
	else if ((scan == 0x37 && ascii == 0x2a)  /* Star */
		|| (scan == 0x4a && ascii == 0x2d)  /* Minus */
		|| (scan == 0x4e && ascii == 0x2b)  /* Plus */
		|| (scan == 0xe0 && ascii == 0x2f)) /* Slash */
			key = ((ascii & 0x0f) | 0xf0) << 8;
	else if (ascii == 0xe0 && scan == 0x47 && pdc_key_modifiers & 
		PDC_KEY_MODIFIER_SHIFT) /* Shift Home */
			key = (int)0xb000;
	else if (ascii == 0xe0 && scan == 0x48 && pdc_key_modifiers & 
		PDC_KEY_MODIFIER_SHIFT) /* Shift Up */
			key = (int)0xb100;
	else if (ascii == 0xe0 && scan == 0x49 && pdc_key_modifiers & 
		PDC_KEY_MODIFIER_SHIFT) /* Shift PgUp */
			key = (int)0xb200;
	else if (ascii == 0xe0 && scan == 0x4b && pdc_key_modifiers & 
		PDC_KEY_MODIFIER_SHIFT) /* Shift Left */
			key = (int)0xb300;
	else if (ascii == 0xe0 && scan == 0x4d && pdc_key_modifiers & 
		PDC_KEY_MODIFIER_SHIFT) /* Shift Right */
			key = (int)0xb400;
	else if (ascii == 0xe0 && scan == 0x4f && pdc_key_modifiers & 
		PDC_KEY_MODIFIER_SHIFT) /* Shift End */
			key = (int)0xb500;
	else if (ascii == 0xe0 && scan == 0x50 && pdc_key_modifiers & 
		PDC_KEY_MODIFIER_SHIFT) /* Shift Down */
			key = (int)0xb600;
	else if (ascii == 0xe0 && scan == 0x51 && pdc_key_modifiers & 
		PDC_KEY_MODIFIER_SHIFT) /* Shift PgDn */
			key = (int)0xb700;
	else if (ascii == 0xe0 && scan == 0x52 && pdc_key_modifiers & 
		PDC_KEY_MODIFIER_SHIFT) /* Shift Ins */
			key = (int)0xb800;
	else if (ascii == 0xe0 && scan == 0x53 && pdc_key_modifiers & 
		PDC_KEY_MODIFIER_SHIFT) /* Shift Del */
			key = (int)0xb900;
	else if (ascii == 0x00 || ascii == 0xe0)
		key = scan << 8;
	else
		key = ascii;

	PDC_LOG(("PDC_get_bios_key() - returned: %d(0x%x), "
		"ascii: %d(0x%x) scan: %d(0x%x)\n",
		key, key, ascii, ascii, scan, scan));

	return key;
}

/*man-start**************************************************************

  PDC_get_ctrl_break()  - return OS control break state

  PDCurses Description:
	This is a private PDCurses routine.

	Returns the current OS Control Break Check state.

  PDCurses Return Value:
	This function returns TRUE if the Control Break Check is enabled 
	otherwise FALSE is returned.

  Portability:
	PDCurses  bool PDC_get_ctrl_break(void);

**man-end****************************************************************/

bool PDC_get_ctrl_break(void)
{
#if defined(CURSES__32BIT__) || defined(__IBMC__) || defined(__TURBOC__)
# ifdef __TURBOC__
	void __cdecl (*oldAction) (int);
# else
	void (*oldAction) (int);
# endif
#endif
	PDC_LOG(("PDC_get_ctrl_break() - called\n"));

#if defined(CURSES__32BIT__) || defined(__IBMC__) || defined(__TURBOC__)

	oldAction = signal(SIGINT, SIG_DFL);

	if (oldAction == SIG_ERR)
		return FALSE;
	else
		signal(SIGINT, oldAction);

	return (oldAction != SIG_IGN);
#else
	PFNSIGHANDLER oldHandler, oldHandler1;
	USHORT oldAction, oldAction1;

	/* get the current state, and set to ignore */

	DosSetSigHandler((PFNSIGHANDLER) NULL, &oldHandler, &oldAction,
		SIGA_IGNORE, SIG_CTRLBREAK);

	/* restore the previous state */

	DosSetSigHandler(oldHandler, &oldHandler1, &oldAction1,
		oldAction, SIG_CTRLBREAK);

	return (oldAction != SIGA_IGNORE);
#endif
}

/*man-start**************************************************************

  PDC_set_ctrl_break()  - Enables/Disables the host OS BREAK key check.

  PDCurses Description:
	This is a private PDCurses routine.

	Enables/Disables the host OS BREAK key check. If the supplied 
	setting is TRUE, this enables CTRL/C and CTRL/BREAK to abort the 
	process. If FALSE, CTRL/C and CTRL/BREAK are ignored.

  PDCurses Return Value:
	This function returns OK on success and ERR on error.

  Portability:
	PDCurses  int PDC_set_ctrl_break(bool setting);

**man-end****************************************************************/

int PDC_set_ctrl_break(bool setting)
{
	PDC_LOG(("PDC_set_ctrl_break() - called. Setting: %d\n", setting));

#if defined(CURSES__32BIT__) || defined(__IBMC__) || defined(__TURBOC__)
	signal(SIGINT, setting ? SIG_DFL : SIG_IGN);
	signal(SIGBREAK, setting ? SIG_DFL : SIG_IGN);
#else
	PFNSIGHANDLER oldHandler;
	USHORT oldAction, Action;

	/* turn off control C checking */

	if (setting)
		Action = SIGA_KILL;
	else
		Action = SIGA_IGNORE;

	DosSetSigHandler((PFNSIGHANDLER) NULL, &oldHandler, &oldAction,
		Action, SIG_CTRLBREAK);
	DosSetSigHandler((PFNSIGHANDLER) NULL, &oldHandler, &oldAction,
		Action, SIG_CTRLC);
#endif
	return OK;
}

/*man-start**************************************************************

  PDC_validchar() - validate/translate passed character
  
  PDCurses Description:
	This is a private PDCurses function.
  
	Checks that 'c' is a valid character, and if so returns it,
	with function key translation applied if 'w' has keypad mode
	set.  If char is invalid, returns -1.
  
  PDCurses Return Value:
	This function returns -1 if the passed character is invalid, or
	the WINDOW* 'w' is NULL, or 'w's keypad is not active.
  
	Otherwise, this function returns the PDCurses equivalent of the
	passed character.  See the function key and key macros in
	<curses.h>
  
  Portability:
	PDCurses  int PDC_validchar(int c);

**man-end****************************************************************/

int PDC_validchar(int c)
{
	int *scanp;

	PDC_LOG(("PDC_validchar() - called. c: %d\n", c));

	if (pdc_getch_win == (WINDOW *)NULL)
		return -1;

	/* normal character */

	if ((unsigned int)c < 256)
		return c;

	/* skip if keys if !keypad mode */

	if (!pdc_getch_win->_use_keypad)
		return -1;

	/* Under DOS, extended keys are in the upper byte.  Shift down 
	   for a comparison. */

	c = (c >> 8) & 0xFF;

	for (scanp = kptab; *scanp > 0; scanp++)	
		if (*scanp++ == c)
			return *scanp;

	return -1;		/* not found, invalid */
}

/*man-start**************************************************************

  PDC_flushinp()		- Low-level input flush

  PDCurses Description:
	This is a private PDCurses routine.

	Discards any pending keyboard and mouse input. Called by 
	flushinp().

  Portability:
	PDCurses  void PDC_flushinp(void);

**man-end****************************************************************/

void PDC_flushinp(void)
{
	PDC_LOG(("PDC_flushinp() - called\n"));

#ifdef EMXVIDEO
	tcflush(0, TCIFLUSH);
#else
	KbdFlushBuffer(0);
#endif
}
