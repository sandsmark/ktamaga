/***************************************************************************
    ktamaga.cpp
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

//---------------------------------------------------
void Ktamaga::dbgWrite() { scr->debugOut(); }
void Ktamaga::dbgCancel() 
{
 scr->setDebug(0);
 setButt(BS_NORMAL);
 scr->setSNorm(AN_NORML);
 scr->setNormal();
 app_pause=0;
}
void Ktamaga::dbgPrev() { scr->debugPrev(); }
void Ktamaga::dbgNext() { scr->debugNext(); }
void Ktamaga::dbgLeft() { scr->debugMove(-1,0); }
void Ktamaga::dbgUp()   { scr->debugMove(0,-1); }
void Ktamaga::dbgDown() { scr->debugMove(0, 1); }
void Ktamaga::dbgRight(){ scr->debugMove(1, 0); }
//----------------------------------------------------

void Ktamaga::feedMeal()
{
 setButt( BS_NORMAL );
 if (((randx(1,10)<=2) && !st.hungry) || (st.bad)) { // test
  scr->setState(AN_NEGATIVE);
  st.bad=1;
  return;
 }

 if (st.hungry>3) {
  scr->setState(AN_NEGATIVE);
  return;
 }

 scr->setState(AN_EATMEAL);
 st.hungry+=2;
 st.wgt++;
 if (ss.neat==SPAUSE) ss.neat=SREINIT;
 if (ss.ars & AR_HUNGRY) ss.ars^=AR_HUNGRY;
}

void Ktamaga::feedSnack()
{
 setButt( BS_NORMAL );
 if (((randx(1,10)<=2) && !st.hungry) || (st.bad)) {// test  
  scr->setState(AN_NEGATIVE);
  st.bad=1;
  return;
 }

 if (st.hungry>3) {
  scr->setState(AN_NEGATIVE);
  return;
 }

 scr->setState(AN_EATSNACK);
 st.hungry++;
 st.happy++;
 st.wgt+=2;
 if (ss.neat==SPAUSE) ss.neat=SREINIT;
 if (ss.ars & AR_HUNGRY) ss.ars^=AR_HUNGRY;
}

void Ktamaga::feedCancel()
{
 setButt( BS_NORMAL );
}

//---------------

void Ktamaga::gameCancel()
{
 setButt( BS_NORMAL );
 scr->setSNorm(AN_NORML);
 scr->setNormal();
}

void Ktamaga::gameLeft()
{
 int dr=randx(0,11)%2;

 if (!scr->isPlaying())
  return;

 addContGame( (dr==0) );
 scr->setPlays(dr,0);
 scr->setState(AN_PLAYRES);
}

void Ktamaga::gameRight()
{
 int dr=randx(0,11)%2;

 if (!scr->isPlaying())
  return;

 addContGame( (dr==1) );
 scr->setPlays(dr,1);
 scr->setState(AN_PLAYRES);
}

void Ktamaga::addContGame( int pos )
{
 ngame++;
 if (pos) ghit++;
 if (ngame>=5) {
  streq=AN_GAMERES;
  scr->setGameres(ghit,ngame-ghit);
  if (ghit>2) st.happy+=2; else st.happy--;
  ngame=0; ghit=0;
  st.wgt--;
 }
}

//---------------

void Ktamaga::feedClicked()
{
 if (!scr->isNormal())
  return;
 
 setButt( BS_FEED );
}

void Ktamaga::lightsClicked()
{
 if (st.lights) {
  if (st.sleeping) {
   st.lights=0;
   scr->setSNorm(AN_DARK);
   scr->setNormal();
   //scr->setState(AN_DARK); 
  }
 } else {
  scr->setSNorm(st.sleeping ? AN_SLEEP : AN_NORML);
  scr->setNormal();
  st.lights=1;
 } 
}

void Ktamaga::gameClicked()
{
 if (!scr->isNormal())
  return;
 ngame=0; ghit=0;
 setButt( BS_PLAY );
 scr->setSNorm(AN_PLAY);
 scr->setState(AN_GAMESTART);
}

void Ktamaga::medicalClicked()
{
 if (st.ill==0) return; 

 st.ill--;
 st.happy++;

 if (st.ill==0) {
  scr->setIll(st.ill);
  scr->setState(AN_HAPPY);
  ss.nill=SREINIT;
  if (ss.ars & AR_ILL) ss.ars^=AR_ILL;
 }
}

void Ktamaga::toiletClicked()
{
 if (!st.poop) return;
 
 scr->setState(AN_CLEANUP);
 st.poop=0; ss.npoop=SREINIT;
 scr->setPoop(0);
 if (ss.ars & AR_MESS) ss.ars^=AR_MESS;
 streq=AN_HAPPY;
 st.happy++;
}

void Ktamaga::statusClicked()
{
 scr->setInfoAnim(st.age, st.wgt, st.hungry, st.discl, st.happy );
 scr->setState(AN_INFO);
}

void Ktamaga::teachClicked()
{
 if ((ss.ars & AR_NOREASON) || (st.bad)) { 
  // the right branch

  if (ss.ars&AR_NOREASON) ss.ars^=AR_NOREASON;
  st.discl+=3;
  st.bad=0;
  st.invdispl--;
  st.miscare--;
  setAttButt(0);
 } else {
  if (st.discl>0)
   st.discl-=2;
  if (st.discl<0)
   st.discl=0;
  scr->setState(AN_UNHAPPY);
  st.happy--;
  st.invdispl+=3;
  st.miscare+=2;
 }
 st.nodispl--;
}

void Ktamaga::attentionClicked()
{
 //scr->setPhase(++st.phase);
 //scr->setNormal();
}

void Ktamaga::resizeEvent( QResizeEvent * )
{
 ;
}
