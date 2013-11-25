/*
 * defaultpanel.cpp
 *
 *  Created on: 25 nov. 2013
 *      Author: MOULIN
 */

#ifndef DEFAULTPANEL_H
#define DEFAULTPANEL_H

#endif // DEFAULTPANEL_H

#include <QWidget>
#include <QPushButton>

class DefaultPanel: public QWidget
{
public:
    DefaultPanel();
    QPushButton* getAddBuildingButton();
private:
    QPushButton* addBuildingButton;
};
