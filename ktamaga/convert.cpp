/***************************************************************************
    convert.cpp
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
#include "tamdata.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
       
#include <qpixmap.h>
#include <qfile.h>

void convaddXpm( char *fname, QFile *g )
{
 QFile f;
 char buf2[303];
 char *q,*r,*rb;
 int w,h,sw;
 int c,d,fl;
 unsigned long fs;

 f.setName(fname);
 if (f.open(IO_ReadOnly)==FALSE) {
  //printf(" Error %s\n",fname);
  return;
 }

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

  r=rb=(char *)malloc(30000);
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

 unsigned char bx[10];  
 fs=strlen(rb)-1;
 bx[0]='J'; bx[1]='0'; bx[2]=fs%256; bx[3]=(fs/256)%256;

 //printf("Size: %d, %d\n",fs,bx[2]+bx[3]*256);
 g->writeBlock((char *)bx,4 );
 g->writeBlock(rb,fs);
 //pd = new QPixmap();
 //pd->loadFromData((unsigned char *)rb,strlen(rb)-1);
 free(rb);

 //return pd;
}

//-----------------------------------

void convblock( char *bn, int sp=0 )
{
 char buf[303],buf2[303];
 char **p=blnam;
 int cnt=0;
 QFile *g;
 
 if (sp) p=specnam;

 sprintf(buf,"data/phase_%s.dat",bn);
 g=new QFile(buf);

 g->open(IO_ReadWrite|IO_Truncate|IO_Raw);

 printf("Converting block %s... ",bn);
 sprintf(buf,"datapre/%s/",bn);
 for ( ; *p ; p++ ) {
  sprintf(buf2,"%s%s.xpm",buf,*p);
  //printf(" %s\n",buf2);
  convaddXpm(buf2,g);
  cnt++;
 }
 g->close();
 printf("done\n");
}


int main( int, int )
{
 convblock("0");
 convblock("1");
 convblock("2");
 convblock("3");
 convblock("4");
 convblock("5");
 convblock("6");
 convblock("7");
 convblock("8");
 convblock("9");
 convblock("10");
 convblock("11");
 convblock("other",1);
}
