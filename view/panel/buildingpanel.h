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
#include <QLineEdit>
#include "locationpanel.h"

class BuildingPanel : public LocationPanel
{
public:
    BuildingPanel(std::string name);
    ~BuildingPanel();
    void setIsAdmin(bool isAdmin);
    QCheckBox* getIsAdminField() const;
    QPushButton* getAddFloorButton() const;
    QPushButton* getRemoveBuildingButton() const;
    void disableFields();
    bool isReadOnly() const;
    QLineEdit* getNameField() const;
private:
    QCheckBox* isAdminField;
    QPushButton* addFloorButton;
    QPushButton* removeBuildingButton;
    QLineEdit *nameField;
    bool readOnly;
};

#endif // BUILDING_H
