#ifndef TABHEADER_H
#define TABHEADER_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStyleOption>
#include <QGroupBox>

#include "tab.h"

class TabHeader : public QGroupBox
{
    Q_OBJECT

    TabHeader   * next = nullptr;
    TabHeader   * prev = nullptr;
    QLabel      * label;
    Tab         * tab;
    QPushButton * removeButton;

    QString MAIN_STYLE =
        "border-radius: 5;"
        "border: 1 solid white;"
        "padding: 5;"
        ;

    QString UNACTIVE_STYLE =
        "background-color: green;"
        ;

    QString ACTIVE_STYLE =
        "background-color: red;"
        ;

public:
    explicit TabHeader(QWidget *parent = nullptr);
    ~TabHeader();
    void addTab (TabHeader *newTab);
    void setNext(TabHeader *);
    void setPrev(TabHeader *);
    void madeActive();
    Tab *getTab();

public slots:
    void remove();
    void changeTitle(QString);

signals:
    void tabUpdated(Tab *);
    void deleted();

private:
    void mousePressEvent(QMouseEvent *event) override;
    bool isActive;
    void setUnactivePrev();
    void setUnactiveNext();
    void updateStyles();
};

#endif // TABHEADER_H
