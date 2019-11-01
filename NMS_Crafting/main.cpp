#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTime>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("NMS Crafting Tool");
    QApplication::setApplicationVersion("0.1.5.1a");
    QCommandLineParser parser;
    bool test;

    parser.setApplicationDescription(QApplication::translate("main", "Outil pour les recettes de No Man's Sky"));
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption optionTest(QStringList() << "t" << "test", QApplication::translate("main", "Utilisation base de test."), QApplication::translate("main", "true|false"), "false");
    parser.addOption(optionTest);

    parser.process(app);

    if (parser.value(optionTest) == "true"){
        test = true;
    } else {
        test = false;
    }

    QPixmap pixmap(":/Atlas.png");
    QSplashScreen splash(pixmap);
    splash.show();
    app.processEvents();

    MainWindow window(nullptr, test);
    window.show();
    splash.finish(&window);

    return app.exec();
}
