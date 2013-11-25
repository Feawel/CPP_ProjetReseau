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
#include <QString>
#include <QMouseEvent>
#include <sstream>
#include <QDockWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QWidget>
#include <QSpinBox>
#include <QLine>
#include <QCheckBox>

#include "requestinterface.h"
#include "buildingview.h"
#include "locationpanel.h"
#include "../model/location/building.h"
#include <vector>

using namespace std;

/**
 * @brief RequestInterface::RequestInterface
 */
RequestInterface::RequestInterface() : QMainWindow(), buildingColor(90,167,45), adminColor(255,124,124){
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
    buildingPanel = new BuildingPanel();

    //open the window in maximized format
    showMaximized();

    // definition of 2 types of pens : default and focus
    selectedPen.setWidth(5);

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
    BuildingView *buildingView = new BuildingView("Building "+oss.str());

    // create a b2b for each other building
    if(!buildingViews.empty())
    {
        for(int i = 0; i<buildingViews.size(); i++)
        {
            Building_BuildingView *b2bView = new Building_BuildingView(buildingViews[i], buildingView);
            b2bViews.push_back(b2bView);
        }
    }

    // adding it to the building view array
    buildingViews.push_back(buildingView);

    request.addBuilding(buildingView->getBuilding());
    // update the window (call paint event)
    update();
}

/**
 * @brief RequestInterface::paintEvent
 */
void RequestInterface::paintEvent(QPaintEvent *)
{
    // painter creation
    QPainter painter(this);

    // foreach building view, add it on the board
    for(unsigned int i = 0 ; i < buildingViews.size();i++)
    {
        BuildingView *currentbuildingView  = buildingViews[i];

        //check if the view is selected
        if(currentbuildingView == selectedBuildingView)
            painter.setPen(selectedPen);
        else
            painter.setPen(defaultPen);

        painter.drawRect(*currentbuildingView);

        //add color
        if(currentbuildingView->getBuilding()->isAdmin())
            painter.fillRect(*currentbuildingView, adminColor);
        else
            painter.fillRect(*currentbuildingView, buildingColor);

        //add name
        painter.drawText(*currentbuildingView,Qt::AlignHCenter,currentbuildingView->getName());
        //add users
        painter.drawText(*currentbuildingView, Qt::AlignBottom+Qt::AlignCenter, currentbuildingView->getUsers());
    }

    // foreach b2b view, add it on the board
    for(unsigned int i = 0; i< b2bViews.size(); i++)
    {
        Building_BuildingView *currentB2bView = b2bViews[i];

        //check if the view is selected
        if(currentB2bView == selectedB2bView)
            painter.setPen(selectedPen);
        else
            painter.setPen(defaultPen);

        // get the line to draw
        painter.drawLine(currentB2bView->getLine());
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
    // reset selected view pointers
    selectedBuildingView = 0;
    selectedB2bView = 0;

    // hide bottom panel
    formPanel->setWidget(0);

    // check if the user select a building
    for(unsigned int i = 0 ; i < buildingViews.size();i++)
    {
        if(buildingViews[i]->contains(event->pos()))
        {
            // set the bottom panel to a building panel
            formPanel->setWidget(buildingPanel);
            selectedBuildingView = buildingViews[i];

            // fill fields and connect field to the building
            buildingPanel->getUserNumberField(NUserType::DEFAULT)->setValue(selectedBuildingView->getBuilding()->getUserNumber(NUserType::DEFAULT));
            buildingPanel->getUserNumberField(NUserType::SUP)->setValue(selectedBuildingView->getBuilding()->getUserNumber(NUserType::SUP));
            buildingPanel->getUserNumberField(NUserType::ADMIN)->setValue(selectedBuildingView->getBuilding()->getUserNumber(NUserType::ADMIN));
            buildingPanel->setIsAdmin(selectedBuildingView->getBuilding()->isAdmin());
            QObject::connect(buildingPanel->getUserNumberField(NUserType::DEFAULT),SIGNAL(valueChanged(int)),this,SLOT(setDefaultUsers(int)));
            QObject::connect(buildingPanel->getUserNumberField(NUserType::SUP),SIGNAL(valueChanged(int)),this,SLOT(setSupUsers(int)));
            QObject::connect(buildingPanel->getUserNumberField(NUserType::ADMIN),SIGNAL(valueChanged(int)),this,SLOT(setAdminUsers(int)));
            QObject::connect(buildingPanel->getIsAdminField(), SIGNAL(clicked(bool)), this, SLOT(setIsAdmin(bool)));
            break;
        }
    }

    // check if the user select a link b2b
    if(selectedBuildingView==0)
    {
        for(unsigned int i= 0; i< b2bViews.size(); i++)
        {
            // get the line
            QLine line = b2bViews[i]->getLine();
            //event coordonates
            int ex=event->x();
            int ey=event->y();

            // split vertical line and other cases
            if(line.p2().x()==line.p1().x())
            {
                if(line.p1().x()-5 <= ex && ex <= line.p1().x()+5 && ((line.p1().y()-5 <= ey && line.p2().y()+5>= ey) || (line.p2().y()-5 <= ey && line.p1().y()+5>= ey)))
                {
                    selectedB2bView = b2bViews[i];
                    break;
                }
            }
            else
            {
                // calculate line equation y = la * x + lb
                float la = float(line.p2().y()-line.p1().y())/float(line.p2().x()-line.p1().x());
                float lb = float(line.p1().y()-la*line.p1().x());
                // calculate y coordonate on the line for x=ex
                float ly = la*ex+lb;

                // check if ly and ey are close
                if(ly-5<=ey && ey<=ly+5)
                {
                    selectedB2bView = b2bViews[i];
                    break;
                }
            }
        }
    }

    // update board draw
    update();
}

/**
 * @brief RequestInterface::mouseMoveEvent
 * @param event
 * move the element
 */
void RequestInterface::mouseMoveEvent(QMouseEvent *event)
{
    // drag and drop move
    if(selectedBuildingView != 0)
    {
        selectedBuildingView->moveTo(event->globalPos());
        update();
    }
}

void RequestInterface::setDefaultUsers(int userNumber)
{
    selectedBuildingView->getBuilding()->setUserNumber(NUserType::DEFAULT, userNumber);
    update();
}

void RequestInterface::setSupUsers(int userNumber)
{
    selectedBuildingView->getBuilding()->setUserNumber(NUserType::SUP, userNumber);
    update();
}

void RequestInterface::setAdminUsers(int userNumber)
{
    selectedBuildingView->getBuilding()->setUserNumber(NUserType::ADMIN, userNumber);
    update();
}

void RequestInterface::setIsAdmin(bool isAdmin)
{
    selectedBuildingView->getBuilding()->setAdmin(isAdmin);
    update();
}
