#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // load video
    mediaPlayer = std::make_unique<QMediaPlayer>(new QMediaPlayer);
    videoSink = std::make_unique<QVideoSink>(new QVideoSink);
    QUrl resourceUrl = QUrl("qrc:/videos/sample-5s.mp4");
    mediaPlayer->setSource(resourceUrl);
    mediaPlayer->setVideoSink(videoSink.get());
    connect(videoSink.get(), SIGNAL(videoFrameChanged(QVideoFrame)), this, SLOT(RXVideoFrame(QVideoFrame)));
    mediaPlayer->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RXVideoFrame(const QVideoFrame &frame) {
    if(frame.isValid()) {
        ui->openGLWidget->setTexture(frame);
    }
}
