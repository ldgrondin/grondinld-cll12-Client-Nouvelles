#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include "thclient.h"
#include <QTcpSocket>

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

private:
    Ui::Client *ui;
    thclient *m_threadClient;

};

#endif // CLIENT_H
