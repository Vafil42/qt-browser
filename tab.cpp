#include "tab.h"

#include <QGroupBox>

Tab::Tab(QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QVBoxLayout;
    urlWidget  = new QWidget;
    urlLayout  = new QHBoxLayout;
    urlEdit    = new QLineEdit;
    urlSubmit  = new QPushButton("Les GO");

    setLayout(mainLayout);
    mainLayout->addWidget(urlWidget);
    urlWidget->setLayout(urlLayout);
    urlLayout->addWidget(urlEdit);
    urlLayout->addWidget(urlSubmit);

    urlLayout->setMargin(0);
    mainLayout->setMargin(0);

    connect(urlSubmit, SIGNAL(clicked()), this, SLOT(changeUrlByUser()));
    connect(urlEdit, SIGNAL(editingFinished()), this, SLOT(changeUrlByUser()));
}

QUrl Tab::refactorUrl(QString url)
{
    if (url.contains("http://") | url.contains("https://"))
        return url;
    return QUrl(QString("https://google.com/search?q=%1").arg(url.replace(" ", "+")));
}

void Tab::showStartPage()
{
    if (view != nullptr)
        delete view;
}

void Tab::setUrl(QUrl url)
{
    if (view == nullptr){
        view = new QWebEngineView;
        view->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
        mainLayout->addWidget(view);

        connect(view, SIGNAL(urlChanged(QUrl)), this, SLOT(changeUrl(QUrl)));
        connect(view, SIGNAL(titleChanged(QString)), this, SLOT(changeTitle(QString)));
    }
    view->setUrl(url);
}

void Tab::changeUrlByUser()
{
    QString url = urlEdit->text();
    setUrl(refactorUrl(url));
}

void Tab::changeUrl(QUrl url)
{
    QString textUrl = url.toString();
    urlEdit->setText(textUrl);
}

void Tab::changeTitle(QString title)
{
    emit titleChanged(title);
}
