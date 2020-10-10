/***************************************************************************
    tlcd.cpp
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

#include "tamagadefs.h"
#include "ktamaga.h"
#include "tlcd.h"

//--------------------------------------------------------

tlcd::tlcd( QWidget *parent, const char *name ) : QWidget( parent, name )
{
 datadir = app->kde_datadir()+TDATADS;

 pbase = new QPixmap();
 pbase->load(datadir+"/tama_base.xpm");
 curan=0;
 framecnt=0;
 fcn=0;
 delt=0;
 debugf=0;
 dpoop=0; dill=0;
 tt = new QTimer( this, "animtimer" );
 connect( tt, SIGNAL(timeout()), SLOT(Nextframe()) );
 tt->start(config->lcspeed);
 ospeed=config->lcspeed;
 specx=0;
 pixml=0;
 pixmr=32-0;
 anrep=0;
 endf=0;
 tphase=0;
 norms=AN_NORML;

 for (int c=0;c<100;c++) pspec[c]=0;
 for (int c=0;c<100;c++) pdat[c]=0;
 pbk = new QPixmap(*pbase);
 setBackgroundPixmap(*pbk);

 loadbase();
}

void tlcd::changeSet( void )
{
 if (ospeed!=config->lcspeed)
  tt->start(config->lcspeed);
 ospeed=config->lcspeed;
}

QPixmap *tlcd::convXpm( char *fname )
{
 QPixmap *pd;
 QFile f;
 char buf2[303];
 char *q,*r,*rb;
 int w,h,sw;
 int c,d,fl;

 f.setName(fname);
 if (f.open(IO_ReadOnly)==FALSE)
  return 0;

// printf("Loading %s\n",fname);
 f.readLine(buf2,200);
 f.readLine(buf2,200);
 q=&buf2[strlen(buf2)-1];
 while (('0'<=*q && *q<='9') || (*q=='\n') || (*q=='\r')) q--;
 q++;
 w=atoi(q);

 f.readLine(buf2,200);
 q=&buf2[strlen(buf2)-1];
 while (('0'<=*q && *q<='9') || (*q=='\n') || (*q=='\r')) q--;
 q++;
 h=atoi(q);
 w/=2; h/=2;
 //printf("W: %d H: %d\n",w,h);

 f.readLine(buf2,200);
 f.readLine(buf2,200);
 f.readLine(buf2,200);
 f.readLine(buf2,200);
 f.readLine(buf2,200);
 f.readLine(buf2,200);
 f.readLine(buf2,200);

  r=rb=(char *)malloc(30000);//w*h*RAX*RAX+h*4+200);
  sprintf(buf2,
   "/* XPM */\n"  
   "static char * xpm_data[] = {\n"
   "\"%d %d 3 1\",\n"
   "\".\tc #FFFFFFFFFFFF\",\n"
   "\"o\tc #C71BC30BC71B\",\n"
   "\"X\tc #000000000000\",\n"
    ,w*RAX,h*RAX);

  strcpy(r,buf2);
  r=&r[strlen(r)];
  sw=w*RAX+4;
  r[sw*h*RAX]=0;

  for ( c=0 ; c<h ; c++ ) {
   for (d=0;d<RAX;d++) {
    r[(c*RAX+d)*sw]='"';
    r[(c*RAX+d)*sw+sw-3]='"';
    r[(c*RAX+d)*sw+sw-2]=',';
    r[(c*RAX+d)*sw+sw-1]='\n'; 
   }
   f.readLine(buf2,300);
   f.readLine(buf2,300);
   for ( d=0; d<w; d++ ) {
    if (buf2[1+d*2]=='a') fl='X'; else fl='o';

    r[1+c*RAX*sw+d*RAX]=fl;
    r[1+c*RAX*sw+d*RAX+1]=fl;
    r[1+c*RAX*sw+d*RAX+2]=fl;
    r[1+c*RAX*sw+d*RAX+3]='.';
    r[1+(c*RAX+1)*sw+d*RAX]=fl;
    r[1+(c*RAX+1)*sw+d*RAX+1]=fl;
    r[1+(c*RAX+1)*sw+d*RAX+2]=fl;
    r[1+(c*RAX+1)*sw+d*RAX+3]='.';
    r[1+(c*RAX+2)*sw+d*RAX]=fl;
    r[1+(c*RAX+2)*sw+d*RAX+1]=fl;
    r[1+(c*RAX+2)*sw+d*RAX+2]=fl;
    r[1+(c*RAX+2)*sw+d*RAX+3]='.';

    r[1+(c*RAX+3)*sw+d*RAX]='.';
    r[1+(c*RAX+3)*sw+d*RAX+1]='.';
    r[1+(c*RAX+3)*sw+d*RAX+2]='.';
    r[1+(c*RAX+3)*sw+d*RAX+3]='.';
   }
  }
  r[strlen(r)-2]=0;
  strcat(r,"};\n");
  f.close();

  pd = new QPixmap();
  pd->loadFromData((unsigned char *)rb,strlen(rb)-1);
  free(rb);

 return pd;
}

