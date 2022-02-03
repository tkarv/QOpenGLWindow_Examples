#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoSink>

#include "customglwidget.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<QMediaPlayer> mediaPlayer;
    std::unique_ptr<QVideoSink> videoSink;

private slots:
    void RXVideoFrame(const QVideoFrame &);
};

#endif // MAINWINDOW_H
