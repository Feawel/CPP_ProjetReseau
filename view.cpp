#include <QApplication>
#include <QtGui>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    QWidget *space = new QWidget;
    window.setCentralWidget(space);

    QMenu *file = window.menuBar()->addMenu("&File");
    QAction *quit = new QAction("&Quit",file);
    file->addAction(quit);

    QObject::connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    window.show();
    return app.exec();
}
