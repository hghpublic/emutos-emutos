/*
 * seedfill.c - Filling algorythm
 *
 * Copyright 1982 by Digital Research Inc.  All rights reserved.
 * Copyright (c) 1999 Caldera, Inc. and Authors:
 *
 *  SCC
 *
 * This file is distributed under the GPL, version 2 or at your
 * option any later version.  See doc/license.txt for details.
 */



#include "portab.h"
#include "vdidef.h"
#include "gsxextrn.h"

#define EMPTY   0xffff
#define DOWN_FLAG 0x8000
#define ABS(v) (v & 0x7FFF)
#define QSIZE 200
#define QMAX QSIZE-1



extern WORD get_pix();

/* Global variables */
WORD seed_type;          /* indicates the type of fill   */
WORD search_color;       /* the color of the border      */
WORD Q[QSIZE];           /* storage for the seed points  */
WORD Qbottom;            /* the bottom of the Q (zero)   */
WORD Qtop;               /* points top seed +3           */
WORD Qptr;               /* points to the active point   */
WORD Qtmp;               /* */
WORD Qhole;              /* an empty space in the Q      */
WORD oldy;               /* the previous scan line       */
WORD oldxleft;           /* left end of line at oldy     */
WORD oldxright;          /* right end                    */
WORD newxleft;           /* ends of line at oldy +       */
WORD newxright;          /* the current direction    */
WORD xleft;              /* temporary endpoints          */
WORD xright;             /* */
WORD direction;          /* is next scan line up or down */
BOOLEAN notdone;         /* does seedpoint==search_color */
BOOLEAN gotseed;         /* a seed was put in the Q      */


static WORD plane_mask[4] = { 1, 3, 7, 15 };


/* Prototypes local to this module */
WORD get_seed(WORD xin, WORD yin, WORD * xleftout, WORD * xrightout);


void d_contourfill()
{
    REG WORD fc;

    extern WORD plane_mask[];

    xleft = PTSIN[0];
    oldy = PTSIN[1];

    if (xleft < XMN_CLIP || xleft > XMX_CLIP || oldy < YMN_CLIP
        || oldy > YMX_CLIP) return;

    search_color = INTIN[0];

    /* Range check the color and convert the index to a pixel value */

    if (search_color >= DEV_TAB[13])
        return;

    else if (search_color < 0) {
        search_color = get_pix();
        seed_type = 1;
    }

    else {
        /* We mandate that white is all bits on.  Since this yields 15     */
        /* in rom, we must limit it to how many planes there really are.   */
        /* Anding with the mask is only necessary when the driver supports */
        /* move than one resolution.                       */

        search_color =
            (MAP_COL[search_color] & plane_mask[INQ_TAB[4] - 1]);
        seed_type = 0;
    }

    /* Initialize the line drawing parameters */

    fc = cur_work->fill_color;
    FG_BP_1 = (fc & 1);
    FG_BP_2 = (fc & 2);
    FG_BP_3 = (fc & 4);
    FG_BP_4 = (fc & 8);

    LSTLIN = FALSE;

    notdone = end_pts(xleft, oldy, &oldxleft, &oldxright);

    Qptr = Qbottom = 0;
    Qtop = 3;                   /* one above highest seed point */
    Q[0] = (oldy | DOWN_FLAG);
    Q[1] = oldxleft;
    Q[2] = oldxright;           /* stuff a point going down into the Q */

    if (notdone) {

        /* couldn't get point out of Q or draw it */
        while (1) {
            direction = (oldy & DOWN_FLAG) ? 1 : -1;
            gotseed = get_seed(oldxleft, (oldy + direction),
                               &newxleft, &newxright);

            if ((newxleft < (oldxleft - 1)) && gotseed) {
                xleft = oldxleft;
                while (xleft > newxleft)
                    get_seed(--xleft, oldy ^ DOWN_FLAG, &xleft, &xright);
            }
            while (newxright < oldxright)
                gotseed = get_seed(++newxright, oldy + direction, &xleft,
                                   &newxright);
            if ((newxright > (oldxright + 1)) && gotseed) {
                xright = oldxright;
                while (xright < newxright)
                    get_seed(++xright, oldy ^ DOWN_FLAG, &xleft, &xright);
            }

            /* Eventually jump out here */
            if (Qtop == Qbottom)
                break;

            while (Q[Qptr] == EMPTY) {
                Qptr += 3;
                if (Qptr == Qtop)
                    Qptr = Qbottom;
            }

            oldy = Q[Qptr];
            Q[Qptr++] = EMPTY;
            oldxleft = Q[Qptr++];
            oldxright = Q[Qptr++];
            if (Qptr == Qtop)
                crunch_Q();

            fill_line(oldxleft, oldxright, ABS(oldy));
        }
    }
}                               /* end of fill() */


void crunch_Q()
{                               /* move Qtop down to remove unused seeds */
    while ((Q[Qtop - 3] == EMPTY) && (Qtop > Qbottom))
        Qtop -= 3;
    if (Qptr >= Qtop)
        Qptr = Qbottom;
}

WORD get_seed(xin, yin, xleftout, xrightout)    /* put seeds into Q if
                                                   (xin,yin) */
WORD xin, yin;                  /* is not of search_color        */
WORD *xleftout, *xrightout;
{

    if (end_pts(xin, ABS(yin), xleftout, xrightout)) {  /* false if of
                                                           search_color */
        for (Qtmp = Qbottom, Qhole = EMPTY; Qtmp < Qtop; Qtmp += 3) {
            if (((Q[Qtmp] ^ DOWN_FLAG) == yin) && (Q[Qtmp] != EMPTY)
                && (Q[Qtmp + 1] == *xleftout))

                /* we ran into another seed so remove it and fill the line */
            {
                fill_line(*xleftout, *xrightout, ABS(yin));
                Q[Qtmp] = EMPTY;
                if ((Qtmp + 3) == Qtop)
                    crunch_Q();
                return (0);
            }
            if ((Q[Qtmp] == EMPTY) && (Qhole == EMPTY))
                Qhole = Qtmp;
        }

        if (Qhole == EMPTY) {
            if ((Qtop += 3) > QMAX) {
                Qtmp = Qbottom;
                Qtop -= 3;
            }
        } else
            Qtmp = Qhole;
        Q[Qtmp++] = yin;        /* put the y and endpoints in the Q */
        Q[Qtmp++] = *xleftout;
        Q[Qtmp] = *xrightout;
        return (1);             /* we put a seed in the Q */

    } /* if endpts() */
    else
        return (0);             /* we didnt put a seed in the Q */
}                               /* get_seed */

void v_get_pixel()
{
    REG WORD pel;
    REG WORD *int_out;

    /* Get the requested pixel */

    pel = get_pix();

    int_out = INTOUT;
    *int_out++ = pel;

    /* Correct the pel value for the number of planes so it is a standard
       value */

    if ((INQ_TAB[4] == 1 && pel) || (INQ_TAB[4] == 2 && pel == 3))
        pel = 15;

    *int_out = REV_MAP_COL[pel];
    CONTRL[4] = 2;
}
