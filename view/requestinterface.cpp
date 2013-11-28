/*
 * requestinterface.cpp
 *
 *  Created on: 19 nov. 2013
 *      Author: MOULIN
 */

#include <QApplication>
#include <QtGui>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QObject>
#include <QPainter>
#include <sstream>
#include <QFormLayout>
#include <QLineEdit>
#include <QWidget>
#include <QSpinBox>
#include <QLine>
#include <QCheckBox>
#include <QPalette>
#include <QMessageBox>

#include "requestinterface.h"
#include "phases/networkbuilder.h"
#include "txt_generation/txtgenerator.h"

using namespace std;

int const SELECT_MARGIN = 5;


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

    // add clean action with shortcut Ctrl + N
    QAction *clean = new QAction("&Clean",this);
    action->addAction(clean);
    clean->setShortcut(QKeySequence("Ctrl+N"));
    QObject::connect(clean, SIGNAL(triggered()), this, SLOT(clean()));

    // create the central board
    QWidget *board = new QWidget;
    setCentralWidget(board);

    // create the form panel (white background)
    formPanel = new QDockWidget("Form");
    formPanel->setAutoFillBackground(true);
    QPalette pal = formPanel->palette();
    pal.setColor( QPalette::Background, QColor( 255, 255, 255));
    formPanel->setPalette(pal);
    addDockWidget(Qt::RightDockWidgetArea, formPanel);

    // create default panel, add create building button and link it to building creation
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
 * @brief RequestInterface::paintEvent
 */
