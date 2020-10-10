/***************************************************************************
    main.cpp
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

#include "tamagadefs.h"
#include "ktamaga.h"

#ifndef NDEBUG
#include <time.h>
#include <sys/time.h>
void dbgtime(const char *id)
{
    static double lastTime = 0.;
    timespec currtime;
    if (clock_gettime(CLOCK_MONOTONIC_RAW, &currtime) != 0) {
        fprintf(stderr, "failed to get clock\n");
        return;
    }
    // convert to nanoseconds
    const double current = currtime.tv_nsec / (1000. * 1000.) + currtime.tv_sec * 1000.f;
    if (!lastTime) {
        lastTime = current;
        return;
    }
    printf("\t - %.0f\t%s\n", current - lastTime, id);
    //lastTime = current;
}
#endif

KApplication *app; 
int app_pause=0;
conf *config;

int main(int argc, char *argv[])
{
    dbgtime("init");
  app = new KApplication(argc, argv, "ktamaga");
    dbgtime("kapp");
 
    Ktamaga *ktamaga = new Ktamaga();
    dbgtime("Ktamaga");
    app->setMainWidget( ktamaga );
	    ktamaga->show();
    dbgtime("setMainWidget");

  return app->exec();
}  
