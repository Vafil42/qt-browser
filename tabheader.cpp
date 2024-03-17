#include "tabheader.h"

#include <iostream>

TabHeader::TabHeader(QWidget *parent)
    : QGroupBox{parent}
{
    QHBoxLayout *layout = new QHBoxLayout;
    label               = new QLabel;
    removeButton        = new QPushButton;
    tab                 = new Tab;

    removeButton->setSizeIncrement(QSize(50, 50));
    // layout->setMargin(0);
    layout->addWidget(label);
    layout->addWidget(removeButton);
    label->setText("Новая вкладка");
    //setMaximumWidth(300);
    setLayout(layout);
    removeButton->setIcon(QIcon(":/icons/cross.png"));
    layout->setMargin(2);

    connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));
    connect(tab, SIGNAL(titleChanged(QString)), this, SLOT(changeTitle(QString)));
}

TabHeader::~TabHeader()
{
    emit deleted();

    if (next != nullptr & prev != nullptr) {
        next->setPrev(prev);
        prev->setNext(next);
        emit tabUpdated(next->tab);
        delete tab;
        return;
    }

    if (next != nullptr)
        next->setPrev(nullptr);
    if (prev != nullptr)
        prev->setNext(nullptr);

    if (next == nullptr){
        if (prev == nullptr) {
            emit tabUpdated(nullptr);
            delete tab;
            return;
        }

        prev->madeActive();
        delete tab;
        return;
    }

    next->madeActive();
    delete tab;
}

void TabHeader::remove()
{
    delete this;
}

void TabHeader::addTab(TabHeader * newTab)
{
    if (next == nullptr) {
        next = newTab;
        next->setPrev(this);

        return;
    }

    next->addTab(newTab);
}

void TabHeader::setNext(TabHeader * tab)
{
    next = tab;
}

void TabHeader::setPrev(TabHeader * tab)
{
    prev = tab;
}

void TabHeader::madeActive()
{
    isActive = true;
    updateDynamicProperties();

    if (next != nullptr)
        next->setUnactiveNext();

    if (prev != nullptr)
        prev->setUnactivePrev();

    emit tabUpdated(tab);
}

void TabHeader::mousePressEvent(QMouseEvent *event)
{
    madeActive();
}

void TabHeader::updateStyles()
{
    if (isActive) {
        setStyleSheet(MAIN_STYLE + ACTIVE_STYLE);
        return;
    }

    setStyleSheet(MAIN_STYLE + UNACTIVE_STYLE);
}

void TabHeader::setUnactiveNext()
{
    isActive = false;
    updateDynamicProperties();

    if (next != nullptr)
        next->setUnactiveNext();
}

void TabHeader::setUnactivePrev()
{
    isActive = false;
    updateDynamicProperties();

    if (prev != nullptr)
        prev->setUnactivePrev();
}

void TabHeader::changeTitle(QString title)
{
    label->setText(title);
}

void TabHeader::updateDynamicProperties()
{
    setProperty("active", isActive);
    style()->unpolish(this);
    style()->polish(this);
}
