#include "mainwindow.h"
#include "tabscontainer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    container = new TabsContainer(this);
    setCentralWidget(container);
    resize(QSize(800, 600));

    QFile file(":/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    file.close();

    qApp->setStyleSheet(styleSheet);

    container->addTab();
}

MainWindow::~MainWindow()
{
}
