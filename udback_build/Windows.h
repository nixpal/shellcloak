/*  windows.h

		Definitions for AWTK window types, variables and routines.

		Copyright (c) 2009 by Jose F. D'Silva
		All Rights Reserved.
*/
#ifndef AWTK_WINDOWS_H
#define AWTK_WINDOWS_H
#include <conio.h>
#include <mem.h>
#include "awtk.h"

#define WND_DEFLAYERPATTERN                      (219)
#define GET_WND_FG(attribute)                    GET_ATTRIBUTE_FG(attribute)
#define GET_WND_BG(attribute)                    GET_ATTRIBUTE_BG(attribute)
#define ATTRIBUTE_SHADOW											   MK_ATTRIBUTE(LIGHTGRAY, BLACK)
#define CLRWND(pr, attribute)                    window_clear((pr), (attribute), WND_DEFLAYERPATTERN)
#define CLRSCRP(attribute, pattern)              { /* begin a code block so that RECT::r is private.                 */ \
																									 RECT r = GET_ACTIVECONTEXT()->viewport;                              \
																									 r.x = r.y = 0; /* this should be relative to the active viewport. */ \
																									 window_clear(&r, (attribute), (pattern));                            \
																								 }
#define CLRSCR(attribute)                        CLRSCRP(attribute, WND_DEFLAYERPATTERN)
#define GET_WND_BUFFERSIZE(w, h)                 ((((w)*(h)) << 1) * sizeof(BYTE))
#define GET_WNDTXT_BUFFERSIZE(w, h)              (GET_WND_BUFFERSIZE(w, h) >> 1)

#define SET_GRID_DIMENSIONS(rows, columns)       MAKELONG(rows, columns)
#define GET_GRID_ROWS(dw)                        LOWORD(dw)
#define GET_GRID_COLUMNS(dw)                     HIWORD(dw)
#define GET_GRID_WIDTH(cw, c)                    ((cw)*(c)+1)
#define GET_GRID_HEIGHT(ch, r)                   ((ch)*(r)+1)

/* ASCII Window layouts (WNDTYPE) */
#define WND_SHSV                    WND_SVSH
#define WND_DHDV                    WND_DVDH
#define WND_DHSV                    WND_SVDH
#define WND_SHDV                    WND_DVSH

/* Grid layouts (GRDTYPE) */
#define GRD_SHSVSC                  GRD_SVSHSC
#define GRD_SHSVDC                  GRD_SVSHDC
#define GRD_DHDVSC                  GRD_DVDHSC
#define GRD_DHDVDC                  GRD_DVDHDC

/* ASCII Window layout enumeration */
typedef enum {
	WND_LAYER=0,   /* plain layer */
	WND_CELL,      /* cell (#) */
	WND_SVSH,      /* single vertical, single horizontal borders */
	WND_DVDH,      /* double vertical, double horizontal borders */
	WND_SVDH,      /* single vertical, double horizontal borders */
	WND_DVSH,      /* double vertical, single horizontal borders */
	WND_CUST,      /* user-defined borders */

	WND_NTYPES     /* how many window types? (NOT A LAYOUT CONSTANT) */
} WNDTYPE;

/* ASCII Window Grid layout enumeration */
typedef enum {
	GRD_SVSHSC=0,  /* single outer border, single bordered cells */
	GRD_SVSHDC,    /* single outer border, double bordered cells */
	GRD_DVDHSC,    /* double outer border, single bordered cells */
	GRD_DVDHDC,    /* double outer border, double bordered cells */
	GRD_CUST,      /* user-defined borders */

	GRD_NTYPES     /* how many grid types? (NOT A LAYOUT CONSTANT) */
} GRDTYPE;

/* window/grid border style */
typedef struct {
	ASCH hb;     /* horizontal border   */
	ASCH vb;     /* vertical border     */
	ASCH lt;     /* left-top corner     */
	ASCH rt;     /* right-top corner    */
	ASCH lb;     /* left-bottom corner  */
	ASCH rb;     /* right-bottom corner */
} WNDBORDERSTYLE;

/* grid-cell border style (for grids only) */
typedef struct {
	ASCH chb;    /* cell horizontal border                     */
	ASCH cvb;    /* cell vertical border                       */
	ASCH cl;     /* left intersection with window border       */
	ASCH cr;     /* right intersection with window border      */
	ASCH ct;     /* top intersection with window border        */
	ASCH cb;     /* bottom intersection with window border     */
	ASCH cm;     /* middle intersection with cell horizontal and vertical borders */
} CELLBORDERSTYLE;

/* window/grid style definition. */
typedef struct {
	ASCH            layer_pattern;       /* ASCII pattern of internal window plane                             */
	ATTRIBUTE       layer_attribute;     /* attribute of internal window plane (use MK_ATTRIBUTE(fg, bg))      */
	bool_t          islayertransparent;  /* should the internal window plane be drawn?                         */
	ATTRIBUTE       border_attribute;    /* border attribute (use MK_ATTRIBUTE(fg, bg))                        */
	WNDBORDERSTYLE  cbs;                 /* custom border style for window/grid (type == WND_CUST or GRD_CUST) */
	CELLBORDERSTYLE ccs;                 /* custom cell border style for grid (type == GRD_CUST)               */
	int             type;                /* draw what, window or grid?                                         */
} WNDSTYLE;

/* ASCII Window/Grid definition */
typedef struct{
	RECT      r;          /* rectangular region */
	WNDSTYLE  style;      /* window/grid style  */
	DWORD     reserved;   /* 4 bytes reserved for special/future use (use MAKELONG(lw, hw)) */
} window_t,
	grid_t;

/* Extended grid definition.
	 An extended grid allows you to customize the width and height of each column and row.
*/
typedef struct {
	POINT xy;
	int cols;
	int rows;
	int *colw; //column widths
	int *rowh; //row heights
	WNDSTYLE style;
	DWORD reserved; //unused: set to zero.
} gridex_t;

typedef window_t  *HWND;
typedef grid_t    *HGRD;
typedef gridex_t  *HGRDEX;

/*
************************************************************************
* WINDOWS module function prototypes: *
************************************************************************
*/
WNDBORDERSTYLE*   window_get_systemborderstyle(void);
CELLBORDERSTYLE*  grid_get_systemcellstyle(void);
int               window_draw(const window_t *pwnd);
void              window_clear(const RECT *pr, ATTRIBUTE attribute, ASCH layer_pattern);
void              window_grab(const RECT *pr, BYTE far *buffer);
void              window_put(const RECT *pr, const BYTE far *buffer);
void              window_grab_text(const RECT *pr, BYTE far *buffer);
void              window_put_text(const RECT *pr, const BYTE far *buffer);
void              grid_draw(const grid_t *pwnd);
void              gridex_draw(const gridex_t *pgrdex);

#endif //AWTK_WINDOWS_H
