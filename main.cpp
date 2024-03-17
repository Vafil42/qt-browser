#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icons/logo256.png"));
    a.setApplicationDisplayName("Green Bug");
    MainWindow w;
    w.show();
    return a.exec();
}
