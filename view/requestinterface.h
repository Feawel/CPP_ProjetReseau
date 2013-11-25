/*
 * requestinterface.h
 *
 *  Created on: 19 nov. 2013
 *      Author: MOULIN
 */

#ifndef REQUESTINTERFACE_H
#define REQUESTINTERFACE_H

#include <QtGui>
#include <QMainWindow>
#include <QGridLayout>
#include <vector>
#include <QMouseEvent>
#include <QDockWidget>
#include <QPen>
#include <QColor>

#include "locationpanel.h"
#include "buildingpanel.h"
#include "buildingview.h"
#include "b2bview.h"
#include "b2bview.h"
#include "../phases/Request.h"
#include "../model/location/building.h"

class RequestInterface: public QMainWindow {
    Q_OBJECT
public:
    RequestInterface();
public slots:
    void addBuilding();
    void setDefaultUsers(int userNumber);
    void setSupUsers(int userNumber);
    void setAdminUsers(int userNumber);
    void setIsAdmin(bool isAdmin);
private:
    void paintEvent(QPaintEvent *);
    std::vector<BuildingView*> buildingViews;
    std::vector<Building_BuildingView*> b2bViews;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    BuildingView *selectedBuildingView;
    Building_BuildingView *selectedB2bView;
    QDockWidget *formPanel;
    Request request;
    BuildingPanel *buildingPanel;
    QPen defaultPen;
    QPen selectedPen;
    QColor buildingColor;
    QColor adminColor;
};

#endif // REQUESTINTERFACE_H
