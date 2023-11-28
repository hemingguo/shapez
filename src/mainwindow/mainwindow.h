//
// Created by hemingguo on 2023-11-20.
//

#ifndef SHAPEZ_MAINWINDOW_H
#define SHAPEZ_MAINWINDOW_H

#include <QLabel>
#include <QWidget>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;


private:
    Ui::MainWindow *ui;
    int windowWidth;
    int windowHeight;
    QVBoxLayout *layout;
    QMovie *movie;
    QLabel *label;
    void playVideo(const QString &filePath);
    void stopVideo();
    void clearLayout(QLayout *layout);

signals:
    void videoStopped();

public slots:

    void onVideoStopped();


};


#endif //SHAPEZ_MAINWINDOW_H