//-----------------------------------

void tlcd::loadblock( void )
{
 char buf[303];
 char **p=blnam;
 int cnt=0;
 QFile *f;
 char *r,*q,*qend;
 unsigned int a;
 unsigned char bx[10];

 printf("Loading block %d",tphase);
 sprintf(buf,datadir+"/phase_%d.dat",tphase);
 f = new QFile(buf);
 if (!f->open(IO_Raw|IO_ReadOnly)) {
  printf("\nError opening file %s !\n",buf);
  return;
 }

 q=(char *)malloc(f->size()+1);
 qend=q+f->size();
 f->readBlock(q,f->size());
 f->close();

 r=q;
 for ( ; *p ; p++ ) {
  if (pdat[cnt]) delete pdat[cnt];
  pdat[cnt]=0;
//  if (r>=qend) { cnt++; continue; }
  if (r>=qend) { printf(".%d. ",cnt); cnt++; continue; } 

  memcpy((char *)bx,r,4); r+=4;
  a=bx[2]+bx[3]*256;

  pdat[cnt] = new QPixmap();
  pdat[cnt]->loadFromData((unsigned char *)r,a);
  if (!pdat[cnt]) printf("Pixmapload error cnt=%d !\n",cnt);
  r+=a;

  cnt++;
 }
 free(q);

 printf("\n");
 loadPos();
}

//-----------------------------------

void tlcd::loadbase( void )
{
 char buf[303];
 char **p=specnam;
 int cnt=0;
 QFile *f;
 char *r,*q,*qend;
 unsigned char bx[10];
 unsigned int a;

 printf("Loading base block");
 sprintf(buf,datadir+"/phase_other.dat");
 f = new QFile(buf);

 if (!f->open(IO_Raw|IO_ReadOnly)) {
  printf("\nError opening file %s (doesn't exist?) !\n",buf);
  return;
 }
 q=(char *)malloc(f->size()+1);
 qend=q+f->size();
 f->readBlock(q,f->size());
 f->close();

 r=q;
 for ( ; *p ; p++ ) {
  if (pspec[cnt]) delete pspec[cnt];
  if (r>=qend) { printf(".%d. ",cnt); cnt++; continue; } 

  memcpy((char *)bx,r,4); r+=4;
  a=bx[2]+bx[3]*256;
//  printf("[%d] %c%c Size %d\n",cnt,bx[0],bx[1],a);

  pspec[cnt] = new QPixmap();
  pspec[cnt]->loadFromData((unsigned char *)r,a);
  if (!pspec[cnt]) printf("Pixmapload error cnt=%d !\n",cnt);
  r+=a;

  cnt++;
 }
 free(q);

 printf("\n");
 loadPos();
}


