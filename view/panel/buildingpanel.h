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
    ~BuildingPanel();
    void setIsAdmin(bool isAdmin);
    QCheckBox* getIsAdminField() const;
    QPushButton* getAddFloorButton() const;
    QPushButton* getRemoveBuildingButton() const;
    void setUsersReadOnly();
    bool isReadOnly() const;
private:
    QCheckBox* isAdminField;
    QPushButton* addFloorButton;
    QPushButton* removeBuildingButton;
    bool readOnly;
};

#endif // BUILDING_H
