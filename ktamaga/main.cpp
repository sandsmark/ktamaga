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

KApplication *app; 
int app_pause=0;
conf *config;

int main(int argc, char *argv[])
{
  app = new KApplication(argc, argv, "ktamaga");
 
    Ktamaga *ktamaga = new Ktamaga();
    app->setMainWidget( ktamaga );
	    ktamaga->show();

  return app->exec();
}  
