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
#include <QDockWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QWidget>
#include <QSpinBox>
#include <QPen>

#include "requestinterface.h"
#include "buildingview.h"
#include "locationpanel.h"
#include "../model/location/building.h"
#include <vector>

using namespace std;

RequestInterface::RequestInterface() : QMainWindow(){
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

    // create the form panel
    formPanel = new QDockWidget("Form");
    addDockWidget(Qt::BottomDockWidgetArea, formPanel);
    locationPanel = new LocationPanel();

    //open the window in maximized format
    showMaximized();
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
    BuildingView *buildingView = new BuildingView(100,100,150,200,"Building "+oss.str());

    // adding it to the building view array
    buildingViews.push_back(buildingView);

    request.addBuilding(buildingView->getBuilding());

    // update the window (call paint event)
    update();
}

void RequestInterface::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen defaultPen = painter.pen();
    QPen focusPen;
    focusPen.setWidth(5);

    QColor buildingColor(90,167,45);

    // foreach building view, add it on the board
    for(unsigned int i = 0 ; i < buildingViews.size();i++)
    {
        BuildingView *currentbuildingView  = buildingViews[i];
        if(currentbuildingView == focusedView)
            painter.setPen(focusPen);
        else
            painter.setPen(defaultPen);
        painter.drawRect(*currentbuildingView);
        painter.fillRect(*currentbuildingView, buildingColor);
        painter.drawText(*currentbuildingView,Qt::AlignHCenter,currentbuildingView->getName());
        painter.drawText(*currentbuildingView, Qt::AlignBottom+Qt::AlignCenter, currentbuildingView->getUsers());
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
    focusedView = 0;
    for(unsigned int i = 0 ; i < buildingViews.size();i++)
    {
        if(buildingViews[i]->contains(event->pos()))
        {
            formPanel->setWidget(locationPanel);
            focusedView = buildingViews[i];
            locationPanel->getUserNumberField(NUserType::DEFAULT)->setValue(focusedView->getBuilding()->getUserNumber(NUserType::DEFAULT));
            locationPanel->getUserNumberField(NUserType::SUP)->setValue(focusedView->getBuilding()->getUserNumber(NUserType::SUP));
            locationPanel->getUserNumberField(NUserType::ADMIN)->setValue(focusedView->getBuilding()->getUserNumber(NUserType::ADMIN));
            QObject::connect(locationPanel->getUserNumberField(NUserType::DEFAULT),SIGNAL(valueChanged(int)),this,SLOT(setDefaultUsers(int)));
            QObject::connect(locationPanel->getUserNumberField(NUserType::SUP),SIGNAL(valueChanged(int)),this,SLOT(setSupUsers(int)));
            QObject::connect(locationPanel->getUserNumberField(NUserType::ADMIN),SIGNAL(valueChanged(int)),this,SLOT(setAdminUsers(int)));
            break;
        }
    }
    if(focusedView == 0)
    {
        formPanel->setWidget(0);
    }
    update();
}

/**
 * @brief RequestInterface::mouseMoveEvent
 * @param event
 * move the element
 */
void RequestInterface::mouseMoveEvent(QMouseEvent *event)
{
    if(focusedView != 0)
    {
        focusedView->moveTo(event->globalPos());
        update();
    }
}


void RequestInterface::setDefaultUsers(int userNumber)
{
    focusedView->getBuilding()->setUserNumber(NUserType::DEFAULT, userNumber);
    update();
}

void RequestInterface::setSupUsers(int userNumber)
{
    focusedView->getBuilding()->setUserNumber(NUserType::SUP, userNumber);
    update();
}

void RequestInterface::setAdminUsers(int userNumber)
{
    focusedView->getBuilding()->setUserNumber(NUserType::ADMIN, userNumber);
    update();
}
