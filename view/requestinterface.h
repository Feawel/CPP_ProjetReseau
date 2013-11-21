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

#include "buildingview.h"

class RequestInterface: public QMainWindow {
    Q_OBJECT
public:
    RequestInterface();public slots:
    void addBuilding();
private:
    void paintEvent(QPaintEvent *);
    std::vector<BuildingView> buildingViews;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    BuildingView *focusedView;
    QDockWidget *formPanel;
};

#endif // REQUESTINTERFACE_H