/*
void tlcd::loadbase( void )
{
 char buf[303],buf2[303];
 char **p=specnam;
 int cnt=0;

 printf("Loading base pixmaps\n");
 sprintf(buf,datadir+"/other/");
 for ( ; *p ; p++ ) {
  sprintf(buf2,"%s%s.xpm",buf,*p);
  pspec[cnt] = convXpm(buf2);
  cnt++;
 }
}
*/

void tlcd::setPlays( int hd, int ud )
{
 headd=hd;
 userd=ud;
}

void tlcd::setSNorm( int st )
{
 norms=st;
}


void tlcd::setGameres( int gxhit, int gxmiss )
{
 hit=gxhit;
 miss=gxmiss;
} 

void tlcd::setPhase( int tst )
{
 tphase=tst;
 if (tphase>MAXPHASES) tphase=0;
 loadblock();
}

void tlcd::setNormal( void )
{
 setState(norms);
}

void tlcd::setState( int st )
{
 cframe=-1;
 delt=0;
 ddir=0;
 specx=0;
 curan=st;

 switch (st) {
  case AN_NORML:
  case AN_NORMR:if (!dpoop && !dill)
                 pixmr=32-0;
               break;
  case AN_CLEANUP:
		curan=AN_NORML;
  		specx=AS_CLEAN;
  		anrep=0;
 	       break;
  case AN_CHANGE:
  		curan=AN_NORML;
  		specx=AS_CHANGE;
  		anrep=0;
	       break;
  case AN_DARK:
		curan=AN_NORML;
  		specx=AS_DARK;
	       break;
  case AN_HATCH:
		curan=AN_NORML;
		specx=AS_HATCH;
		anrep=3;
	       break;
  case AN_INFO:
		curan=AN_NORML;
		specx=AN_INFO;
		anrep=0;
	       break;
  case AN_EATMEAL:
		setMeal(1);
		curan=AN_EAT;
	       break;
  case AN_EATSNACK:
		setMeal(0);
		curan=AN_EAT;
	       break;
  case AN_GAMESTART:
		specx=AS_GAMEPRE;
		curan=AN_NORML;
		anrep=3;
	       break;
  case AN_PLAYRES:
		specx=AN_PLAYRES;
		curan=AN_NORML;
		anrep=3;
	       break;
  case AN_GAMERES:
		specx=AS_GAMERES;
		curan=AN_NORML;
		anrep=4;
	       break;
 }
 if (st!=AN_NORML && st!=AN_NORMR)
  Nextframe();
}

//-------------------------

void tlcd::setInfoAnim( int age, int wgt, int hun, int dis, int hap )
{
 inf[IN_AGE]=age;
 inf[IN_WGT]=wgt;
 inf[IN_HUNGRY]=hun;
 inf[IN_DISCL]=dis;
 inf[IN_HAPPY]=hap;
// setAnim(AN_INFO);
}

void tlcd::setDebug( int ison ) { debugf=ison; }
void tlcd::setPoop( int ison ) { dpoop=ison; }

void tlcd::setIll( int ison )
{
 dill=ison;
}

void tlcd::setMeal( int ismeal )
{
 fmeal=ismeal;
}

