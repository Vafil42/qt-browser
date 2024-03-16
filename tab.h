#ifndef TAB_H
#define TAB_H

#include <QWidget>
#include <QWebEngineView>
#include <QString>
#include <QUrl>
#include <QGridLayout>
#include <QLabel>
#include <QSizePolicy>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class Tab : public QWidget
{
    Q_OBJECT

    QWebEngineView *view = nullptr;
    QVBoxLayout    *mainLayout;
    QHBoxLayout    *urlLayout;
    QWidget        *urlWidget;
    QLineEdit      *urlEdit;
    QPushButton    *urlSubmit;

public:
    explicit Tab(QWidget *parent = nullptr);

private:
    QUrl refactorUrl(QString url);
    void showStartPage();
    void setUrl(QUrl url);

public slots:
    void changeUrlByUser();
    void changeUrl(QUrl);
    void changeTitle(QString);

signals:
    void titleChanged(QString);
};

#endif // TAB_H
