/*
 * b2bpanel.cpp
 *
 *  Created on: 25 nov. 2013
 *      Author: MOULIN
 */

#include <QFormLayout>
#include <QVBoxLayout>
#include <QGroupBox>

#include "b2bpanel.h"

Building_BuildingPanel::Building_BuildingPanel(): QWidget()
{
    distanceField = new QDoubleSpinBox;

    existingTechFields(4);
    QGroupBox* existingTechsGroup = new QGroupBox;
    QVBoxLayout* existingTechsLayout = new QVBoxLayout;

    QCheckBox* fiberCheck = new QCheckBox("Fiber:");
    existingTechFields[NTechnology::FIBER]=fiberCheck;
    existingTechsLayout->addWidget(fiberCheck);

    QCheckBox* twistedPairCheck = new QCheckBox("Twisted Pair:");
    existingTechFields[NTechnology::TWISTEDPAIR]=twistedPairCheck;
    existingTechsLayout->addWidget(twistedPairCheck);

    QCheckBox* wifiCheck = new QCheckBox("Wifi Bridge:");
    existingTechFields[NTechnology::WIFI]=wifiCheck;
    existingTechsLayout->addWidget(wifiCheck);

    QCheckBox* infraredCheck = new QCheckBox("Infrared:");
    existingTechFields[NTechnology::INFRARED]=infraredCheck;
    existingTechsLayout->addWidget(infraredCheck);

    existingTechsGroup->setLayout(existingTechsLayout);

    QFormLayout *layout = new QFormLayout;
    layout->addRow("Distance (m):", distanceField);
    layout->addRow("Existing technologies:", existingTechsGroup);

    this->setLayout(layout);
}

Building_BuildingPanel::~Building_BuildingPanel()
{
    delete distanceField;
}


QDoubleSpinBox* Building_BuildingPanel::getDistanceField() const
{
    return distanceField;
}

QCheckBox* Building_BuildingPanel::getExistingTechCheck(NTechnology::Technology technology) const
{
    return existingTechFields[technology];
}
