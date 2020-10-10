/***************************************************************************
    tamdata.h
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

#ifndef TAMDATA_H
#define TAMDATA_H

struct animes {
	int	start,len;
	int	eact;
	int	rep;
};

extern animes ans[];
extern char *blnam[];
extern char *specnam[];

struct andisps {
	int	dx,dy;
};

extern andisps andp[100];

extern char	*icnam[];
extern char	*ictip[];

struct PhaseData {
        float   poopf,poopt,psens,foodcf,foodct,happycf,happyct,
        	illf,illt,illfact,illsens;
        float	sleepf,sleept,sleeps,slf,slt;
        float	disclf,disclt;
        float	discfact; // 0..100
        float	badfact; // 0..100
};

extern PhaseData psd[];



#endif
