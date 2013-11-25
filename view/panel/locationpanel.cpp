/*
 * locationpanel.cpp
 *
 *  Created on: 20 nov. 2013
 *      Author: MOULIN
 */
#include "locationpanel.h"
#include <QVBoxLayout>

LocationPanel::LocationPanel(): QWidget()
{
    layout = new QFormLayout;
    QSpinBox* defaultUserNumberField= new QSpinBox;
    QSpinBox* supUserNumberField= new QSpinBox;
    QSpinBox* adminUserNumberField= new QSpinBox;
    layout->addRow("Default user number",defaultUserNumberField);
    layout->addRow("Sup user number",supUserNumberField);
    layout->addRow("Admin user number",adminUserNumberField);

    userNumberFields.push_back(defaultUserNumberField);
    userNumberFields.push_back(supUserNumberField);
    userNumberFields.push_back(adminUserNumberField);

    QGroupBox* cantUseTechsGroup = new QGroupBox;
    QVBoxLayout* cantUseTechsLayout = new QVBoxLayout;
    QCheckBox* wifiCheck = new QCheckBox("Wifi:");
    QCheckBox* infraredCheck = new QCheckBox("Infrared:");
    QCheckBox* fiberCheck = new QCheckBox("Fiber:");
    QCheckBox* ethernetCheck = new QCheckBox("Ethernet:");
    QCheckBox* twistedPairCheck = new QCheckBox("Twisted Pair:");
    cantUseTechsLayout->addWidget(wifiCheck);
    cantUseTechsLayout->addWidget(infraredCheck);
    cantUseTechsLayout->addWidget(fiberCheck);
    cantUseTechsLayout->addWidget(ethernetCheck);
    cantUseTechsLayout->addWidget(twistedPairCheck);

    cantUseTechsGroup->setLayout(cantUseTechsLayout);

    layout->addRow("Can't use technologies:", cantUseTechsGroup);

    this->setLayout(layout);
}

QSpinBox* LocationPanel::getUserNumberField(NUserType::UserType userType)
{
    int index = userType;
    return userNumberFields[index];
}


