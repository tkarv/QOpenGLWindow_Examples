#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // load image
    QImage image(QString(":/images/bird.jpg"));

    // show image
    ui->openGLWidget->setTexture(image);
}

MainWindow::~MainWindow()
{
    delete ui;
}
