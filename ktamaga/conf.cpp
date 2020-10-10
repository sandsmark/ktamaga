/***************************************************************************
    conf.cpp
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

#include <stdio.h>

#include "tamagadefs.h"
#include "ktamaga.h"
#include "conf.h"
#include <qlabel.h>
#include <qtstream.h>

#define Inherited confData

float tfv[] = { 0, TIMEMULT/2.0, TIMEMULT, 2.0*TIMEMULT, 5.0*TIMEMULT,
	8.0*TIMEMULT, 0 };

conf::conf( QWidget* parent, const char* name ) : Inherited( parent, name )
{
 setCaption( i18n("Configure") );

 lcspeed=TL_TICK;
 //tfact=TIMEMULT;
 //menuvis=1;
 //stmenuvis=1;
 dbgreq=0;
 sound=1;
 resetreq=0;
 tflevel=2;

 datadir = app->kde_datadir()+TDATADS;

 // Support running without installing
 // Check if we're being run from the builddir
 if (!QFile::exists(datadir) && QFile::exists("../ktamaga/data/")) {
     datadir = "../ktamaga/data/";
 }
 // Check for in source build
 if (!QFile::exists(datadir) && QFile::exists("./ktamaga/data/")) {
     datadir = "./ktamaga/data/";
 }
}

void conf::helpClicked()
{
 app->invokeHTMLHelp("ktamaga/configure.html", "");
}

int conf::load()
{
 printf(i18n("Loading settings..."));
 KConfig *cf = KApplication::getKApplication()->getConfig();

 cf->setGroup("Settings");
 lcspeed=cf->readNumEntry("LCDSpeed",TL_TICK);
 //stmenuvis=cf->readNumEntry("MenuVisible",1);
 sound=cf->readNumEntry("Sound",1);
 tflevel=cf->readNumEntry("TimeScale",2);
 tfact=tfv[tflevel];
 return 1;
}

int conf::save()
{ 
 QString s;
 KConfig *cf = KApplication::getKApplication()->getConfig();

 cf->setGroup("Settings");
 cf->writeEntry("LCDSpeed",s.setNum(lcspeed));
 //cf->writeEntry("MenuVisible",s.setNum(stmenuvis));
 cf->writeEntry("Sound",s.setNum(sound));
 cf->writeEntry("TimeScale",s.setNum(tflevel));
 cf->sync();
 return 1;
}

void conf::prep( void )
{
 lcs1->setChecked(lcspeed==TL_TICK);
 lcs2->setChecked(lcspeed==300);
 lcs3->setChecked(lcspeed==200);
 snd->setChecked(sound);

 ts1->setChecked(tfact==tfv[1]);
 ts2->setChecked(tfact==tfv[2]);
 ts3->setChecked(tfact==tfv[3]);
 ts4->setChecked(tfact==tfv[4]);
 ts5->setChecked(tfact==tfv[5]);
 //ts6->setChecked(tfact==tfv[3]);
 //scin->setEnabled(0);
}

void conf::okClicked()
{
 if (lcs1->isChecked()) lcspeed=TL_TICK;
  else if (lcs2->isChecked()) lcspeed=300;
   else lcspeed=200;

 if (ts1->isChecked()) tflevel=1;
  else if (ts2->isChecked()) tflevel=2;
   else if (ts3->isChecked()) tflevel=3;
    else if (ts4->isChecked()) tflevel=4;
     else if (ts5->isChecked()) tflevel=5;
 tfact=tfv[tflevel];

 sound=snd->isChecked();

 save();
 
 emit accept();
}

void conf::cancelClicked()
{
 emit reject(); 
}

void conf::debug1()
{ 
 dbgreq=1;

 emit accept();
}

void conf::debug2()
{ 
 dbgreq=2;

 emit accept();
}

void conf::resetClicked()
{ 
 dlgsel d(this,
          i18n("Sure?"),
          i18n("Are you sure you want to reset your tamagotchi?"));
 if ( d.exec() ) {
  resetreq=1;

  emit accept();
 }
}

conf::~conf()
{
}

//---------------------------

dlgsel::dlgsel( QWidget *parent, const char *name, const char *txt ) 
 : QDialog(parent,name,TRUE)
{
 QPushButton *ok, *cancel;
 QLabel *l;

 setCaption(name);
 l = new QLabel(txt,this);
 l->setGeometry(10,10,300,60);
 l->setAlignment( 1316 );

 ok = new QPushButton(i18n("Ok"),this);
 ok->setGeometry(225,60,90,30);
 cancel = new QPushButton(i18n("Cancel"),this);
 cancel->setGeometry(10,60,90,30);

 connect( ok, SIGNAL(clicked()), SLOT(accept()) );
 connect( cancel, SIGNAL(clicked()), SLOT(reject()) );
}
