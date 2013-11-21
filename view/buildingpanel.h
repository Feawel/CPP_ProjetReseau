/*
 * buildingpanel.h
 *
 *  Created on: 20 nov. 2013
 *      Author: MOULIN
 */

#ifndef BUILDINGPANEL_H_
#define BUILDINGPANEL_H_

#include <QWidget>
#include <QSpinBox>
#include <vector>
#include "../model/constant.h"

class BuildingPanel: public QWidget {
public:
    BuildingPanel();
    QSpinBox* getUserNumberField(NUserType::UserType userType);
private:
    std::vector<QSpinBox*> userNumberFields;
};

#endif /* BUILDINGPANEL_H_ */
