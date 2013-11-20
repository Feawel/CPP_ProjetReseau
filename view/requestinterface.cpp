/*
 * requestinterface.cpp
 *
 *  Created on: 19 nov. 2013
 *      Author: MOULIN
 */

#include "requestinterface.h"
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

#include "buildingview.h"

using namespace std;

RequestInterface::RequestInterface() : QMainWindow(){
	showFullScreen();
	QWidget *space = new QWidget;
	setCentralWidget(space);

	QMenu *file = menuBar()->addMenu("&File");
    QAction *quit = new QAction("&Quit", this);
	file->addAction(quit);
	quit->setShortcut(QKeySequence("Ctrl+Q"));

    QToolBar *toolBar = addToolBar("&Edition");

    QAction *addBuildingAction = new QAction("Add Building", this);
    QAction *addFloorAction = new QAction("Add Floor", this);
    toolBar->addAction(addBuildingAction);
    toolBar->addAction(addFloorAction);

	QWidget *board = new QWidget;
    setCentralWidget(board);

    QObject::connect(addBuildingAction, SIGNAL(triggered()), this, SLOT(addBuilding()));
    QObject::connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void RequestInterface::addBuilding()
{
    BuildingView buildingView(100,100,150,200);
    buildingViews.push_back(buildingView);
    update();
}

void RequestInterface::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QColor buildingColor(90,167,45);

    for(int i = 0 ; i < buildingViews.size();i++)
    {
        painter.drawRect(buildingViews[i]);
        painter.fillRect(buildingViews[i], buildingColor);
        QString name = "Building "+ QString::number(i+1);
        painter.drawText(buildingViews[i],Qt::AlignHCenter, name);
    }

    painter.end();
}

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

void RequestInterface::mouseMoveEvent(QMouseEvent *event)
{

    focusedView->moveTo(event->globalPos());
    update();
}

void RequestInterface::mouseReleaseEvent(QMouseEvent *event)
{
    focusedView = 0;
}
