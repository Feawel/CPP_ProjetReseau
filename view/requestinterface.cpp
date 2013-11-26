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
#include "phases/networkbuilder.h"
#include <vector>

using namespace std;

/**
 * @brief RequestInterface::RequestInterface
 */
RequestInterface::RequestInterface() :
    QMainWindow(), buildingColor(90,167,45), buildingAdminColor(255,124,124), floorColor(110,196,45),floorAdminColor(255,155,124)
{
    // create the file menu
    QMenu *file = menuBar()->addMenu("&File");

    // add quit action with shortcut Ctrl + Q
    QAction *quit = new QAction("&Quit", this);
    file->addAction(quit);
    quit->setShortcut(QKeySequence("Ctrl+Q"));
    QObject::connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    // create the action menu
    QMenu *action = menuBar()->addMenu("&Action");

    // add run action with shortcut Ctrl + R
    QAction *run = new QAction("&Run", this);
    action->addAction(run);
    run->setShortcut(QKeySequence("Ctrl+R"));
    QObject::connect(run, SIGNAL(triggered()), this, SLOT(run()));

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

    // create default panel
    defaultPanel = new DefaultPanel;
    QObject::connect(defaultPanel->getAddBuildingButton(), SIGNAL(clicked()), this, SLOT(addBuilding()));
    formPanel->setWidget(defaultPanel);

    //open the window in maximized format
    showMaximized();

    // definition of pens : default, focus, warning text
    selectedPen.setWidth(3);
    warningTextPen.setColor(QColor(255,0,0));
    warningTextFont.setBold(true);
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
    BuildingPanel *buildingPanel = new BuildingPanel("Building "+oss.str());
    buildingView->setBuildingPanel(buildingPanel);
    QObject::connect(buildingPanel->getUserNumberField(NUserType::DEFAULT),SIGNAL(valueChanged(int)),this,SLOT(setDefaultUsers(int)));
    QObject::connect(buildingPanel->getUserNumberField(NUserType::SUP),SIGNAL(valueChanged(int)),this,SLOT(setSupUsers(int)));
    QObject::connect(buildingPanel->getUserNumberField(NUserType::ADMIN),SIGNAL(valueChanged(int)),this,SLOT(setAdminUsers(int)));
    QObject::connect(buildingPanel->getIsAdminField(), SIGNAL(clicked(bool)), this, SLOT(setIsAdmin(bool)));
    QObject::connect(buildingPanel->getAddFloorButton(), SIGNAL(clicked()), this, SLOT(addFloor()));
    QObject::connect(buildingPanel->getRemoveBuildingButton(), SIGNAL(clicked()), this, SLOT(removeBuilding()));
    QObject::connect(buildingPanel->getNameField(), SIGNAL(textChanged(QString)), this, SLOT(setName(QString)));

    // create a b2b for each other building
    if(!buildingViews.empty())
    {
        for(unsigned int i = 0; i<buildingViews.size(); i++)
        {
            Building_BuildingView *b2bView = new Building_BuildingView(buildingViews[i], buildingView);
            Building_BuildingPanel *b2bPanel = new Building_BuildingPanel;
            b2bView->setB2bPanel(b2bPanel);
            QObject::connect(b2bPanel->getDistanceField(), SIGNAL(valueChanged(double)), this, SLOT(setDistance(double)));
            b2bViews.push_back(b2bView);
            request.addBuilding_Building(b2bView->getB2b());
        }
    }

    // adding it to the building view array
    buildingViews.push_back(buildingView);

    // ading building to the request
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
        bool isAdmin = currentBuildingView->getBuilding()->isAdmin();
        if(isAdmin)
            painter.fillRect(*currentBuildingView, buildingAdminColor);
        else
            painter.fillRect(*currentBuildingView, buildingColor);

        // add floors
        for(unsigned int j=0; j< currentBuildingView->getFloorViews().size(); j++)
        {
            FloorView* currentFloorView(currentBuildingView->getFloorViews()[j]);
            if(selectedFloor == currentFloorView)
                painter.setPen(selectedPen);
            else
                painter.setPen(defaultPen);
            QRect rect(currentBuildingView->x()+15, currentBuildingView->y()+ 15 + j * 90, 120,75);
            painter.drawRect(rect);
            if(isAdmin)
                painter.fillRect(rect, floorAdminColor);
            else
                painter.fillRect(rect, floorColor);
            painter.drawText(rect, Qt::AlignHCenter,currentFloorView->getName());

            if(currentFloorView->getFloor()->isUsersNull())
            {
                painter.setFont(warningTextFont);
                painter.setPen(warningTextPen);
            }
            painter.drawText(rect, Qt::AlignBottom+Qt::AlignCenter, currentFloorView->getUsers());
            painter.setFont(defaultFont);
            painter.setPen(defaultPen);
        }

        //add name
        painter.drawText(*currentBuildingView,Qt::AlignHCenter,currentBuildingView->getName());
        //add users
        if(currentBuildingView->getBuilding()->isUsersNull() && !currentBuildingView->getBuildingPanel()->isReadOnly())
        {
            painter.setFont(warningTextFont);
            painter.setPen(warningTextPen);
        }
        painter.drawText(*currentBuildingView, Qt::AlignBottom+Qt::AlignCenter, currentBuildingView->getUsers());
        painter.setFont(defaultFont);
        painter.setPen(defaultPen);
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
        // if there is an intersection between 2 building don't draw
        if(!currentB2bView->intersect())
        {
            // draw the line
            QLine line = currentB2bView->getLine();
            painter.drawLine(line);

            // find the middle of the line and right the distance
            // get the x average and the y average, offset 4 on y to place text above line
            QPoint mid((line.p2().x()+line.p1().x())/2, (line.p2().y()+line.p1().y())/2-4);

            // if distance == 0 set warning
            double distance = currentB2bView->getB2b()->getDistance();
            if(distance == 0)
            {
                painter.setFont(warningTextFont);
                painter.setPen(warningTextPen);
            }
            painter.drawText(mid, currentB2bView->getDistance());
            painter.setPen(defaultPen);
            painter.setFont(defaultFont);
        }
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
    selectedFloor = 0;

    // hide bottom panel
    formPanel->setWidget(defaultPanel);

    // check if the user select a building
    for(unsigned int i = 0 ; i < buildingViews.size();i++)
    {
        BuildingView *currentBuildingView = buildingViews[i];
        for(unsigned int j =0; j < currentBuildingView->getFloorViews().size(); j++)
        {
            QRect rect(currentBuildingView->x()+15, currentBuildingView->y()+ 15 + j * 90, 120,75);
            if(rect.contains(event->pos()))
            {
                selectedFloor = currentBuildingView->getFloorViews()[j];
                formPanel->setWidget(selectedFloor->getFloorPanel());
                break;
            }
        }

        if(selectedFloor==0 && buildingViews[i]->contains(event->pos()))
        {
            selectedBuildingView = buildingViews[i];
            // set the bottom panel to a building panel
            formPanel->setWidget(selectedBuildingView->getBuildingPanel());
            break;
        }
    }

    // check if the user select a link b2b
    if(selectedBuildingView==0 && selectedFloor == 0)
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
                formPanel->setWidget(selectedB2bView->getB2bPanel());
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
    Location *location;
    if(selectedBuildingView != 0)
    {
        location = selectedBuildingView->getBuilding();
    }
    else
    {
        location = selectedFloor->getFloor();
    }
    location->setUserNumber(NUserType::DEFAULT, userNumber);
    update();
}