void tlcd::ShowInfos( void )
{
 int c,d;
  
 if (anrep>0) {
  anrep--;
  return;
 } else {
  anrep=3;
  if (specx==AN_INFOEND) {
   //anrep=0;
   setNormal();
   endf=1;
   return;
  }
 }

 printf("[Inf] %d\n",specx);

 switch (specx) {
  case AN_INFO: // age + wgt
		bitBlt(pbk,3, 3,pspec[AS_AGEWGT]);
		c=inf[IN_AGE]/10; d=inf[IN_AGE]%10;
		if (c) bitBlt(pbk,3+4*11,3+4*2,pspec[AS_SNUM+c]);
		bitBlt(pbk,3+4*16,3+4*2,pspec[AS_SNUM+d]);

		c=inf[IN_WGT]/10; d=inf[IN_WGT]%10;
		if (c) bitBlt(pbk,3+4*11,3+4*8,pspec[AS_BNUM+c]);
		bitBlt(pbk,3+4*16,3+4*8,pspec[AS_BNUM+d]);

	       break;
  case AN_INFO2: // discl
		bitBlt(pbk,3,3,pspec[AS_DISCLTEXT]);
		d=int(inf[IN_DISCL]*13.0/10.0);
		for ( c=0 ; c<d /* max 13 */ ; c++ )
		 bitBlt(pbk,3+4*(3+c), 3+4*11,pspec[AS_DISCLATOM]);
		break;
  case AN_INFO3: // hunger
		bitBlt(pbk,3+4*3, 3+4*1,pspec[AS_HUNGRYTEXT]);
		for ( c=0 ; c<4 ; c++ )
		 bitBlt(pbk,3+4*(0+8*c), 3+4*8,
		  pspec[ c<inf[IN_HUNGRY] ? AS_HEART0 : AS_HEART1]);
		break;
  case AN_INFO4: // happy
		bitBlt(pbk,3+4*3, 3+4*1,pspec[AS_HAPPYTEXT]);
		for ( c=0 ; c<4 ; c++ )
		 bitBlt(pbk,3+4*(0+8*c), 3+4*8,
		  pspec[ c<inf[IN_HAPPY] ? AS_HEART0 : AS_HEART1]);
		break;
 }
 setBackgroundPixmap(*pbk); 
 specx++;
}

void tlcd::loadPos( void )
{
 QFile f;
 char buf[303];
 char *p;
 int cnt=0,c;

 sprintf(buf,datadir+"/position_%d.dat",tphase);
 f.setName(buf);
 if (!f.open(IO_ReadOnly|IO_Translate)) {
   printf("Error loading pos's\n");
   for (c=0;c<100;c++) { andp[c].dx=0; andp[c].dy=0; }
   return;
 } else printf("Loading pos's\n");

 for (cnt=0; !f.atEnd() ; cnt++ ) {
  f.readLine(buf,303);
  //printf("%d\n",cnt);
  p=strtok(buf,", ");
  if (!p) continue;
  andp[cnt].dx=atoi(p);
  p=strtok(0,", ");
  if (!p) continue;
  andp[cnt].dy=atoi(p);
 }
 f.close();
}

void tlcd::savePos( void )
{
 QFile f;
 char buf[303];
 int cnt=0;

 sprintf(buf,datadir+"/position_%d.dat",tphase);
 f.setName(buf);
 if (!f.open(IO_WriteOnly|IO_Truncate)) {
   printf("Error opening/save pos's\n");
   return;
 } else printf("Saving pos's %s\n",buf);

 for (cnt=0; blnam[cnt] ; cnt++ ) {
  sprintf(buf,"%d,%d   (%s)\n",andp[cnt].dx,andp[cnt].dy,blnam[cnt]);
  f.writeBlock(buf,strlen(buf));
 }
 f.close();
}

void tlcd::debugNext( void )
{
 if (!debugf) { cframe=0; debugf=1; 
 } else if (blnam[cframe+1]) cframe++;

 printf("Frame %d [%d,%d] (%s)\n",cframe,andp[cframe].dx,andp[cframe].dy,
  blnam[cframe]);
 StepAnim();
}

void tlcd::debugPrev( void )
{
 if (!debugf) { cframe=0; debugf=1; 
 } else if (cframe>0) cframe--;

 printf("Frame %d [%d,%d] (%s)\n",cframe,andp[cframe].dx,andp[cframe].dy,
  blnam[cframe]);
 StepAnim();
}

void tlcd::debugMove( int dx, int dy )
{
 andp[cframe].dx+=dx;
 andp[cframe].dy+=dy;

 printf("Frame %d [%d,%d] (%s)\n",cframe,andp[cframe].dx,andp[cframe].dy,
  blnam[cframe]);
 StepAnim(); 
}

