/*  awtk.h

		Definitions for the ASCII Windows Tool Kit (AWTK) Library.

		Copyright (c) 2009 by Jose F. D'Silva
		All Rights Reserved.
*/

#ifndef AWTK_H
#define AWTK_H
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <alloc.h>
#include <mem.h>
#include <string.h>
#include "awtypes.h"
#include "bitmanip.h"
//license information
#define ISLICENSED      FALSE
#define PRODUCTID       "0000-0000-0000-0000"
#define LICENSEDTO      "Jose F. D'Silva"
#define COMPANYNAME     "none."

/* version information */
#define AWTK_VERMJ                               (2)
#define AWTK_VERMN                               (0)
#define AWTK_VERRL                               (0)

#define INTR_VIDEO                               (0x10)
/* Textmode Bytes Per Character */
#define BPC_TXT8025                              (2)
/* attribute management */
#define ATTRIBUTEMASK_FG                         (0x0F)
#define ATTRIBUTEMASK_BG                         (0x70)
/* attribute HIBYTE control flags */
#define ATTRIBUTECF_IGNORE                       (0x01)
#define ATTRIBUTECF_TRANSPARENT                  (0x02)
#define ATTRIBUTECF_ROP                          (0x04)
#define ATTRIBUTECF_ERROR                        (0x80)
/* attribute raster operation flags.
	 You should bitwise OR one of these flags with ATTRIBUTECF_ROP.
*/
#define ROP_NOTA                                 (0x01)
#define ROP_NOTS                                 (0x02)
#define ROP_AND                                  (0x08)
#define ROP_XOR                                  (0x10)
#define ROP_OR                                   (0x20)
#define ROP_COPY                                 (0x40)
/* attribute management helpers */
#define GET_ATTRIBUTE_FG(attribute)              ((BYTE) (LOBYTE(attribute) & ATTRIBUTEMASK_FG))
#define GET_ATTRIBUTE_BG(attribute)              ((BYTE) ((LOBYTE(attribute) & ATTRIBUTEMASK_BG) >> 4))
#define MK_ATTRIBUTE(fg, bg)                     ((ATTRIBUTE) ((((BYTE) (bg)) << 4) | ((BYTE) (fg))))
#define ATTRIBUTE_IGNORE                         MAKEWORD(0, ATTRIBUTECF_IGNORE)
/* should attribute be ignored? */
#define IS_IATTRIBUTE(attribute)                 ((bool_t) ((HIBYTE(attribute) & ATTRIBUTECF_IGNORE) == ATTRIBUTECF_IGNORE))
/* transparent attribute */
#define IS_TATTRIBUTE(attribute)                 ((bool_t) ((HIBYTE(attribute) & ATTRIBUTECF_TRANSPARENT) == ATTRIBUTECF_TRANSPARENT))
#define MK_TATTRIBUTE(fg)                        MAKEWORD(((fg) & (0x8F)), ATTRIBUTECF_TRANSPARENT)

#define CENTRESCREEN                             (-1)
#define CENTRESCREENX(wd)                        ((g_awtk_sysinfo.hcontext->viewport.w - (wd)) >> 1)
#define CENTRESCREENY(ht)                        ((g_awtk_sysinfo.hcontext->viewport.h - (ht)) >> 1)
/* video mode setting helpers */
#define GET_CGA8025SEG()                         ((BYTE far*) MK_FP(0xB800,0))
#define GET_MONO8025SEG()                        ((BYTE far*) MK_FP(0xB000,0))
#define set_cgamode()                            set_videomode(CGA8025)
#define set_monomode()                           set_videomode(MONO8025)
/* get pointer to the active context */
#define GET_ACTIVECONTEXT()                      ((HCONTEXT) g_awtk_sysinfo.hcontext)
#define SET_ACTIVECONTEXT(hc)                    g_awtk_sysinfo.hcontext = (hc)
#define context_render(hcontext)                 put_physicalcontext(hcontext)
#define refresh_screen()                         context_render(GET_ACTIVECONTEXT())
#define PSCR_COLS                                (80)
#define PSCR_ROWS                                (25)
/* get pointer to the viewport */
#define GET_VPSEG(hcontext)                      ((BYTE far*) ((hcontext)->vseg + ((hcontext)->viewport.y * ((hcontext)->vw * (hcontext)->bpc)) + ((hcontext)->viewport.x * (hcontext)->bpc)))
/* get pointer to the viewport at (rx,ry) within the viewport. */
#define GET_VPXYSEG(hcontext, rx, ry)            ((BYTE far*) ((hcontext)->vseg + (((hcontext)->viewport.y + (ry)) * ((hcontext)->vw * (hcontext)->bpc)) + (((hcontext)->viewport.x + (rx)) * (hcontext)->bpc)))
/* cursor helpers */
#define cursor_normal()                          cursor_size(6,7)
#define cursor_understrike()                     cursor_size(7,7)
#define cursor_overstrike()                      cursor_size(0,0)
#define cursor_block()                           cursor_size(0,7)
#define cursor_show()                            cursor_normal()
#define cursor_hide()                            cursor_size(1,0)
/* prints flags */
#define PFL_DEFAULT                              (0x0000)
#define PFL_MARGINX                              (0x0001)
#define PFL_NOTRIM                               (0x0002)
#define PFL_CWRAP                                (0x0004)
#define PFL_KEEPXSPC                             (0x0008)
// You can undef this macro and redefine it according to your program needs.
#define PRINTS(rx, ry, s, attr)                  prints((rx),(ry),s,(attr),PFL_DEFAULT)

