/*
 * requestinterface.cpp
 *
 *  Created on: 19 nov. 2013
 *      Author: MOULIN
 */

#include <QApplication>
#include <QtGui>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QObject>
#include <QToolBar>
#include <QPainter>
#include <QPolygon>
#include <QColor>
#include <QString>
#include <QMouseEvent>
#include <sstream>

#include "requestinterface.h"
#include "buildingview.h"
#include "../model/location/building.h"

using namespace std;

RequestInterface::RequestInterface() : QMainWindow(){

    //open the wwindow in maximized format
    showMaximized();

    // create the file menu
    QMenu *file = menuBar()->addMenu("&File");

    // add qui action with shortcut Ctrl + Q
    QAction *quit = new QAction("&Quit", this);
    file->addAction(quit);
    quit->setShortcut(QKeySequence("Ctrl+Q"));
    QObject::connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    // create the toolbar
    QToolBar *toolBar = addToolBar("&Edition");

    // add the create building action
    QAction *addBuildingAction = new QAction("Add Building", this);
    toolBar->addAction(addBuildingAction);
    QObject::connect(addBuildingAction, SIGNAL(triggered()), this, SLOT(addBuilding()));

    // add the create floor action
    QAction *addFloorAction = new QAction("Add Floor", this);
    toolBar->addAction(addFloorAction);

    // create the central board
    QWidget *board = new QWidget;
    setCentralWidget(board);
}

/**
 * @brief RequestInterface::addBuilding
 * create a building view on the board and create the building attached
 */
void RequestInterface::addBuilding()
{
    std::ostringstream oss;
    oss << (buildingViews.size()+1);

    // create the new bulding view with name Building i
    BuildingView buildingView(100,100,150,200,"Building "+oss.str());

    // adding it to the building view array
    buildingViews.push_back(buildingView);

    // update the window (call paint event)
    update();
}

void RequestInterface::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QColor buildingColor(90,167,45);

    // foreach building view, add it on the board
    for(int i = 0 ; i < buildingViews.size();i++)
    {
        BuildingView *currentbuildingView  = &buildingViews[i];
        painter.drawRect(*currentbuildingView);
        painter.fillRect(*currentbuildingView, buildingColor);
        painter.drawText(*currentbuildingView,Qt::AlignHCenter,currentbuildingView->getName());
    }

    painter.end();
}

/**
 * @brief RequestInterface::mousePressEvent
 * @param event
 * find the current focus
 */
void RequestInterface::mousePressEvent(QMouseEvent *event)
{
    for(int i = 0 ; i < buildingViews.size();i++)
    {
        if(buildingViews[i].contains(event->pos()))
        {
            focusedView = &buildingViews[i];
        }
    }
}

/**
 * @brief RequestInterface::mouseMoveEvent
 * @param event
 * move the element
 */
void RequestInterface::mouseMoveEvent(QMouseEvent *event)
{
    focusedView->moveTo(event->globalPos());
    update();
}

/**
 * @brief RequestInterface::mouseReleaseEvent
 * @param event
 * unfocus the element
 */
void RequestInterface::mouseReleaseEvent(QMouseEvent *event)
{
    focusedView = 0;
}
