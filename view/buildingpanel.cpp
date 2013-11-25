/*
 * buildingpanel.cpp
 *
 *  Created on: 20 nov. 2013
 *      Author: MOULIN
 */

#include "buildingpanel.h"

BuildingPanel::BuildingPanel():LocationPanel()
{
    isAdminField = new QCheckBox();
    layout->addRow("Admin building ?",isAdminField);
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
