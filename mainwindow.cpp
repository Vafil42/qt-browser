#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tabscontainer.h"

#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    container = new TabsContainer(this);
    ui->gridLayout->addWidget(container);
}

MainWindow::~MainWindow()
{
    delete ui;
}