void tlcd::debugOut( void )
{
 savePos();
}

void tlcd::debugProc( void )
{
  if (pdat[cframe])
   bitBlt(pbk,3+4*andp[cframe].dx, 3+4*andp[cframe].dy,pdat[cframe]);
  setBackgroundPixmap(*pbk);
  return;
}

void tlcd::addSpec( void )
{
 int dxp;
 if (dpoop && curan!=AN_MESS && (curan!=AN_HAPPY && curan!=AN_UNHAPPY &&
   curan!=AN_PLAY)) {
  bitBlt(pbk,3+4*24,3+4*8,pspec[(dpoop==1) ? AS_MESS : AS_MESSLOOP]);
  if (dpoop==1) dpoop++; else dpoop=1;
  pixmr=32-8;
 }

 if (dill && (curan!=AN_HAPPY && curan!=AN_UNHAPPY && curan!=AN_PLAY)) {
  bitBlt(pbk,3+4*27,3,pspec[AS_SKULL]);
  pixmr=32-5;
 }

 if (specx) {
  dxp=0;
  if (specx==AS_ZZZ || specx==AS_ZZZLOOP) 
   dxp=andp[cframe].dx+pdat[cframe]->width()/4;
  bitBlt(pbk,3+4*dxp,3,pspec[specx]);
 }
}

void tlcd::putBase( void )
{
 int dxp;
 if (pdat[cframe]) {
  dxp=0;
  if (curan==AN_NORML || curan==AN_NORMR)
   dxp=delt;
  bitBlt(pbk,3+dxp*4+4*andp[cframe].dx, 3+4*andp[cframe].dy,pdat[cframe]);
 }
}

int tlcd::animStepafter( void )
{
 int nreq=0;

 if (curan==AN_NORML && tphase!=TS_TAMAGOTCHI) {
  delt--;
  if ((delt+andp[cframe].dx-1)<pixml)
   curan=AN_NORMR;
 } else if (curan==AN_NORMR) {
  delt++;
  if ((delt+andp[cframe].dx+pdat[cframe]->width()/4+1)>pixmr)
   curan=AN_NORML;
 }

 if (specx!=0) {
  if (specx==AS_MEALEND) { nreq=1; }
  if (specx==AS_SNACKEND) { nreq=1; }
  if (specx==AS_ZZZLOOP) specx=AS_ZZZ-1;

  if (specx!=0) specx++;
 } 
 return nreq;
}

