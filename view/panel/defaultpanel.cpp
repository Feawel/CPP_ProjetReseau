/*
 * defaultpanel.cpp
 *
 *  Created on: 25 nov. 2013
 *      Author: MOULIN
 */

#include "defaultpanel.h"
#include <QFormLayout>

DefaultPanel::DefaultPanel(): QWidget()
{
    addBuildingButton=new QPushButton("Add Building");

    QFormLayout *layout = new QFormLayout;
    layout->addWidget(addBuildingButton);
    this->setLayout(layout);
}

QPushButton* DefaultPanel::getAddBuildingButton()
{
    return addBuildingButton;
}
