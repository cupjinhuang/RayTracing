#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setMouseTracking(true);
    QHBoxLayout *layout = new QHBoxLayout;
    scene = new Scene(this);
    view = new QGraphicsView(scene);
    view->show();
    layout->addWidget(view);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    widget->show();

    scene->sceneMain();
    setCentralWidget(widget);
    this->setFixedSize(CWIDTH + 100, CHEIGHT + 100);


}

MainWindow::~MainWindow()
{

}
