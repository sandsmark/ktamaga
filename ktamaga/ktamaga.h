/***************************************************************************
    ktamaga.h
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

#ifndef KTAMAGA_H
#define KTAMAGA_H

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
#include "tamagadefs.h"
#include "tlcd.h"

//-----------------------------------------

class Ktamaga : public QWidget
{
    Q_OBJECT;

public:
    Ktamaga( QWidget *parent=0, const char *name=0 );
    QPushButton    *makeButton( int, int, int, int, const char *, QPixmap*, char * );
    ~Ktamaga( void );
           
public slots:
    void	configMenu();
    void	aboutClicked();
    void	launchHelp();
    void	popmenu( QPoint p );
    
    void	feedClicked();
    void	lightsClicked();
    void	gameClicked();
    void	medicalClicked();
    void	toiletClicked();
    void	statusClicked();
    void	teachClicked();
    void	attentionClicked();
    
    void	stateEnded();
    void	schedTick();

    void	dbgWrite();
    void	dbgPrev();
    void	dbgNext();
    void	dbgLeft();
    void	dbgUp();
    void	dbgDown();
    void	dbgRight();
    void	dbgCancel();
    
    void	feedMeal();
    void	feedSnack();
    void	feedCancel();

    void	gameCancel();
    void	gameLeft();
    void	gameRight();
        
signals:
    void quits( int );

protected:
    void resizeEvent( QResizeEvent * );

private:
    QPushButton 	*quit;
    QPushButton 	*bcont[8]; // 8 bushbuttons
    QWidget		*cont; // container
    QString		datadir;
    
    KMenuBar            *menu;
    QPopupMenu		*pmenu;
    QPixmap		pcont[25]; // pixmaps/icons for pushbuttons
    QPixmap		bp;	   // background pixmap
    QTimer		*tx;	   // timer for scheduler
    QString		saveName;  // save file/dat name
    tlcd		*scr;	   // the LCD screen, the display engine
    int			streq,streq2;	   // (next) state request, (next+1)
    int			ngame; 		// num. play in game
    int			ghit;  		// times scored in game
    int			curst;		// current button state
    
    long		ctime;	// current time in (sec) units

    PhaseData		*pd;   // tmp, act phase data
    struct SchedData {
    		long	npoop,tpoop;
    		long	nill,till;
    		long	nhatch;
    		long	nsleep,tsleep,nwake;
    		long	nhappy,thappy;
    		long	neat,teat;
    		long	ndiscl,tdiscl;
    		long	tsave;
    		long	tgrow,tinphase;
    		long	nbadd;
    		long	ctimetmp; // temp, filled on save
    		long	attn;	// attention sig., increments
    		int	ars;	// attention state, bitmask
    } ss;

    struct TamaData {
    	int		sleeping,hungry,lights,happy;
    	int		ill,poop,phase;
    	int		discl;
    	int		age,wgt;
    	int		bad;

    	int 		miscare;
	int		invdispl; // inverse discipline points
	int		fedplg; // feed/play before it beeps
	int		nodispl; // disclip. gone before done (cws)
    } st;


// Static part
    int		saveTama( void );
    int		loadTama( void );
    void	resetTama( void );
    void	startTama( void );
    int		randx( int, int );
    float	randf( float, float );
    void	setButt( int st );
    void	createButt( void );
    void	changeCButton( int, QPixmap *pix, const char *tip );
    void	setAttButt( int );
    void	addContGame( int pos ); 
    void	initVars( void );
    void	createMenu( void );
    void	createWidgets( void );
    void	placeWidgets( void );
    
// Scheduler part 
    void	initScheduler( void );
    void	startScheduler( void );
    void	schedReinit( void );
    void	scheduler( void );
    void	debugstat( void );
    void	advphase( void );

// Active part
    void	needAttention( void ); // beep, etc
    
};


#endif





