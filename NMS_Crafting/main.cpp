#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/Atlas.png");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();

    QTime dieTime= QTime::currentTime().addSecs(3);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    MainWindow w;
    w.show();
    splash.finish(&w);

    return a.exec();
}
