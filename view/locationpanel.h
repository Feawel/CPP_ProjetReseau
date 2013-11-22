/*
 * locationpanel.h
 *
 *  Created on: 20 nov. 2013
 *      Author: MOULIN
 */

#ifndef LOCATIONPANEL_H_
#define LOCATIONPANEL_H_

#include <QWidget>
#include <QSpinBox>
#include <vector>
#include "../model/constant.h"

class LocationPanel: public QWidget {
public:
    LocationPanel();
    QSpinBox* getUserNumberField(NUserType::UserType userType);
private:
    std::vector<QSpinBox*> userNumberFields;
};

#endif /* LOCATIONPANEL_H_ */
