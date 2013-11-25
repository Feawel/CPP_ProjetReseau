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

#include "panel/locationpanel.h"
#include "panel/buildingpanel.h"
#include "panel/defaultpanel.h"
#include "panel/b2bpanel.h"
#include "views/buildingview.h"
#include "views/b2bview.h"
#include "views/floorview.h"
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
    void addFloor();
private:
    Request request;
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    std::vector<BuildingView*> buildingViews;
    std::vector<Building_BuildingView*> b2bViews;
    BuildingView *selectedBuildingView;
    Building_BuildingView *selectedB2bView;
    QDockWidget *formPanel;
    DefaultPanel* defaultPanel;
    //BuildingPanel *buildingPanel;
    //Building_BuildingPanel *b2bPanel;

    QPen defaultPen;
    QPen selectedPen;
    QColor buildingColor;
    QColor adminColor;
};

#endif // REQUESTINTERFACE_H
