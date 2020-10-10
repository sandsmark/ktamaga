/***************************************************************************
    conf.h
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

#ifndef conf_included
#define conf_included

#include "confData.h"

class conf : public confData
{
    Q_OBJECT

public:
    int		lcspeed;
    float	tfact;
    int		tflevel;
    int		dbgreq,resetreq;
    int		sound;

    conf( QWidget* parent = 0, const char* name = 0 );
    int		load( void );
    int		save( void );
    void	prep( void );

    virtual ~conf();

protected slots:
    void	debug1();
    void	debug2();
    void	resetClicked();
    void	okClicked();
    void	cancelClicked();
    void	helpClicked();
};

class dlgsel : public QDialog
{
 Q_OBJECT
public:
	dlgsel( QWidget *parent, const char *name, const char * );
};


#endif // conf_included


