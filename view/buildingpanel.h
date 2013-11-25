/*
 * buildingpanel.h
 *
 *  Created on: 20 nov. 2013
 *      Author: MOULIN
 */

#ifndef BUILDING_H
#define BUILDING_H

#endif // BUILDING_H

#include <QCheckBox>
#include "locationpanel.h"

class BuildingPanel : public LocationPanel
{
public:
    BuildingPanel();
    void setIsAdmin(bool isAdmin);
    QCheckBox* getIsAdminField();
private:
    QCheckBox* isAdminField;
};