void RequestInterface::setSupUsers(int userNumber)
{
    Location *location;
    if(selectedBuildingView != 0)
    {
        location = selectedBuildingView->getBuilding();
    }
    else
    {
        location = selectedFloor->getFloor();
    }
    location->setUserNumber(NUserType::SUP, userNumber);
    update();
}

void RequestInterface::setAdminUsers(int userNumber)
{
    Location *location;
    if(selectedBuildingView != 0)
    {
        location = selectedBuildingView->getBuilding();
    }
    else
    {
        location = selectedFloor->getFloor();
    }
    location->setUserNumber(NUserType::ADMIN, userNumber);
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
    FloorView *floorView = selectedBuildingView->addFloor();
    LocationPanel *floorPanel = new LocationPanel;
    floorView->setFloorPanel(floorPanel);

    QObject::connect(floorPanel->getUserNumberField(NUserType::DEFAULT),SIGNAL(valueChanged(int)),this,SLOT(setDefaultUsers(int)));
    QObject::connect(floorPanel->getUserNumberField(NUserType::SUP),SIGNAL(valueChanged(int)),this,SLOT(setSupUsers(int)));
    QObject::connect(floorPanel->getUserNumberField(NUserType::ADMIN),SIGNAL(valueChanged(int)),this,SLOT(setAdminUsers(int)));

    update();
}

void RequestInterface::setDistance(double distance)
{
    selectedB2bView->getB2b()->setDistance(distance);
    update();
}

void RequestInterface::run()
{
    Request *ptr(0);
    ptr=&request;
    NetworkBuilder builder(ptr);
}

void RequestInterface::removeBuilding()
{
    for(unsigned int i = 0; i <b2bViews.size(); i++)
    {
        if(b2bViews[i]->getBuilding1() == selectedBuildingView)
        {
            delete b2bViews[i];
            b2bViews.erase(b2bViews.begin()+i);
            request.removeBuilding_Building(i);
        }
        else if(b2bViews[i]->getBuilding2() == selectedBuildingView)
        {
            delete b2bViews[i];
            b2bViews.erase(b2bViews.begin()+i);
            request.removeBuilding_Building(i);
        }
    }

    for(unsigned int i = 0; i< buildingViews.size(); i++)
    {
        if(buildingViews[i] == selectedBuildingView)
        {
            request.removeBuilding(i);
            buildingViews.erase(buildingViews.begin()+i);
        }
    }
    delete selectedBuildingView;
    formPanel->setWidget(defaultPanel);
    update();
}

void RequestInterface::setName(QString name)
{
    selectedBuildingView->getBuilding()->setName(name.toStdString());
    update();
}