void RequestInterface::paintEvent(QPaintEvent *)
{
    // reset errors messages
    errors.clear();

    // painter creation
    QPainter painter(this);

    // foreach building view
    for(unsigned int i = 0 ; i < buildingViews.size();i++)
    {
        BuildingView *currentBuildingView  = buildingViews[i];

        // take selected pen if view has been selected
        if(currentBuildingView == selectedBuildingView)
            painter.setPen(selectedPen);
        else
            painter.setPen(defaultPen);

        // draw the building
        painter.drawRect(*currentBuildingView);

        // add color
        bool isAdmin = currentBuildingView->getBuilding()->isAdmin();
        if(isAdmin)
            painter.fillRect(*currentBuildingView, buildingAdminColor);
        else
            painter.fillRect(*currentBuildingView, buildingColor);

        // add floors
        for(unsigned int j=0; j< currentBuildingView->getFloorViews().size(); j++)
        {
            FloorView* currentFloorView(currentBuildingView->getFloorViews()[j]);

            // take selected pen if view has been selected
            if(selectedFloor == currentFloorView)
                painter.setPen(selectedPen);
            else
                painter.setPen(defaultPen);

            // get floor coordonates
            QRect rect(currentBuildingView->x()+15, currentBuildingView->y()+ 15 + j * 90, 120,75);
            painter.drawRect(rect);

            // add color
            if(isAdmin)
                painter.fillRect(rect, floorAdminColor);
            else
                painter.fillRect(rect, floorColor);

            // add floor name
            painter.drawText(rect, Qt::AlignHCenter,currentFloorView->getName());

            // if all users are null set warning style and add an error in errors
            if(currentFloorView->getFloor()->isUsersNull())
            {
                painter.setFont(warningTextFont);
                painter.setPen(warningTextPen);
                errors.push_back(currentFloorView->getName().toStdString()+" in "+currentBuildingView->getName().toStdString()+ " doesn't have any user.");
            }

            // add floor users
            painter.drawText(rect, Qt::AlignBottom+Qt::AlignCenter, currentFloorView->getUsers());

            // reset pen and font
            painter.setFont(defaultFont);
            painter.setPen(defaultPen);
        }

        //add name
        painter.drawText(*currentBuildingView,Qt::AlignHCenter,currentBuildingView->getName());

        // if all users are null set warning style and add an error in errors
        if(currentBuildingView->getBuilding()->isUsersNull() && !currentBuildingView->getBuildingPanel()->isReadOnly())
        {
            painter.setFont(warningTextFont);
            painter.setPen(warningTextPen);
            errors.push_back(currentBuildingView->getName().toStdString()+" doesn't have any user.");
        }

        // add building users
        painter.drawText(*currentBuildingView, Qt::AlignBottom+Qt::AlignCenter, currentBuildingView->getUsers());

        // reset pen and font
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

            // if distance == 0 set warning style and add an error
            double distance = currentB2bView->getB2b()->getDistance();
            if(distance == 0)
            {
                painter.setFont(warningTextFont);
                painter.setPen(warningTextPen);
                errors.push_back("Distance between "+ currentB2bView->getBuilding1()->getName().toStdString() +" and "+currentB2bView->getBuilding2()->getName().toStdString()+" can't be null.");
            }

            // draw distance
            painter.drawText(mid, currentB2bView->getDistance());

            // reset pen and style
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

    // reset panel to default
    formPanel->setWidget(defaultPanel);

    // check if the user select a building or a floor
    for(unsigned int i = 0 ; i < buildingViews.size();i++)
    {
        BuildingView *currentBuildingView = buildingViews[i];
        //check first floors
        for(unsigned int j =0; j < currentBuildingView->getFloorViews().size(); j++)
        {
            QRect rect(currentBuildingView->x()+15, currentBuildingView->y()+ 15 + j * 90, 120,75);
            if(rect.contains(event->pos()))
            {
                // select the floor and add the panel
                selectedFloor = currentBuildingView->getFloorViews()[j];
                formPanel->setWidget(selectedFloor->getFloorPanel());
                break;
            }
        }

        // if no floor has been selected
        if(selectedFloor==0 && buildingViews[i]->contains(event->pos()))
        {
            // select the building and add the panel
            selectedBuildingView = buildingViews[i];
            formPanel->setWidget(selectedBuildingView->getBuildingPanel());
            break;
        }
    }

    // check if the user select a link b2b if no location has been selected
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
            // ex = line.p1().x() = line.p2().x() with SELECT_MARGIN of error
            // line.p1().y() < ey < line.p2().y() or line.p2().y() < ey < line.p1().y() with SELECT_MARGIN of error
            if(line.p2().x()==line.p1().x())
            {
                if(line.p1().x()-SELECT_MARGIN <= ex && ex <= line.p1().x()+SELECT_MARGIN && ((line.p1().y()-SELECT_MARGIN <= ey && line.p2().y()+SELECT_MARGIN>= ey) || (line.p2().y()-SELECT_MARGIN <= ey && line.p1().y()+SELECT_MARGIN>= ey)))
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
                if(ly-SELECT_MARGIN<=ey && ey<=ly+SELECT_MARGIN)
                {
                    selected =true;
                }
            }
            if(selected)
            {
                // select the b2b and add the panel
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
 * move the element only for buildings
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

/**
 * @brief RequestInterface::addBuilding
 * create a building view on the board and create the building attached, adding b2bView and b2b attached
 */
void RequestInterface::addBuilding()
{

    // create the new bulding view and building panel with name Building i
    std::ostringstream oss;
    oss << (buildingViews.size()+1);
    BuildingView *buildingView = new BuildingView("Building "+oss.str());
    BuildingPanel *buildingPanel = new BuildingPanel("Building "+oss.str());
    buildingView->setBuildingPanel(buildingPanel);

    // connect all panel actions to building view
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
            //create the b2bView and the associate panel
            Building_BuildingView *b2bView = new Building_BuildingView(buildingViews[i], buildingView);
            Building_BuildingPanel *b2bPanel = new Building_BuildingPanel;
            b2bView->setB2bPanel(b2bPanel);
            b2bViews.push_back(b2bView);
            request.addBuilding_Building(b2bView->getB2b());

            //connect b2bPanel action to b2bView
            QObject::connect(b2bPanel->getDistanceField(), SIGNAL(valueChanged(double)), this, SLOT(setDistance(double)));
        }
    }

    // adding it to the building view array and to the request
    buildingViews.push_back(buildingView);
    request.addBuilding(buildingView->getBuilding());

    // update the window (call paint event)
    update();
}

/**
 * @brief RequestInterface::setDefaultUsers
 * @param userNumber
 * set default user number for the selected location view
 */
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

/**
 * @brief RequestInterface::setDefaultUsers
 * @param userNumber
 * set sup user number for the selected location view
 */
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

/**
 * @brief RequestInterface::setDefaultUsers
 * @param userNumber
 * set admin user number for the selected location view
 */
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
    // search previous admin building
    for(unsigned int i = 0 ; i< buildingViews.size(); i++)
    {
        BuildingView *currentbuildingView = buildingViews[i];
        if(currentbuildingView!=selectedBuildingView && currentbuildingView->getBuilding()->isAdmin())
        {
            // set to non-admin
            currentbuildingView->getBuilding()->setAdmin(false);
            currentbuildingView->getBuildingPanel()->getIsAdminField()->setChecked(false);
            for(unsigned int j = 0; j< currentbuildingView->getFloorViews().size(); j++)
            {
                // set all floor admin number to 0 and field admin number to readonly
                FloorView *currentFloorView = currentbuildingView->getFloorViews()[j];
                currentFloorView->getFloor()->setUserNumber(NUserType::ADMIN,0);
                currentFloorView->getFloorPanel()->getUserNumberField(NUserType::ADMIN)->setEnabled(false);
                currentFloorView->getFloorPanel()->getUserNumberField(NUserType::ADMIN)->setValue(0);
            }

            //set building admin number to 0 and admin number field to read only
            currentbuildingView->getBuilding()->setUserNumber(NUserType::ADMIN,0);
            currentbuildingView->getBuildingPanel()->getUserNumberField(NUserType::ADMIN)->setEnabled(false);
            currentbuildingView->getBuildingPanel()->getUserNumberField(NUserType::ADMIN)->setValue(0);

            // stop search, only one building can be admin
            break;
        }
    }

    //set buiding to admin
    selectedBuildingView->getBuilding()->setAdmin(isAdmin);
    unsigned int size =selectedBuildingView->getFloorViews().size();

    // set building admin user number field to editable only if ther is no floors
    if(size == 0)
        selectedBuildingView->getBuildingPanel()->getUserNumberField(NUserType::ADMIN)->setEnabled(true);

    for(unsigned int i = 0; i< size; i++)
    {
        // set all floor field admin number to editable
        selectedBuildingView->getFloorViews()[i]->getFloorPanel()->getUserNumberField(NUserType::ADMIN)->setEnabled(true);
    }

    update();
}

