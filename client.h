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
    
private slots:
    void on_btnConnecter_clicked();
    void MAJTime(QByteArray);
    void MAJNouvelles(QByteArray);

private:
    Ui::Client *ui;

};

#endif // CLIENT_H
