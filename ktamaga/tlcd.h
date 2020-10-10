/***************************************************************************
    tlcd.h
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

#ifndef TLCD_H
#define TLCD_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <qpushbt.h>
#include <qscrbar.h>
#include <qlcdnum.h>
#include <qfont.h>
#include <qmenubar.h>
#include <qmenudta.h>
#include <qpopmenu.h>
#include <qkeycode.h>
#include <qapp.h>
#include <qfile.h>
#include <qwidget.h>
#include <qpixmap.h>
#include <qtooltip.h>
#include <qmsgbox.h>
#include <qdialog.h>

#include <kmenubar.h>
#include <kmsgbox.h>
#include <kapp.h>

#include "conf.h"
#include "tamdata.h"


class tlcd : public QWidget
{
 Q_OBJECT;
 
public:
 tlcd( QWidget *parent=0, const char *name=0 );
// void		setAnim( int aid );
 void		setState( int );
 void		setInfoAnim( int age, int wgt, int hun, int dis, int hap );
 void           setPoop( int ison );
 void		setIll( int ison );
 void		setPlays( int hd, int ud );
 void		setGameres( int gxhit, int gxmiss );
 void		setPhase( int tst );
 void		makeDark( void );
 void		setMeal( int );
 void		setNormal( void );
 void		changeSet( void );
 void		mousePressEvent( QMouseEvent * );

 void		debugNext( void );
 void		debugPrev( void );
 void		debugMove( int dx, int dy );
 void		debugOut( void );
 void		setSNorm( int st );
 void		setDebug( int ison );

 int		isNormal( void );
 int		isPlaying( void );

signals:
 void		endState();
 void		clickedX( QPoint ); 

public slots:
 void		Nextframe(); 
                    
private:
 int		ospeed;
 int		eid,endf;
 int		framecnt,fcn;
 int		curan,cframe,mframe,sframe; 
 int		delt,ddir;
 int		specx,fmeal;
 int		debugf;
 int		pixml,pixmr;
 int		headd,userd,hit,miss;
 QPixmap	*pm;
 QTimer		*tt;
 int		anrep,norms;

 int		inf[5];
 int		dpoop,dill;
 int		tphase;
 QPixmap	*pdat[100];
 QPixmap	*pspec[100];
 QPixmap	*pbase,*pbk;
 QString	datadir;

 void		ShowInfos( void );
 void		StepAnim( void );
 void		debugProc( void );
 int		specPreproc( void );
 void		addSpec( void );
 void		putBase( void );
 int		animStepafter( void );
 int		initandloop( void );
 
 void		loadblock( void );
 void		loadbase( void );
 void		loadPos( void );
 void		savePos( void );

 QPixmap	*convXpm( char *fname );
 
 void 		paintEvent( QPaintEvent* );
};


#endif