/* Move a chunk of memory independant of the memory model used.
	 NOTE: movedata() behaves like _fmemcpy() and does not copy overlapping blocks correctly.
	 udf: movemem() behaves like movedata() and will correctly copy overlapping blocks.
*/
#define MEMMOVE(dest,src,n)                      movemem(FP_SEG(src),FP_OFF(src),FP_SEG(dest),FP_OFF(dest),n)
/* move a chunk of 4k memory */
#define MC4K(dest,src)                           MEMMOVE(dest,src,4000)

/*
************************************************************************
* AWTK module specific types: *
************************************************************************
*/

/* The attribute type:
	LOBYTE: color information.
	HIBYTE: control/manipulation flags.
*/
typedef WORD ATTRIBUTE;
/* The viewport type:
	 A rectangular area within the context where rendering is done.
*/
typedef RECT VIEWPORT, *HVIEWPORT;
/* The vector type: (vector is a linear memory of consecutive bytes). */
typedef BYTE far *VSEG;
/* The context type. */
typedef struct context {
	BYTE far *vseg;        /* vector segment. */
	int vw;                /* vector width. */
	int vh;                /* vector height. */
	UINT bpc;              /* bytes per character. */
	VIEWPORT viewport;     /* active viewport within the context. */
} *HCONTEXT;

/* textmodes supported by AWTK */
enum textmodes {AUTODETECT=-1, CGA8025=3, MONO8025=7};

/* margin styles */
//typedef enum margin {MARGINX_LOCK0, MARGINX_LOCKX} MARGIN;

/* AWTK system information structure. */
extern struct awtk_sysinfo {
	HCONTEXT hcontext;         /* handle to the active context. */
	enum textmodes textmode;   /* active text video mode. */
	int previous_videomode;    /* video mode from which the system was started. */
	POINT previous_cursorpos;  /* cursor position when the system became active. */
} g_awtk_sysinfo;

/*
************************************************************************
* AWTK module function prototypes: *
************************************************************************
*/
// These routines manipulate the specified context.
HCONTEXT        context_alloc(HCONTEXT *hc, int vw, int vh, UINT bpc);
void            context_free(HCONTEXT *hc);
HCONTEXT        context_clone(HCONTEXT *hclone, const HCONTEXT hsrc);
void            context_freeclone(HCONTEXT *hclone);
void            context_copy(HCONTEXT hcd, HCONTEXT hcs);
bool_t          context_copyxy(HCONTEXT hcd, const RECT *pdr, HCONTEXT hcs, int sx, int sy);
bool_t          set_viewport(HCONTEXT hc, const RECT *pr);
void            extend_viewport(HCONTEXT hc);
BYTE far*       scrollup(HCONTEXT hc, const RECT *pr, ASCH blpat, ATTRIBUTE blattr);
BYTE far*       scrolldown(HCONTEXT hc, const RECT *pr, ASCH blpat, ATTRIBUTE blattr);
BYTE far*       scrollleft(HCONTEXT hc, const RECT *pr, ASCH blpat, ATTRIBUTE blattr);
BYTE far*       scrollright(HCONTEXT hc, const RECT *pr, ASCH blpat, ATTRIBUTE blattr);
// Except for context_alloc(), this should be the first routine called to initialize the AWTK system.
bool_t          awtk_init(enum textmodes whichmode, HCONTEXT hcScreen);
// These routines use the VGA BIOS interrupt.
void            set_videomode(int vmode);
int             get_videomode(void);
bool_t          cursor_setxy(int rx, int ry);
bool_t          cursor_getxy(int *rx, int *ry);
int             cursor_getscrx(void);
int             cursor_getscry(void);
void            cursor_size(UCHAR ss, UCHAR es);
// These routines manipulate the active context.
bool_t          printc(int rx, int ry, ASCH ch, ATTRIBUTE attribute);
int             prints(int rx, int ry, const char *s, ATTRIBUTE attribute, FLAGS flags);
ASCH            readc(int rx, int ry);
bool_t          set_attribute(int rx, int ry, ATTRIBUTE attribute);
bool_t          set_rectattrib(const RECT *pr, ATTRIBUTE attribute);
bool_t          set_rectattribcompl(const RECT *pr, ATTRIBUTE attribute);
ATTRIBUTE       get_attribute(int rx, int ry);
// These routines affect/manipulate the physical context (screen).
void            wait_crtretrace(void);
const HCONTEXT  get_physicalcontext(void);
void            clear_physicalcontext(void);
void            grab_physicalcontext(HCONTEXT hc);
void            put_physicalcontext(HCONTEXT hc);
void            grabxy_physicalcontext(const RECT *psr, HCONTEXT hc, int wrx, int wry);
void            putxy_physicalcontext(const RECT *psr, HCONTEXT hc, int wrx, int wry);
// Misc. routines.
void            beep(__U msec);
BYTE far*       get_videosegment(int textmode);
bool_t          is_cgamode(void);
bool_t          is_textmode_supported(void);
void            movemem(unsigned srcseg, unsigned srcoff, unsigned destseg, unsigned destoff, size_t n);
void            awtk_showlicense(bool_t show);

#endif /* AWTK_H */
