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
#include <QPalette>

#include "requestinterface.h"
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

    // create the central board
    QWidget *board = new QWidget;
    setCentralWidget(board);

    // create the form panel
    formPanel = new QDockWidget("Form");
    formPanel->setAutoFillBackground(true);
    QPalette pal = formPanel->palette();
    pal.setColor( QPalette::Background, QColor( 255, 255, 255));
    formPanel->setPalette(pal);

    //create building panel
    addDockWidget(Qt::RightDockWidgetArea, formPanel);
    buildingPanel = new BuildingPanel;

    // create b2b panel
    b2bPanel = new  Building_BuildingPanel;

    // create default panel
    defaultPanel = new DefaultPanel;
    QObject::connect(defaultPanel->getAddBuildingButton(), SIGNAL(clicked()), this, SLOT(addBuilding()));
    formPanel->setWidget(defaultPanel);

    //create floor panel

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
        for(unsigned int i = 0; i<buildingViews.size(); i++)
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
        BuildingView *currentBuildingView  = buildingViews[i];

        //check if the view is selected
        if(currentBuildingView == selectedBuildingView)
            painter.setPen(selectedPen);
        else
            painter.setPen(defaultPen);

        painter.drawRect(*currentBuildingView);

        //add color
        if(currentBuildingView->getBuilding()->isAdmin())
            painter.fillRect(*currentBuildingView, adminColor);
        else
            painter.fillRect(*currentBuildingView, buildingColor);

        // add floors
        for(unsigned int j=0; j< currentBuildingView->getFloorViews().size(); j++)
        {
            painter.setPen(defaultPen);
            QRect rect(currentBuildingView->x()+15, currentBuildingView->y()+ 15 + j * 90, 120,75);
            painter.drawRect(rect);
        }

        //add name
        painter.drawText(*currentBuildingView,Qt::AlignHCenter,currentBuildingView->getName());
        //add users
        painter.drawText(*currentBuildingView, Qt::AlignBottom+Qt::AlignCenter, currentBuildingView->getUsers());
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
    formPanel->setWidget(defaultPanel);

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
            QObjectCleanupHandler::connect(buildingPanel->getAddFloorButton(), SIGNAL(clicked()), this, SLOT(addFloor()));
            break;
        }
    }

    // check if the user select a link b2b
    if(selectedBuildingView==0)
    {
        bool selected = false;
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
                    selected=true;
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
                    selected =true;
                }
            }
            if(selected)
            {
                selectedB2bView = b2bViews[i];
                formPanel->setWidget(b2bPanel);
                break;
            }
        }
    }

    // update draw
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

/**
 * @brief RequestInterface::setIsAdmin
 * @param isAdmin
 * Set selected building to admin
 */
void RequestInterface::setIsAdmin(bool isAdmin)
{
    // only one building can be admin, put all other to non-admin
    for(unsigned int i = 0 ; i< buildingViews.size(); i++)
    {
        buildingViews[i]->getBuilding()->setAdmin(false);
    }

    selectedBuildingView->getBuilding()->setAdmin(isAdmin);
    update();
}

void RequestInterface::addFloor()
{
    selectedBuildingView->addFloor();
    update();
}
