/***************************************************************************
    ktamagastat.cpp
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

#include "ktamaga.h"
#include "conf.h"

//----------

Ktamaga::Ktamaga( QWidget *parent, const char *name )
        : QWidget( parent, name )
{
 int	 c; 
 QString s;

 initVars();

 cont = new QWidget( this );

 bp.load(config->datadir+"/bg1.xpm");
 
 for (c=0;c<B_MAX;c++)
  pcont[c].load((config->datadir+"/")+icnam[c]);

 createWidgets();
 setCaption("Tamaga");
 placeWidgets();

 initScheduler(); // must come before loadtama
 if (!loadTama())
  resetTama();

 startTama();
 startScheduler();
}

Ktamaga::~Ktamaga( void )
{
 saveTama();
}

void Ktamaga::createMenu( void )
{
 menu = new KMenuBar(cont,"Tamaga");
 pmenu = new QPopupMenu;
 pmenu->insertItem(i18n("&Configure..."),this,SLOT(configMenu()),ALT+Key_C);
 pmenu->insertSeparator();
 pmenu->insertItem( i18n("&Help"), this, SLOT(launchHelp()), ALT+Key_H);
 pmenu->insertItem( i18n("&About"), this, SLOT(aboutClicked()));
 pmenu->insertSeparator();
 pmenu->insertItem(i18n("&Quit"),qApp,SLOT(quit()),ALT+Key_Q ); 
}

void Ktamaga::createWidgets( void )
{
 createMenu();
 createButt();
 scr = new tlcd( cont, "lcdmain" );
 cont->setBackgroundPixmap(bp);
 connect( scr, SIGNAL(endState()), SLOT(stateEnded()) );
 connect( scr, SIGNAL(clickedX( QPoint )), SLOT(popmenu( QPoint )) );
}
 
void Ktamaga::placeWidgets( void )
{
 int ix=147,iy=142,c;

 scr->disconnect( this, SLOT(popmenu( QPoint )) );

 menu->show();
 menu->hide();

 connect( scr, SIGNAL(clickedX( QPoint )), SLOT(popmenu( QPoint )) );

 for (c=0;c<8;c++)
  bcont[c]->move( 5+35*(c%4), 5+int(c/4)*105 );

 scr->setGeometry(5,35,133,70);

 menu->resize( ix, menu->height());

 cont->setFixedSize(ix,iy);
 setFixedSize(ix,iy);
 resize(ix,iy); 
}

void Ktamaga::configMenu( )
{
 int fl=0;
 app_pause=1;
 
 config->prep();
 if ( config->exec() ) {
  scr->changeSet();
  if (config->dbgreq==1) scr->setPhase(++st.phase);
  if (config->dbgreq==2) { scr->setDebug(1); setButt(BS_DEBUG); 
                           app_pause=1; fl=1; }
  config->dbgreq=0;

  if (config->resetreq) {
   config->resetreq=0;
   resetTama();
   startTama();
   initScheduler();
  }
 }
 
 if (!fl)
  app_pause=0;
}


void Ktamaga::aboutClicked()
{
 app_pause=1;
 KMsgBox::message(0,
                  i18n("About"),
                  ABOUT_MSG,
                  KMsgBox::INFORMATION,
                  i18n("OK"));
 app_pause=0;
}

void Ktamaga::launchHelp()
{
 app_pause=1;
 app->invokeHTMLHelp("ktamaga/ktamaga.html", "");
 app_pause=0;
}

QPushButton *Ktamaga::makeButton( int x, int y, int w, int h, const char *n,
 QPixmap *pix=0, char *tip=0 )
{
   QPushButton *pb = new QPushButton( n, cont );
   pb->setGeometry( x, y, w, h );
   pb->setAutoRepeat(FALSE);
   if (pix) pb->setPixmap(*pix);
   if (tip) QToolTip::add( pb, tip );
   return pb;
} 

void Ktamaga::changeCButton( int ind, QPixmap *pix=0, const char *tip=0 )
{
 QPushButton *pb=bcont[ind];
 if (pix) pb->setPixmap(*pix);
 if (tip) QToolTip::add( pb, tip );
} 

void Ktamaga::setAttButt( int on )
{
 bcont[7]->setPixmap( on ? pcont[B_ATTLIGHT] : pcont[B_ATTNORM] );
}

void Ktamaga::createButt( void )
{
 int c;

 for (c=0;c<8;c++)
  bcont[c] = makeButton( 5+35*(c%4), 0+5+int(c/4)*105, 30, 26, "Cntlx" );
}

void Ktamaga::setButt( int st )
{
 printf("SetButt [%d]\n",st);
 int c;
 if (curst==0) {
 } else {
  for (c=0;c<8;c++)
   bcont[c]->disconnect(this);
 }

 curst=st;
 switch (st) {
  case BS_NORMAL:
		for (c=0;c<8;c++)
    		 changeCButton( c, &pcont[c], i18n(ictip[c]) );
		if (ss.ars)
		 setAttButt(1);

	 	connect( bcont[0], SIGNAL(clicked()), SLOT(feedClicked()) );
 		connect( bcont[1], SIGNAL(clicked()), SLOT(lightsClicked()) );
 		connect( bcont[2], SIGNAL(clicked()), SLOT(gameClicked()) );
 		connect( bcont[3], SIGNAL(clicked()), SLOT(medicalClicked()) );
 		connect( bcont[4], SIGNAL(clicked()), SLOT(toiletClicked()) );
 		connect( bcont[5], SIGNAL(clicked()), SLOT(statusClicked()) );
 		connect( bcont[6], SIGNAL(clicked()), SLOT(teachClicked()) );
 		connect( bcont[7], SIGNAL(clicked()), SLOT(attentionClicked()) );
	       break;

  case BS_DEBUG:
		changeCButton( 0, &pcont[B_CANCEL], i18n(ictip[B_CANCEL]));
		for (c=0;c<7;c++)
    		 changeCButton( 1+c, &pcont[B_DEBUGSET+c], i18n(ictip[B_DEBUGSET+c]) );

	 	connect( bcont[0], SIGNAL(clicked()), SLOT(dbgCancel()) );
 		connect( bcont[1], SIGNAL(clicked()), SLOT(dbgWrite()) );
		connect( bcont[2], SIGNAL(clicked()), SLOT(dbgPrev()) );
 		connect( bcont[3], SIGNAL(clicked()), SLOT(dbgNext()) );
 		connect( bcont[4], SIGNAL(clicked()), SLOT(dbgLeft()) );
 		connect( bcont[5], SIGNAL(clicked()), SLOT(dbgUp()) );
 		connect( bcont[6], SIGNAL(clicked()), SLOT(dbgDown()) );
 		connect( bcont[7], SIGNAL(clicked()), SLOT(dbgRight()) );
	       break;
 
  case BS_PLAY:	
    		changeCButton( 0, &pcont[B_CANCEL], i18n(ictip[B_CANCEL]) );
    		changeCButton( 1, &pcont[B_TLEFT], i18n(ictip[B_TLEFT]) );
    		changeCButton( 2, &pcont[B_TRIGHT], i18n(ictip[B_TRIGHT]) );
		for (c=0;c<5;c++)
		 changeCButton( 3+c, &pcont[B_NULL], i18n(ictip[B_NULL]) );

	 	connect( bcont[0], SIGNAL(clicked()), SLOT(gameCancel()) );
 		connect( bcont[1], SIGNAL(clicked()), SLOT(gameLeft()) );
 		connect( bcont[2], SIGNAL(clicked()), SLOT(gameRight()) );

	       break; 
  case BS_FEED:
		for (c=0;c<4;c++)
    		 changeCButton( c, &pcont[B_EATSET+c], i18n(ictip[B_EATSET+c]) );
		for (c=0;c<4;c++)
		 changeCButton( 4+c, &pcont[B_NULL], i18n(ictip[B_NULL]) );

	 	connect( bcont[0], SIGNAL(clicked()), SLOT(feedCancel()) );
 		connect( bcont[1], SIGNAL(clicked()), SLOT(feedMeal()) );
 		connect( bcont[2], SIGNAL(clicked()), SLOT(feedSnack()) );
               break;
 }
}


void Ktamaga::stateEnded( void )
{
 printf("StateEnd [%d]\n",streq);
 if (streq) {
  scr->setState(streq);
  streq=0;
 } else {
  if (streq2) {
   scr->setState(streq2);
   streq2=0;
  }
 }
}

void Ktamaga::needAttention( void )
{
 // if /dev/dsp exists/can be opened, then this should emit a sound... etc.
 if (!config->sound) return;
 
 if (ss.ars&AR_HATCH) {
  if (ctime%2==0)
   app->beep();
  return;
 } 

 if (ss.attn==5 || ss.attn==10 || ss.attn==20 || ss.attn==40)
  app->beep();
}

int Ktamaga::loadTama( void )
{
 QFile	f(saveName);
 if (f.open(IO_Raw|IO_ReadOnly)==FALSE) 
  return 0;
 f.readBlock((char *)&st,sizeof(st));
 f.readBlock((char *)&ss,sizeof(ss));
 ctime=ss.ctimetmp;
 f.close();
 return 1;
}

int Ktamaga::saveTama( void )
{
 QFile	f(saveName);

 printf("[Autosave %s]\n",saveName.data());
 if (f.open(IO_Raw|IO_WriteOnly|IO_Truncate)==FALSE) 
  { printf("[!Save error!!!]\n"); return 0; }
 ss.ctimetmp=ctime;
 f.writeBlock((char *)&st,sizeof(st));
 f.writeBlock((char *)&ss,sizeof(ss));
 f.close();
 return 1;
}

void Ktamaga::resetTama( void )
{
 st.sleeping=0;
 st.lights=1;
 st.ill=0;
 st.hungry=2;
 st.happy=2;
 st.poop=0;
 st.ill=0;
 st.phase=TS_TAMAGOTCHI;
 st.bad=0;
 st.miscare=0;
 st.invdispl=0;
 st.fedplg=0;
 st.nodispl=0;

 st.age=0;
 st.wgt=5;
 st.discl=0; 
}

void Ktamaga::startTama( void )
{
 streq=0;
 streq2=0;

 setButt(BS_NORMAL);
 scr->setPoop(st.poop);
 scr->setIll(st.ill);
 scr->setPhase(st.phase); 
 scr->setSNorm(AN_NORML);
 scr->setNormal();
}

void Ktamaga::initVars( void )
{
 curst=0;

 saveName=getenv("HOME");
 CHECK_PTR(saveName);
 saveName+=TAMDATFILE;

 config = new conf;
 config->load();
}

int Ktamaga::randx( int from, int to )
{
 return ( from  + (int)(float(to)*rand()/RAND_MAX) );
}   

float Ktamaga::randf( float from, float to )
{
 return ( from  + (to*rand()/RAND_MAX) );
}   


void Ktamaga::popmenu( QPoint p )
{
 pmenu->popup(p);
}
