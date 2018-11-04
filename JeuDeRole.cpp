#include "mainWindowController.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*MainWindow w;
    w.show();*/
    MainWindowController controllerApplication(&a);

    return a.exec();
}
