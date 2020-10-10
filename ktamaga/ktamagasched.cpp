/***************************************************************************
    ktamagasched.cpp
                             -------------------
    copyright            : (C) 2000 by Thomas Leineweber
                           (C) 1997 John Zero
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

void Ktamaga::initScheduler( void )
{
 ctime=0;
 ss.npoop=SREINIT;
 ss.nill=SREINIT;
 ss.nsleep=SREINIT;
 ss.nhappy=SREINIT; 
 ss.neat=SREINIT;
 ss.nwake=SPAUSE;
 ss.nhatch=ctime+(long int)(1.0*config->tfact); // hatch in 1 minute
 ss.ndiscl=SREINIT;
 ss.tsave=0;
 ss.attn=0;
 ss.ars=0;
 ss.tgrow=SREINIT;
 ss.tinphase=0;
 
 pd=&psd[1]; // test
}

void Ktamaga::advphase( void )
{
 int svp=st.phase;

 ss.tinphase++;
 switch (st.phase) {
//  case TS_TAMAGOTCHI
  case TS_BABITCHI:if (ss.tinphase>=2)
                    st.phase=TS_MARUTCHI;
                  break;
  case TS_MARUTCHI:if (ss.tinphase>=3) {
		    if ((st.happy < 2) || (st.miscare > 10))
		     st.phase=TS_TAMATCHI;
		    else
                     st.phase=TS_KUCHITAMACHI;
                   }
                  break;

  case TS_TAMATCHI:if (ss.tinphase>=3) {
                    if ((st.wgt<32) && (st.miscare < 10) && (st.fedplg<2))
  		     st.phase=TS_MAMETCHI;
		    else
  		     if ((st.invdispl>9) && (st.miscare > 4))
                      st.phase=TS_MASKTCHI;
                     else
                      st.phase=TS_GINJIROTCHI;
                   }
                  break;
  case TS_KUCHITAMACHI:
                   if (ss.tinphase>=3) {
		    if ((st.miscare>17))
		     st.phase=TS_NYOROTCHI;
 		    else
                     if ((st.miscare<6) && (st.nodispl>=2))
 		      st.phase=TS_TARAKOTCHI;
		     else
                      st.phase=TS_KUCHIPATCHI;
                   }
                  break;
  case TS_GINJIROTCHI:
                  break;
  case TS_MASKTCHI:// should conditionally adv. to gainjinchi
                  break;
  case TS_KUCHIPATCHI:
                  break;
  case TS_TARAKOTCHI:
                  break;
  case TS_MAMETCHI:
                  break;
  case TS_NYOROTCHI:
                  break;

  case TS_GAIJINTCHI:
                  break;
 }
 if (svp!=st.phase) {
  scr->setState(AN_CHANGE);
  scr->setPhase(st.phase);
  app->beep();
  ss.tinphase=0;
 }
}

void Ktamaga::startScheduler( void )
{
 tx = new QTimer( this, "animtimer" );
 connect( tx , SIGNAL(timeout()), SLOT(schedTick()) );

 tx->start(TS_TICK);
}
 
void Ktamaga::schedTick( void )
{
 if (app_pause) return;

 pd=&psd[1]; // test
 ctime++;
 scheduler();
}

#define CLTIME(x,y)	(long int)( ctime+config->tfact*randf((x),(y)) )

void Ktamaga::schedReinit( void )
{
 if (ss.npoop==SREINIT) ss.npoop=CLTIME(pd->poopf,pd->poopt);
 if (ss.nill==SREINIT) ss.nill=CLTIME(pd->illf,pd->illt);
 if (ss.nsleep==SREINIT) ss.nsleep=CLTIME(pd->sleepf,pd->sleept);
 if (ss.nwake==SREINIT) ss.nwake=CLTIME(pd->slf,pd->slt);
 if (ss.nhappy==SREINIT) ss.nhappy=CLTIME(pd->happycf,pd->happyct);
 if (ss.neat==SREINIT) ss.neat=CLTIME(pd->foodcf,pd->foodct);
 if (ss.ndiscl==SREINIT) ss.ndiscl=CLTIME(pd->disclf,pd->disclt);
 if (ss.tgrow==SREINIT) ss.tgrow=(long int)(ctime+config->tfact*60); // test
}
                     
//----------------------------------

#define HEARTX(x) ((x>3)?"[####]" : (x>2) ? "[###.]" : \
		  (x>1) ? "[##..]" : (x>0) ? "[#...]" : "[....]")
#define TMX(x) 		((x)>0) ? (int)((x)/60):0,((x)>0) ? \
			(int)((x)%60):(int)x

void Ktamaga::debugstat( void )
{
 /* printf("%ld [Poop %ld,Ill %ld, Sleep/W: %ld/%ld, att %ld, eat/happy %ld/%ld,"
  "food %d, happy %d :%d:]\n",
  ctime,ss.npoop,ss.nill,ss.nsleep,ss.nwake,ss.attn,ss.neat,ss.nhappy,
  st.hungry,st.happy,ss.ars); */

 printf("\n [Time: %2d:%02d]\n",(int)ctime/60,(int)ctime%60);
 printf(  " [Poop: %2d:%02d   Ill: %2d:%02d   Discl: %2d:%02d   Attn,ars: %ld :%d:\n",
	TMX(ss.npoop),TMX(ss.nill),TMX(ss.ndiscl),ss.attn,ss.ars);
 printf(  " [Sleep: %2d:%02d -Wake %2d:%02d   Hungry: %2d:%02d Happy: %2d:%02d"
	   " Grow: %2d:%02d\n",
	TMX(ss.nsleep), TMX(ss.nwake), TMX(ss.neat), TMX(ss.nhappy),
	TMX(ss.tgrow) );
 printf(  " [Hungry: %s Happy: %s Discl: %d%%\n",
	HEARTX(st.hungry),HEARTX(st.happy),st.discl );
}