int tlcd::specPreproc( void )
{
 int dxp;
 if (specx>=AS_CHANGE && specx<=AS_CHANGEEND) {
  bitBlt(pbk,3,3,pspec[specx]);
  setBackgroundPixmap(*pbk);
  if (specx==AS_CHANGEEND) setNormal(); else specx++;
  return 1;  
 }

 if (specx==AS_GAMEPRE) {
  bitBlt(pbk,3,3,pspec[specx]);
  setBackgroundPixmap(*pbk);
  anrep--;
  if (anrep==0) setState(AN_PLAY);
  return 1;  
 }

 if (specx==AS_GAMERES) {
  bitBlt(pbk,3,3,pspec[specx]);
  // + szamok
  
  bitBlt(pbk,3+4*4,3+4*8,pspec[AS_BNUM+hit]);
  bitBlt(pbk,3+4*18,3+4*8,pspec[AS_BNUM+miss]);

  setBackgroundPixmap(*pbk);
  anrep--;
  if (anrep==0) setState( (hit>miss) ? AN_HAPPY : AN_UNHAPPY);
  return 1;  
 }


 if (specx==AN_PLAYRES) {
  dxp=(headd) ? AN_TURNR : AN_TURNL;
  bitBlt(pbk,3+4*andp[dxp].dx,3+4*andp[dxp].dy,pdat[dxp]);
  if (userd)
   bitBlt(pbk,3+4*25,3+4*8,pspec[AS_RIGHTARR]);
  else
   bitBlt(pbk,3+4*1,3+4*8,pspec[AS_LEFTARR]);

  setBackgroundPixmap(*pbk);

  anrep--;
  if (anrep==0) {
   setState((headd==userd) ? AN_HAPPY : AN_UNHAPPY);
  }
  return 1;    
 }

 if (specx==AS_CLEAN) {
  dxp=(4*anrep+2)*4;
  bitBlt(pbk,3+32*4-dxp,3,pspec[AS_CLEAN],0,0,dxp>pspec[AS_CLEAN]->width() ?
   pspec[AS_CLEAN]->width() : dxp,pspec[AS_CLEAN]->height() );
  setBackgroundPixmap(*pbk);

  anrep++;
  if (anrep>7) {
   endf=1;
   setState(AN_NORML);
  }
  return 1;
 } 

 if (specx>=AS_DARK && specx<=AS_DARKZLOOP) { // sotet van
  bitBlt(pbk,3,3,pspec[specx]);
  setBackgroundPixmap(*pbk);
  if (specx==AS_DARKZLOOP) specx=AS_DARKZ; else specx++;
  return 1;
 }

 if (specx==AS_HATCH) {
  printf("Hatch [%d]\n",anrep);
  bitBlt(pbk,3+4*andp[AN_HFRAME].dx,3+4*(andp[AN_HFRAME].dy+(3-anrep)),
   pdat[AN_HFRAME]);
  setBackgroundPixmap(*pbk);
  anrep--;
  if (anrep<=0) {
   endf=1;
   curan=0;
//   specx=0;
   setPhase(tphase+1);
   setState(AN_NORML);
  } 
  return 1;
 }

 if (specx>=AN_INFO && specx<=AN_INFOEND) {
  ShowInfos();
  return 1;
 }

 return 0;
}

int tlcd::isNormal( void )
{
 return ((curan==AN_NORML || curan==AN_NORMR) && (!specx));
}

int tlcd::isPlaying( void )
{
 return( curan==AN_PLAY );
}


int tlcd::initandloop( void )
{
 int nreq=0;

 if (cframe==-1) { // initek
  cframe=ans[curan].start;
  anrep=ans[curan].rep-1;
  if (curan==AN_EAT) { if (fmeal) specx=AS_MEAL; else specx=AS_SNACK; }
  if (curan==AN_SLEEP) specx=AS_ZZZ;
 } else {
  if (cframe>=ans[curan].start+ans[curan].len) {
   if (anrep>0) {
    anrep--;
    cframe=ans[curan].start;
   } else if (anrep==0) {
     nreq=1;
     cframe=ans[curan].start;
     endf=1;
    } else {
     cframe=ans[curan].start;
    }
  }
 }

 return nreq;
}

void tlcd::StepAnim( void )
{
 int nreq=0;
 if (specx!=AS_CLEAN)
  bitBlt(pbk,0,0,pbase);

 if (debugf) { debugProc(); return; }

 if (specPreproc()) return;

 nreq+=initandloop();

 addSpec();
 putBase();

 setBackgroundPixmap(*pbk);

 nreq+=animStepafter();

 cframe++;
 if (nreq) setNormal();
}

void tlcd::Nextframe()
{
 if (debugf) { bitBlt(pbk,0,0,pbase); debugProc(); return; }

 if (app_pause) return;

 framecnt++; fcn++;
 if (!curan)
  return;

/* if (curan>=AN_INFO && curan<=AN_INFO4) {
  ShowInfos(); 
  return;
 }*/ 

 StepAnim();

 if (endf) {
  //printf("debug2\n");
  endf=0;
  emit endState();
 }
}

void tlcd::paintEvent( QPaintEvent* )
{
} 

void tlcd::mousePressEvent( QMouseEvent *ev )
{
 emit clickedX( mapToGlobal(ev->pos()) );
}
