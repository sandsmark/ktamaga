/***************************************************************************
    confData.cpp
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
 
#include "confData.h"

#define Inherited QDialog
#include <kapp.h>
#include <qbttngrp.h>
#include <qpushbt.h>

confData::confData
(
	QWidget* parent,
	const char* name
)
	:
	Inherited( parent, name, TRUE )
{
	QPushButton* tmpQPushButton;
	QButtonGroup* tmpQButtonGroup;

	tmpQPushButton = new QPushButton( this, "cancel" );
	tmpQPushButton->setGeometry( 10, 205, 100, 30 );
	connect( tmpQPushButton, SIGNAL(clicked()), SLOT(cancelClicked()) );
	tmpQPushButton->setText( i18n("Cancel") );
	tmpQPushButton->setAutoRepeat( FALSE );
	tmpQPushButton->setAutoResize( FALSE );

	tmpQPushButton = new QPushButton( this, "hb" );
	tmpQPushButton->setGeometry( 120, 205, 100, 30 );
	connect( tmpQPushButton, SIGNAL(clicked()), SLOT(helpClicked()) );
	tmpQPushButton->setText( i18n("Help") );
	tmpQPushButton->setAutoRepeat( FALSE );
	tmpQPushButton->setAutoResize( FALSE );

	tmpQPushButton = new QPushButton( this, "ok" );
	tmpQPushButton->setGeometry( 230, 205, 100, 30 );
	connect( tmpQPushButton, SIGNAL(clicked()), SLOT(okClicked()) );
	tmpQPushButton->setText( i18n("OK") );
	tmpQPushButton->setAutoRepeat( FALSE );
	tmpQPushButton->setAutoResize( FALSE );

	ts1 = new QRadioButton( this, "tsc1" );
	ts1->setGeometry( 20, 25, 130, 20 );
	ts1->setText( i18n("1/2 hour/yr") );
	ts1->setAutoRepeat( FALSE );
	ts1->setAutoResize( FALSE );

	ts2 = new QRadioButton( this, "tsc2" );
	ts2->setGeometry( 20, 45, 130, 20 );
	ts2->setText( i18n("1 hour/yr") );
	ts2->setAutoRepeat( FALSE );
	ts2->setAutoResize( FALSE );
	ts2->setChecked( TRUE );

	ts3 = new QRadioButton( this, "tsc3" );
	ts3->setGeometry( 20, 65, 130, 20 );
	ts3->setText( i18n("2 hours/yr") );
	ts3->setAutoRepeat( FALSE );
	ts3->setAutoResize( FALSE );

	ts4 = new QRadioButton( this, "tsc4" );
	ts4->setGeometry( 20, 85, 130, 20 );
	ts4->setText( i18n("5 hours/yr") );
	ts4->setAutoRepeat( FALSE );
	ts4->setAutoResize( FALSE );

	ts5 = new QRadioButton( this, "tsc5" );
	ts5->setGeometry( 20, 105, 130, 20 );
	ts5->setText( i18n("8 hours/yr") );
	ts5->setAutoRepeat( FALSE );
	ts5->setAutoResize( FALSE );

	ts6 = new QRadioButton( this, "tsc6" );
	ts6->setGeometry( 20, 125, 130, 20 );
//	{
//		QColorGroup normal( QColor( QRgb(0) ),
//                                      QColor( QRgb(12632256) ),
//                                      QColor( QRgb(16777215) ),
//                                      QColor( QRgb(6316128) ),
//                                      QColor( QRgb(10789024) ),
//                                      QColor( QRgb(8421504) ),
//                                      QColor( QRgb(16777215) ) );
//		QColorGroup disabled( QColor( QRgb(8421504) ),
//                                      QColor( QRgb(12632256) ),
//                                      QColor( QRgb(16777215) ),
//                                      QColor( QRgb(6316128) ),
//                                      QColor( QRgb(10789024) ),
//                                      QColor( QRgb(8421504) ),
//                                      QColor( QRgb(12632256) ) );
//		QColorGroup active( QColor( QRgb(0) ),
//                                    QColor( QRgb(12632256) ),
//                                    QColor( QRgb(16777215) ),
//                                    QColor( QRgb(6316128) ),
//                                    QColor( QRgb(10789024) ),
//                                    QColor( QRgb(0) ),
//                                    QColor( QRgb(16777215) ) );
//		QPalette palette( normal, disabled, active );
//		ts6->setPalette( palette );
//	}
	ts6->setText( i18n("1 Real Day/yr") );
	ts6->setAutoRepeat( FALSE );
	ts6->setAutoResize( FALSE );

	tmpQPushButton = new QPushButton( this, "reset" );
	tmpQPushButton->setGeometry( 340, 15, 165, 40 );
	connect( tmpQPushButton, SIGNAL(clicked()), SLOT(resetClicked()) );
	tmpQPushButton->setText( i18n("Reset tamagotchi") );
	tmpQPushButton->setAutoRepeat( FALSE );
	tmpQPushButton->setAutoResize( FALSE );

	tmpQPushButton = new QPushButton( this, "debug1" );
	tmpQPushButton->setGeometry( 340, 65, 165, 20 );
	connect( tmpQPushButton, SIGNAL(clicked()), SLOT(debug1()) );
	tmpQPushButton->setText( i18n("Debug: advance phase") );
	tmpQPushButton->setAutoRepeat( FALSE );
	tmpQPushButton->setAutoResize( FALSE );

	tmpQPushButton = new QPushButton( this, "debug2" );
	tmpQPushButton->setGeometry( 340, 95, 165, 20 );
	connect( tmpQPushButton, SIGNAL(clicked()), SLOT(debug2()) );
	tmpQPushButton->setText( i18n("Debug: modify pos's") );
	tmpQPushButton->setAutoRepeat( FALSE );
	tmpQPushButton->setAutoResize( FALSE );

	lcs1 = new QRadioButton( this, "lcs1" );
	lcs1->setGeometry( 170, 30, 150, 20 );
	lcs1->setText( i18n("500 ms/frame") );
	lcs1->setAutoRepeat( FALSE );
	lcs1->setAutoResize( FALSE );
	lcs1->setChecked( TRUE );

	lcs2 = new QRadioButton( this, "lcs2" );
	lcs2->setGeometry( 170, 50, 150, 20 );
	lcs2->setText( i18n("300 ms/frame") );
	lcs2->setAutoRepeat( FALSE );
	lcs2->setAutoResize( FALSE );

	lcs3 = new QRadioButton( this, "lcs3" );
	lcs3->setGeometry( 170, 70, 150, 20 );
	lcs3->setText( i18n("200 ms/frame") );
	lcs3->setAutoRepeat( FALSE );
	lcs3->setAutoResize( FALSE );

//    	mvt = new QCheckBox( this, "Menu" );
//     	mvt->setGeometry( 165, 135, 200, 20 );
//     	mvt->setText( i18n("Menubar on startup") );
//     	mvt->setAutoRepeat( FALSE );
//     	mvt->setAutoResize( FALSE );

	snd = new QCheckBox( this, "Sound" );
	snd->setGeometry( 165, 110, 150, 20 );
	snd->setText( i18n("Sound") );
	snd->setAutoRepeat( FALSE );
	snd->setAutoResize( FALSE );

	tmpQButtonGroup = new QButtonGroup( this, "BGLCD" );
	tmpQButtonGroup->setGeometry( 165, 10, 160, 90 );
	tmpQButtonGroup->setFrameStyle( 49 );
	tmpQButtonGroup->setTitle( i18n("LCD speed") );
	tmpQButtonGroup->setAlignment( 1 );
	tmpQButtonGroup->insert( lcs1 );
	tmpQButtonGroup->insert( lcs2 );
	tmpQButtonGroup->insert( lcs3 );
	tmpQButtonGroup->lower();

	tmpQButtonGroup = new QButtonGroup( this, "BGScale" );
	tmpQButtonGroup->setGeometry( 10, 10, 150, 140 );
	tmpQButtonGroup->setFrameStyle( 49 );
	tmpQButtonGroup->setTitle( i18n("Time scale") );
	tmpQButtonGroup->setAlignment( 1 );
	tmpQButtonGroup->insert( ts2 );
	tmpQButtonGroup->insert( ts3 );
	tmpQButtonGroup->insert( ts4 );
	tmpQButtonGroup->insert( ts6 );
	tmpQButtonGroup->insert( ts5 );
	tmpQButtonGroup->insert( ts1 );
	tmpQButtonGroup->lower();

	resize( 510, 245 );
}


confData::~confData()
{
}
void confData::resetClicked()
{
}
void confData::okClicked()
{
}
void confData::cancelClicked()
{
}
void confData::debug1()
{
}
void confData::debug2()
{
}
void confData::helpClicked()
{
}
