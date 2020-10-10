/***************************************************************************
    tamdata.cpp
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

#include "tamdata.h"
#include "ktamaga.h"

animes ans[] = {
	{},
	{0,2,0,-1}, // norml
	{2,2,0,-1}, // normr
	{4,2,EA_LOOP,-1}, // eat
	{6,2,0,3}, // happy
	{8,2,0,3}, // mess
	{10,2,0,3}, // negative
	{12,2,0,-1}, // play
	{14,2,0,-1}, // sick
	{16,2,0,-1}, // sleep
	{18,1,0,1}, // turnl
	{19,1,0,1}, // turnr
	{20,6,0,1} // unhappy
};

char *blnam[] = {
	"1","2","3","4","eat1","eat2","happy1","happy2","mess1","mess2",
	"no1","no2","play1","play2","sick1","sick2","sleep1","sleep2",
	"turn1","turn2","unhappy1","unhappy2","unhappy3","unhappy4",
	"unhappy5","unhappy6", 0
};

char *specnam[] = {
	"am","change1","change2","change3","change4","change5","change6",
	"change7","change8","dark0","dark1","dark2",
	"gohome1","gohome2","heart1","heart2",
	"meal1","meal2","meal3","meal4","mess1","mess2","pm",
	"snack1","snack2","snack3","snack4","tmwalk1","tmwalk2","z1","z2",
	"clean","skull","hungry","happy","discip","discip_a","agewgt",
	"b0","b1","b2","b3","b4","b5","b6","b7","b8","b9",
	"s0","s1","s2","s3","s4","s5","s6","s7","s8","s9",
	"gamepre","leftarr","rightarr","gameres",
	0
};

andisps andp[100];

//--------------------------------------------------------
    char	*icnam[]={"icon_feeds.xpm",
	"icon_light.xpm","icon_plays.xpm","icon_inject.xpm",
	"icon_toilet.xpm","icon_status.xpm","icon_teach.xpm","icon_attents.xpm",
	"icon_attentact.xpm",
	"icon_cancel.xpm", "icon_meal.xpm","icon_snack.xpm","icon_null.xpm",
	"icon_turnleft.xpm","icon_turnright.xpm",
	"icon_dbgsave.xpm","icon_dbgprev.xpm","icon_dbgnext.xpm",
	"icon_dbgleft.xpm","icon_dbgup.xpm","icon_dbgdown.xpm","icon_dbgright.xpm" };
    char	*ictip[] = {
	"Feed the animal","Turn on/off the lights","Play","Cure",
	"Flush the toilet","Display status","Discipline","Attention",
	"Attention needed!",
	"Cancel","Give a meal","Give a snack","(Nothing)",
	"Will he turn left?","Will he turn right?",
	"Save settings","Prev frame","Next frame",
	"Left","Up","Down","Right"
    };

//----------

PhaseData psd[] = {
//----------+-----+------+-------------+---------+------+-------------
//    Poop  |Food |Happy |    Illness  | Sleep   |SlpLen|Discip
// Fr-to sns|fr-to|fr-to |fr-to fct sns|Fr-to sns|Fr-to |fr-to
//----------+-----+------+-------------+---------+------+-------------
 {  0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0,  0, 0,  0, 0  }, // TAMAGOTCHI
 {  5,10, 1,  3, 4, 2, 4,  7,12, 1, 1,  15,22, 1,  3, 7,  10,15 }, // BABITCHI

 {  5,10, 1,  4, 7, 3, 7,  7,12, 1, 1,  15,22, 1,  3, 7,  10,15 }, // MARUTCHI

 { 10,20, 2,  5, 8, 6, 8,  9,14, 1, 2,  20,28, 2,  5, 8,  12,20 }, // TAMATCHI
 {  4,12, 2,  4, 8, 4, 7,  8,12, 2, 2,  17,25, 2,  7,12,  11,16 }, // KUCHITAMACHI

 { 12,25, 3,  7, 8, 4, 9,  9,19, 1, 3,  15,27, 3,  4, 9,  14,27 }, // MAMETCHI
 { 12,25, 3,  7, 8, 4, 9,  9,19, 1, 3,  15,27, 3,  4, 6,  14,27 }, // GINJIROTCHI
 { 12,25, 3,  7, 8, 4, 9,  9,19, 2, 3,  15,27, 3,  4, 9,  14,27 }, // MASKTCHI
 { 12,25, 3,  7, 8, 4, 9,  9,19, 1, 3,  15,27, 3,  4, 9,  14,27 }, // KUCHIPATCHI
 { 12,25, 3,  7, 8, 8,15,  3,10, 1, 4,  12,20, 3,  7,15,  14,27 }, // NYOROTCHI
 { 12,25, 3,  7, 8, 4, 9,  9,19, 1, 3,  15,27, 3,  4, 9,  14,27 }, // TARAKOTCHI
 { 12,25, 3,  7, 8, 4, 9,  9,19, 1, 3,  15,27, 3,  4, 9,  14,27 }  // GAIJINTCHI
};
