/*
 * keyb_us.h - a keyboard layout definition
 *
 * Copyright (c) 2001 EmuTOS development team
 *
 * Authors:
 *  LVL   Laurent Vogel
 *
 * This file is distributed under the GPL, version 2 or at your
 * option any later version.  See doc/license.txt for details.
 */

#if KEYB_US

BYTE keytbl_us_norm[];
BYTE keytbl_us_shft[];
BYTE keytbl_us_caps[];
BYTE keytbl_us_altnorm[];
BYTE keytbl_us_altshft[];
BYTE keytbl_us_altcaps[];

struct keytbl keytbl_us = {
    keytbl_us_norm, 
    keytbl_us_shft, 
    keytbl_us_caps, 
    keytbl_us_altnorm, 
    keytbl_us_altshft, 
    keytbl_us_altcaps, 
};

BYTE keytbl_us_norm[] = {
       0, 0x1b,  '1',  '2',  '3',  '4',  '5',  '6', 
     '7',  '8',  '9',  '0',  '-',  '=',    8, 0x09, 
     'q',  'w',  'e',  'r',  't',  'y',  'u',  'i', 
     'o',  'p',  '[',  ']', 0x0d,    0,  'a',  's', 
     'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';', 
    '\'',  '`',    0, '\\',  'z',  'x',  'c',  'v', 
     'b',  'n',  'm',  ',',  '.',  '/',    0,    0, 
       0,  ' ',    0,    0,    0,    0,    0,    0, 
       0,    0,    0,    0,    0,    0,    0,    0, 
       0,    0,  '-',    0,    0,    0,  '+',    0, 
       0,    0,    0, 0x7f,    0,    0,    0,    0, 
       0,    0,    0,    0,    0,    0,    0,    0, 
       0,    0,    0,  '(',  ')',  '/',  '*',  '7', 
     '8',  '9',  '4',  '5',  '6',  '1',  '2',  '3', 
     '0',  '.', 0x0d,    0,    0,    0,    0,    0, 
       0,    0,    0,    0,    0,    0,    0,    0, 
};

BYTE keytbl_us_shft[] = {
       0, 0x1b,  '!',  '@',  '#',  '$',  '%',  '^', 
     '&',  '*',  '(',  ')',  '_',  '+',    8, 0x09, 
     'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I', 
     'O',  'P',  '{',  '}', 0x0d,    0,  'A',  'S', 
     'D',  'F',  'G',  'H',  'J',  'K',  'L',  ':', 
    '\"',  '~',    0,  '|',  'Z',  'X',  'C',  'V', 
     'B',  'N',  'M',  '<',  '>',  '?',    0,    0, 
       0,  ' ',    0,    0,    0,    0,    0,    0, 
       0,    0,    0,    0,    0,    0,    0,  '7', 
     '8',    0,  '-',  '4',    0,  '6',  '+',    0, 
     '2',    0,  '0', 0x7f,    0,    0,    0,    0, 
       0,    0,    0,    0,    0,    0,    0,    0, 
       0,    0,    0,  '(',  ')',  '/',  '*',  '7', 
     '8',  '9',  '4',  '5',  '6',  '1',  '2',  '3', 
     '0',  '.', 0x0d,    0,    0,    0,    0,    0, 
       0,    0,    0,    0,    0,    0,    0,    0, 
};

BYTE keytbl_us_caps[] = {
       0, 0x1b,  '1',  '2',  '3',  '4',  '5',  '6', 
     '7',  '8',  '9',  '0',  '-',  '=',    8, 0x09, 
     'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I', 
     'O',  'P',  '[',  ']', 0x0d,    0,  'A',  'S', 
     'D',  'F',  'G',  'H',  'J',  'K',  'L',  ';', 
    '\'',  '`',    0, '\\',  'Z',  'X',  'C',  'V', 
     'B',  'N',  'M',  ',',  '.',  '/',    0,    0, 
       0,  ' ',    0,    0,    0,    0,    0,    0, 
       0,    0,    0,    0,    0,    0,    0,    0, 
       0,    0,  '-',    0,    0,    0,  '+',    0, 
       0,    0,    0, 0x7f,    0,    0,    0,    0, 
       0,    0,    0,    0,    0,    0,    0,    0, 
       0,    0,    0,  '(',  ')',  '/',  '*',  '7', 
     '8',  '9',  '4',  '5',  '6',  '1',  '2',  '3', 
     '0',  '.', 0x0d,    0,    0,    0,    0,    0, 
       0,    0,    0,    0,    0,    0,    0,    0, 
};

BYTE keytbl_us_altnorm[] = {
    0,
};
BYTE keytbl_us_altshft[] = {
    0,
};
BYTE keytbl_us_altcaps[] = {
    0,
};

#if DFLT_KEYB_US
#define dflt_keytbl keytbl_us
#endif /* DFLT_KEYB_US */

#endif /* KEYB_US */
