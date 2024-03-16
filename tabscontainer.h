#ifndef TABSCONTAINER_H
#define TABSCONTAINER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "tabheader.h"

class TabsContainer : public QWidget
{
    Q_OBJECT

    QVBoxLayout *mainLayout;
    QWidget     *headersWidget;
    QHBoxLayout *headersLayout;
    QGridLayout *tabLayout;
    QPushButton *addTabButton;

public:
    explicit TabsContainer(QWidget *parent = nullptr);

private:
    TabHeader *tabHeader = nullptr;
    Tab       *activeTab = nullptr;

public slots:
    void addTab();
    void setTab(Tab *);
    void removeTabHeader();

signals:
};

#endif // TABSCONTAINER_H
