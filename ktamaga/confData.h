/***************************************************************************
    confData.h
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
#ifndef confData_included
#define confData_included

#include <qdialog.h>
#include <qchkbox.h>
#include <qradiobt.h>

class confData : public QDialog
{
    Q_OBJECT

public:

    confData
    (
        QWidget* parent = 0,
        const char* name = 0
    );

    virtual ~confData();

public slots:


protected slots:

    virtual void debug1();
    virtual void helpClicked();
    virtual void cancelClicked();
    virtual void okClicked();
    virtual void resetClicked();
    virtual void debug2();

protected:
    QRadioButton* ts2;
    QRadioButton* ts3;
    QRadioButton* lcs1;
    QRadioButton* lcs2;
    QRadioButton* lcs3;
    QCheckBox* mvt;
    QRadioButton* ts4;
    QRadioButton* ts6;
    QCheckBox* snd;
    QRadioButton* ts5;
    QRadioButton* ts1;

};

#endif // confData_included
