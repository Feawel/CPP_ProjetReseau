/*
 * buildingpanel.cpp
 *
 *  Created on: 20 nov. 2013
 *      Author: MOULIN
 */
#include <QFormLayout>
#include <QSpinBox>

#include "buildingpanel.h"

BuildingPanel::BuildingPanel(): QWidget(), userNumberFields(3)
{
    QFormLayout *layout = new QFormLayout;
    QSpinBox* defaultUserNumberField= new QSpinBox;
    QSpinBox* supUserNumberField= new QSpinBox;
    QSpinBox* adminUserNumberField= new QSpinBox;
    layout->addRow("Default user number",defaultUserNumberField);
    layout->addRow("Sup user number",supUserNumberField);
    layout->addRow("Admin user number",adminUserNumberField);
    this->setLayout(layout);

    userNumberFields.push_back(defaultUserNumberField);
    userNumberFields.push_back(supUserNumberField);
    userNumberFields.push_back(adminUserNumberField);
}

QSpinBox* BuildingPanel::getUserNumberField(NUserType::UserType userType)
{
    return userNumberFields[userType];
}


