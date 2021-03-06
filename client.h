#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include "thclient.h"
#include <QTcpSocket>
#include <QtWebKit>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QTreeWidget>
#include <QList>

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Client(QWidget *parent = 0);
    ~Client();
signals:
    void MAJNouvelle(QByteArray);
    
private slots:
    void on_btnConnecter_clicked();
    void MAJTime(QByteArray);
    void MAJNouvelles(QByteArray);
    void MAJCouleur(QByteArray);
    void on_btnrafraichir_clicked();
    void on_TW_itemActivated(QTreeWidgetItem *item);

public slots:
    void parseXml();
    void readData(const QHttpResponseHeader &resp);

private:
    Ui::Client *ui;
    thclient *m_threadClient;

    //Pour RSS
    int connectionId;
    QXmlStreamReader xml;
    QHttp http;
    QString currentTag;
    QString linkString;
    QString titleString;
    QString dateString;
    QTreeWidgetItem *feed;

};

#endif // CLIENT_H
