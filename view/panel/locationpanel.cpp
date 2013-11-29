/*
 * locationpanel.cpp
 *
 *  Created on: 20 nov. 2013
 *      Author: MOULIN
 */
#include "locationpanel.h"
#include <QVBoxLayout>
#include <limits>

using namespace std;

LocationPanel::LocationPanel(): QWidget()
{
    layout = new QFormLayout;
    QSpinBox* defaultUserNumberField= new QSpinBox;
    defaultUserNumberField->setMaximum(numeric_limits<int>::max());
    layout->addRow("Default user number",defaultUserNumberField);

    QSpinBox* supUserNumberField= new QSpinBox;
    supUserNumberField->setMaximum(numeric_limits<int>::max());
    layout->addRow("Sup user number",supUserNumberField);

    QSpinBox* adminUserNumberField= new QSpinBox;
    adminUserNumberField->setMaximum(numeric_limits<int>::max());
    layout->addRow("Admin user number",adminUserNumberField);

    // editable only on an admin building
    adminUserNumberField->setEnabled(false);

    userNumberFields.push_back(defaultUserNumberField);
    userNumberFields.push_back(supUserNumberField);
    userNumberFields.push_back(adminUserNumberField);

    QGroupBox* cantUseTechsGroup = new QGroupBox;
    QVBoxLayout* cantUseTechsLayout = new QVBoxLayout;
    QCheckBox* wifiCheck = new QCheckBox("Wifi:");
    QCheckBox* ethernetCheck = new QCheckBox("Ethernet:");
    cantUseTechsLayout->addWidget(wifiCheck);
    cantUseTechsLayout->addWidget(ethernetCheck);

    cantUseTechsGroup->setLayout(cantUseTechsLayout);

    layout->addRow("Can't use technologies:", cantUseTechsGroup);

    this->setLayout(layout);
}

LocationPanel::~LocationPanel()
{
    delete layout;
    for(unsigned int i = 0; i< userNumberFields.size(); i++)
    {
        delete userNumberFields[i];
    }
}

QSpinBox* LocationPanel::getUserNumberField(NUserType::UserType userType)
{
    int index = userType;
    return userNumberFields[index];
}


