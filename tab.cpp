#include "tab.h"

#include <QGroupBox>

Tab::Tab(QWidget *parent)
    : QWidget{parent}
{
    mainLayout    = new QVBoxLayout;
    urlWidget     = new QWidget;
    urlLayout     = new QHBoxLayout;
    urlEdit       = new QLineEdit;
    urlSubmit     = new QPushButton;
    backButton    = new QPushButton;
    forwardButton = new QPushButton;
    reloadButton  = new QPushButton;

    setLayout(mainLayout);
    mainLayout->addWidget(urlWidget);
    urlWidget->setLayout(urlLayout);
    urlLayout->addWidget(backButton);
    urlLayout->addWidget(forwardButton);
    urlLayout->addWidget(reloadButton);
    urlLayout->addWidget(urlEdit);
    urlLayout->addWidget(urlSubmit);

    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    urlWidget->setObjectName("url-widget");

    urlSubmit    ->setIcon(QIcon(":/icons/search.png"));
    backButton   ->setIcon(QIcon(":/icons/arrow-left.png"));
    forwardButton->setIcon(QIcon(":/icons/arrow-right.png"));
    reloadButton ->setIcon(QIcon(":/icons/rotate-right.png"));

    connect(urlSubmit, SIGNAL(clicked()), this, SLOT(changeUrlByUser()));
    connect(urlEdit, SIGNAL(editingFinished()), this, SLOT(changeUrlByUser()));

    showStartPage();
}

QUrl Tab::refactorUrl(QString url)
{
    if (url.contains("http://") | url.contains("https://"))
        return url;
    return QUrl(QString("https://google.com/search?q=%1").arg(url.replace(" ", "+")));
}

void Tab::showStartPage()
{
    startPageWidget              = new QWidget;
    QVBoxLayout *startPageLayout = new QVBoxLayout;
    QLabel      *startPageTitle  = new QLabel("Welcome to Green Bug.\nStart searching with url field on the top.");
    QLabel      *startPageImage  = new QLabel;

    mainLayout->addWidget(startPageWidget);
    startPageWidget->setLayout(startPageLayout);
    startPageLayout->addWidget(startPageImage);
    startPageLayout->addWidget(startPageTitle);

    startPageLayout->setAlignment(Qt::AlignCenter);
    startPageTitle->setAlignment(Qt::AlignCenter);
    startPageImage->setAlignment(Qt::AlignCenter);

    startPageLayout->setSpacing(50);
    startPageLayout->setMargin(100);

    QFont font = QFont();
    font.setPixelSize(30);
    startPageTitle->setFont(font);

    startPageImage->setPixmap(QPixmap(":/icons/logo256.png").scaled(QSize(256, 256)));

}

void Tab::setUrl(QUrl url)
{
    if (view == nullptr){
        startPageWidget->setVisible(false);
        view = new QWebEngineView;
        view->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
        mainLayout->addWidget(view);

        connect(view, SIGNAL(urlChanged(QUrl)), this, SLOT(changeUrl(QUrl)));
        connect(view, SIGNAL(titleChanged(QString)), this, SLOT(changeTitle(QString)));
        connect(backButton, SIGNAL(clicked()), view, SLOT(back()));
        connect(forwardButton, SIGNAL(clicked()), view, SLOT(forward()));
        connect(reloadButton, SIGNAL(clicked()), view, SLOT(reload()));
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
