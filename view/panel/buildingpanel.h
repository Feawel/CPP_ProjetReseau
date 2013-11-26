/*
 * buildingpanel.h
 *
 *  Created on: 25 nov. 2013
 *      Author: MOULIN
 */

#ifndef BUILDING_H
#define BUILDING_H

#include <QCheckBox>
#include <QPushButton>
#include "locationpanel.h"

class BuildingPanel : public LocationPanel
{
public:
    BuildingPanel();
    void setIsAdmin(bool isAdmin);
    QCheckBox* getIsAdminField();
    QPushButton* getAddFloorButton();
    void setUsersReadOnly();
    bool isReadOnly();
private:
    QCheckBox* isAdminField;
    QPushButton* addFloorButton;
    bool readOnly;
};

#endif // BUILDING_H
