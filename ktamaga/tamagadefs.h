/***************************************************************************
    tamagadefs.h
                             -------------------
    copyright            : (C) 2000 by Thomas Leineweber
                           (C) 1997 by John Zero
    email                : leine@users.sourceforge.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef TAMAGA_H
#define TAMAGA_H

#define APPVER	"v0.6"
#define APPNAME	"KTamaga " APPVER

#define APPINITMSG "[" APPNAME " (C) 1997, John Zero, (C) 2000, Thomas Leineweber, GNU GPL]\n"
#define ABOUT_MSG i18n("KTamaga v0.6 was written and is\n" \
                       "(C) 1997 by John Zero <johnzero@telnet.hu>\n" \
                  "(C) 2000 by Thomas Leineweber <leine@users.sourceforge.net>\n" \
                  "This program falls under the GNU GPL license") 

//------------------------------------
#define TL_TICK		500 // tlcd tick time, in millisec.
#define TS_TICK		1000 // scheduler tick time, msec.

#define TAMDATFILE	"/.tamaga.dat"
#define TAMXRCFILE	"/.tamaga.rc"

// For the KDE version
#define TDATADS		"/ktamaga"



//------------------------------------------------------------------------
#define TS_TAMAGOTCHI	0
#define TS_BABITCHI	1
#define TS_MARUTCHI	2
//
#define TS_TAMATCHI	3
#define TS_KUCHITAMACHI 4
//
#define TS_GINJIROTCHI	6
#define TS_MASKTCHI	7
#define TS_KUCHIPATCHI  8
#define TS_TARAKOTCHI	10
#define TS_MAMETCHI	5
#define TS_NYOROTCHI	9
//
#define TS_GAIJINTCHI	11
//
#define TS_BYE		-1

#define MAXPHASES	11

//-----------------------------------

#define AN_NORML	1
#define AN_NORMR	2
#define AN_EAT		3
#define AN_HAPPY	4
#define AN_MESS		5
#define AN_NEGATIVE	6
#define AN_PLAY		7
#define AN_SICK		8
#define AN_SLEEP	9
#define AN_TURNL	10
#define AN_TURNR	11
#define AN_UNHAPPY	12

//#define AN_INJECT	100
#define AN_CLEANUP	101
#define AN_CHANGE	102
#define AN_DARK		103
#define AN_HATCH	104
#define AN_INFO		105
#define AN_INFO2	106
#define AN_INFO3	107
#define AN_INFO4	108
#define AN_INFOEND	109
#define AN_EATSNACK	110
#define AN_EATMEAL	111
#define AN_GAMESTART	112
#define AN_PLAYRES	113
#define AN_GAMERES	114

#define AN_HFRAME	2	// 3. frame a hatch

#define EA_LOOP		1

//#define AS_AM		0
#define AS_NONE		0

#define AS_CHANGE	1
#define AS_CHANGEEND	8
#define AS_DARK		9
#define AS_DARKZ	10
#define AS_DARKZLOOP	11
#define AS_GOHOME	12
#define AS_GOHOMELOOP	13
#define AS_HEART1	14
#define AS_HEART0	15
#define AS_MEAL		16
#define AS_MEALEND	19
#define AS_MESS		20
#define AS_MESSLOOP	21
#define AS_PM		22
#define AS_SNACK	23
#define AS_SNACKEND	26
#define AS_TMWALK	27
#define AS_ZZZ		29
#define AS_ZZZLOOP	30
#define AS_CLEAN	31
#define AS_SKULL	32
#define AS_HUNGRYTEXT	33
#define AS_HAPPYTEXT	34
#define AS_DISCLTEXT	35
#define AS_DISCLATOM	36
#define AS_AGEWGT	37
#define AS_BNUM		38
#define AS_SNUM		48
#define AS_GAMEPRE	58
#define AS_LEFTARR	59
#define AS_RIGHTARR	60
#define AS_GAMERES	61

#define AS_HATCH	100

#define SREINIT		-1
#define SPAUSE		-2

#define AR_NONE		0
#define AR_HUNGRY	1
#define AR_UNHAPPY	2
#define AR_ILL		4
#define AR_MESS		8
#define AR_NOREASON	16
#define AR_HATCH	32

#define IN_AGE		0
#define IN_WGT		1
#define IN_HUNGRY	2
#define IN_HAPPY	3
#define IN_DISCL	4

#define BS_NORMAL	1
#define BS_DEBUG	2
#define BS_PLAY		3
#define BS_FEED		4

#define B_BASESET	0
#define B_ATTNORM	7
#define B_ATTLIGHT	8
#define B_EATSET	9
#define B_CANCEL	9
#define B_NULL		12
#define B_TLEFT		13
#define B_TRIGHT	14
#define B_DEBUGSET	15 
// +7
#define B_MAX		22 // update, if needed!

#define TIMEMULT	60.0

#define LCBOTT  3+4*16
#define LCCENT  3+4*16-2
#define RAX  4    

extern int	app_pause;

#include <qapp.h>

#include <kapp.h>
extern KApplication *app;

#include "conf.h"
extern conf *config;

#ifndef NDEBUG
void dbgtime(const char *id);
#else
#define dbgtime(x)
#endif

#endif
