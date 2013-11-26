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
#include <QFormLayout>
#include <vector>
#include <QGroupBox>
#include <QCheckBox>
#include "../../model/constant.h"

class LocationPanel: public QWidget {
public:
    LocationPanel();
    ~LocationPanel();
    QSpinBox* getUserNumberField(NUserType::UserType userType);
protected:
    QFormLayout* layout;
    std::vector<QSpinBox*> userNumberFields;


};

#endif /* LOCATIONPANEL_H_ */