#define TIMEFOR(x)	((ctime>x) && (x>0))

void Ktamaga::scheduler( void )
{
 if ((ss.ars!=AR_NONE) && (!ss.attn)) { 
  ss.attn=1;
  setAttButt(1);
 } else if (ss.attn) {
  if (ss.ars==AR_NONE) {
   ss.attn=0;
   setAttButt(0);
  } else {
   needAttention();
   ss.attn++;
   if ((ss.attn>20) && (ss.ars&AR_NOREASON)) {
    ss.ars^=AR_NOREASON;
    st.nodispl++;
   }
   if (ss.attn==30) st.miscare++;
   if (ss.attn==60) st.miscare+=2;
   if (ss.attn==120) st.miscare+=3;
  }
 }

 if ((ss.ars&AR_UNHAPPY) && st.happy>0) {
   ss.ars^=AR_UNHAPPY;
   ss.nhappy=SREINIT;
 }
 if ((ss.ars&AR_HUNGRY) && st.hungry>0) {
   ss.ars^=AR_HUNGRY;
   ss.neat=SREINIT;
 }

 if (ctime%10==0) debugstat();

 //-----------------------------------
 
 if (TIMEFOR(ss.tgrow)) {
  st.age++;
  
  advphase();
//  scr->setState(AN_CHANGE);
//  scr->setPhase(++st.phase);
//  app->beep();
  ss.tgrow=SREINIT;
 }

 if (TIMEFOR(ss.npoop)) {
  if (!scr->isNormal()) {
   ss.npoop+=randx(4,19);
  } else {
   ss.npoop=-2;
   scr->setState(AN_MESS); 
   scr->setPoop(1); st.poop=1; 
   ss.ars|=AR_MESS;
  }
 }

 if (TIMEFOR(ss.ndiscl)) {
  if (!scr->isNormal()) {
   ss.ndiscl+=randx(4,15);
  } else {
   ss.ars|=AR_NOREASON;
   ss.ndiscl=SREINIT;
  }
 }


 if (TIMEFOR(ss.nill)) {
  if ( (!scr->isNormal()) || (st.poop) ) {
   ss.nill+=randx(4,22);
  } else {
   ss.nill=SPAUSE;
   scr->setState(AN_SICK);
   scr->setIll(1); st.ill=randx(1,10); if (st.ill>2) st.ill=1;
   ss.ars|=AR_ILL;
  }
 } 

 if (TIMEFOR(ss.nwake)) {
  scr->setSNorm(AN_NORML);
  scr->setNormal();
  ss.nsleep=SREINIT; ss.nwake=SPAUSE;
  st.sleeping=0;
  st.lights=1;
 }

 if (TIMEFOR(ss.nsleep)) {
  if ( (!scr->isNormal()) || (st.poop) || (st.ill)) {
   ss.nsleep+=randx(10,24);
  } else {
   scr->setSNorm(AN_SLEEP);
   scr->setNormal(); st.sleeping=1;
   ss.nwake=SREINIT; //ctime+randx(30,60);
   ss.nsleep=SPAUSE;
  }
 }

 if (ctime>ss.nhatch && ss.nhatch) {
  if (ss.ars&AR_HATCH) ss.ars^=AR_HATCH;
  ss.nhatch=0;
  scr->setState(AN_HATCH);
  st.phase++; // auto.sync in AN_HATCH 
  st.age++;
  app->beep();
 }

 if (ctime+10>ss.nhatch && ss.nhatch) {
  ss.ars=AR_HATCH;
  //if (ctime%2==0)
  // app->beep();
 }

 if (TIMEFOR(ss.nhappy)) {
  if (st.sleeping) {
   ss.nhappy+=5;
  } else {
   if (st.happy) {
    st.happy--;
    ss.nhappy=SREINIT;
   } else {
    ss.ars|=AR_UNHAPPY;
    ss.thappy=ctime;
    ss.nhappy=SPAUSE; 
    st.fedplg++;
   }
  }
 }

 if (TIMEFOR(ss.neat)) {
  if (st.sleeping) {
   ss.neat+=35;
  } else {
   if (st.hungry) {
    st.hungry--;
    ss.neat=SREINIT;
   }
   if (!st.hungry) {
    ss.ars|=AR_HUNGRY;
    ss.teat=ctime;
    ss.neat=SPAUSE;
    st.fedplg++;
   }
  }
 }

 if (ctime>ss.tsave+60) {
  ss.tsave=ctime;
  saveTama();
 }

 schedReinit();
}

