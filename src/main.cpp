#include <QApplication>
#include <QMediaPlaylist>
#include <QDir>
#include "mainwindow/mainwindow.h"
#include "first/first.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
