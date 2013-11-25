/*
 * buildingpanel.cpp
 *
 *  Created on: 2( nov. 2013
 *      Author: MOULIN
 */

#include "buildingpanel.h"

BuildingPanel::BuildingPanel():LocationPanel()
{
    isAdminField = new QCheckBox();
    layout->addRow("Admin building ?",isAdminField);

    addFloorButton = new QPushButton("Add Floor");
    layout->addRow(addFloorButton);
}

void BuildingPanel::setIsAdmin(bool isAdmin)
{
    if(isAdmin)
        isAdminField->setCheckState(Qt::Checked);
    else
        isAdminField->setCheckState(Qt::Unchecked);
}

QCheckBox* BuildingPanel::getIsAdminField()
{
    return isAdminField;
}
