/*
 * buildingpanel.cpp
 *
 *  Created on: 25 nov. 2013
 *      Author: MOULIN
 */

#include "buildingpanel.h"

BuildingPanel::BuildingPanel():LocationPanel()
{
    isAdminField = new QCheckBox();
    layout->addRow("Admin building ?",isAdminField);

    addFloorButton = new QPushButton("Add Floor");
    layout->addRow(addFloorButton);

    removeBuildingButton = new QPushButton("Remove Building");
    layout->addRow(removeBuildingButton);

    readOnly =false;
}

BuildingPanel::~BuildingPanel()
{
    delete isAdminField;
    delete addFloorButton;
    delete removeBuildingButton;
}

void BuildingPanel::setIsAdmin(bool isAdmin)
{
    if(isAdmin)
        isAdminField->setCheckState(Qt::Checked);
    else
        isAdminField->setCheckState(Qt::Unchecked);
}

QCheckBox* BuildingPanel::getIsAdminField() const
{
    return isAdminField;
}

QPushButton* BuildingPanel::getAddFloorButton() const
{
    return addFloorButton;
}

void BuildingPanel::setUsersReadOnly()
{
    readOnly = true;
    for(unsigned int i = 0; i< userNumberFields.size(); i++)
    {
        userNumberFields[i]->setValue(0);
        userNumberFields[i]->setEnabled(false);
    }
}

bool BuildingPanel::isReadOnly() const
{
    return readOnly;
}

QPushButton* BuildingPanel::getRemoveBuildingButton() const
{
    return removeBuildingButton;
}
