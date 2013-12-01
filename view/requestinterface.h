/*
 * requestinterface.h
 *
 *  Created on: 19 nov. 2013
 *      Author: MOULIN
 */

#ifndef REQUESTINTERFACE_H
#define REQUESTINTERFACE_H

#include <QtGui>
#include <QString>
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
#include "model/request.h"
#include "../model/location/building.h"

class RequestInterface: public QMainWindow {
    Q_OBJECT
public:
    RequestInterface();
    std::string displayErrors() const;
public slots:
    void addBuilding();
    void setDefaultUsers(int userNumber);
    void setSupUsers(int userNumber);
    void setAdminUsers(int userNumber);
    void setIsAdmin(bool isAdmin);
    void addFloor();
    void run();
    void setDistance(double distance);
    void removeBuilding();
    void setName(QString name);
    void clean();
    void setExistingFiber(bool exist);
    void setExistingTwisted(bool exist);
    void setExistingWifi(bool exist);
    void setExistingInfra(bool exist);
    void setUseWifi(bool use);
    void setUseEthenet(bool use);
private:
    Request request;
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    std::vector<std::string> errors;

    std::vector<BuildingView*> buildingViews;
    std::vector<Building_BuildingView*> b2bViews;
    BuildingView *selectedBuildingView;
    Building_BuildingView *selectedB2bView;
    FloorView *selectedFloor;
    QDockWidget *formPanel;
    DefaultPanel* defaultPanel;

    QPen defaultPen;
    QPen selectedPen;
    QPen warningTextPen;
    QColor buildingColor;
    QColor buildingAdminColor;
    QColor floorColor;
    QColor floorAdminColor;
    QFont warningTextFont;
    QFont defaultFont;
};

#endif // REQUESTINTERFACE_H
