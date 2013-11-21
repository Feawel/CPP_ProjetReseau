/*
 * buildingpanel.cpp
 *
 *  Created on: 20 nov. 2013
 *      Author: MOULIN
 */
#include <QFormLayout>
#include <QSpinBox>

#include "buildingpanel.h"

BuildingPanel::BuildingPanel(): QWidget()
{
    QFormLayout *layout = new QFormLayout;
    QSpinBox *userNumberField= new QSpinBox;
    layout->addRow("User number",userNumberField);
    this->setLayout(layout);
}