/**
 * @brief RequestInterface::addFloor
 * add a floor to the selected building
 */
void RequestInterface::addFloor()
{
    // create the view and the associate panel
    FloorView *floorView = selectedBuildingView->addFloor();
    LocationPanel *floorPanel = new LocationPanel;
    floorView->setFloorPanel(floorPanel);

    if(selectedBuildingView->getBuilding()->isAdmin())
    {
        floorPanel->getUserNumberField(NUserType::ADMIN)->setEnabled(true);
    }

    QObject::connect(floorPanel->getUserNumberField(NUserType::DEFAULT),SIGNAL(valueChanged(int)),this,SLOT(setDefaultUsers(int)));
    QObject::connect(floorPanel->getUserNumberField(NUserType::SUP),SIGNAL(valueChanged(int)),this,SLOT(setSupUsers(int)));
    QObject::connect(floorPanel->getUserNumberField(NUserType::ADMIN),SIGNAL(valueChanged(int)),this,SLOT(setAdminUsers(int)));

    update();
}

/**
 * @brief RequestInterface::setDistance
 * @param distance
 * set the distance to the selected b2b
 */
void RequestInterface::setDistance(double distance)
{
    selectedB2bView->getB2b()->setDistance(distance);
    update();
}

/**
 * @brief RequestInterface::displayErrors
 * @return string
 * construct a string with all error messages
 */
string RequestInterface::displayErrors() const
{
    string message;
    for(unsigned int i = 0; i< errors.size(); i++)
    {
        message+=errors[i];
        message+="\n";
    }
    return message;
}

/**
 * @brief RequestInterface::run
 * run the builder
 */
void RequestInterface::run()
{
    // check if there is errors
    if(errors.empty())
    {
        Request *ptr(0);
        ptr=&request;
        NetworkBuilder builder(ptr);
        TxtGenerator txtGenerator(ptr);
        txtGenerator.generateDoc();
    }
    else
    {
        QMessageBox::critical(this, QString::fromStdString("More information needed"), QString::fromStdString(displayErrors()));
    }
}

/**
 * @brief RequestInterface::removeBuilding
 * remove the selected building
 */
void RequestInterface::removeBuilding()
{
    // remove all b2b adajacents to the building
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

    // search the building in the request and in the buildingviews array
    for(unsigned int i = 0; i< buildingViews.size(); i++)
    {
        if(buildingViews[i] == selectedBuildingView)
        {
            request.removeBuilding(i);
            buildingViews.erase(buildingViews.begin()+i);
        }
    }

    // delete building
    delete selectedBuildingView;

    // reset panel
    formPanel->setWidget(defaultPanel);
    update();
}

/**
 * @brief RequestInterface::setName
 * @param name
 * et the selected building name
 */
void RequestInterface::setName(QString name)
{
    selectedBuildingView->getBuilding()->setName(name.toStdString());
    update();
}

/**
 * @brief RequestInterface::clean
 * delete all buildings
 */
void RequestInterface::clean()
{
    // remove all b2b
    for(unsigned int i = 0; i <b2bViews.size(); i++)
    {
        delete b2bViews[i];
    }

    // remove all buildings
    for(unsigned int i = 0; i< buildingViews.size(); i++)
    {
        delete buildingViews[i];
    }

    // reset views array
    buildingViews.clear();;
    b2bViews.clear();

    // deselect all
    selectedB2bView=0;
    selectedBuildingView=0;
    selectedFloor=0;

    //reset panel
    formPanel->setWidget(defaultPanel);
    update();
}
