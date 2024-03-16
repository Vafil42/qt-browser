#include "tabscontainer.h"

#include <iostream>
#include <QGroupBox>

TabsContainer::TabsContainer(QWidget *parent)
    : QWidget{parent}
{
    mainLayout    = new QVBoxLayout(this);
    headersWidget = new QWidget    ;
    headersLayout = new QHBoxLayout(headersWidget);
    tabLayout     = new QGridLayout;
    addTabButton  = new QPushButton("+");

    mainLayout->setMargin(0);
    headersLayout->setMargin(0);
    mainLayout->addWidget(headersWidget);
    mainLayout->addLayout(tabLayout);
    mainLayout->setAlignment(Qt::AlignTop);

    headersLayout->addWidget(addTabButton);
    headersLayout->setAlignment(Qt::AlignLeft);
    headersWidget->setMaximumHeight(50);

    connect(addTabButton, SIGNAL(clicked(bool)), this, SLOT(addTab()));
}

void TabsContainer::addTab()
{
    TabHeader * newTabHeader = new TabHeader(this);

    connect(newTabHeader, SIGNAL(tabUpdated(Tab*)), this, SLOT(setTab(Tab*)));
    headersLayout    -> insertWidget(headersLayout->count() - 1, newTabHeader);
    if (tabHeader == nullptr) {
        tabHeader = newTabHeader;
        connect(newTabHeader, SIGNAL(deleted()), this, SLOT(removeTabHeader()));
        newTabHeader->madeActive();
        return;
    }
    tabHeader -> addTab    (newTabHeader);
    newTabHeader->madeActive();
}

void TabsContainer::setTab(Tab *tab)
{
    std::cout << tab <<std::endl;
    if (activeTab != nullptr)
        activeTab->setVisible(false);
    activeTab = tab;

    if (tab == nullptr)
        return;

    tabLayout->addWidget(tab);
    activeTab->setVisible(true);
}

void TabsContainer::removeTabHeader()
{
    tabHeader = nullptr;
}
