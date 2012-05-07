#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    thclient *m_threadClient = new thclient();
    connect(m_threadClient, SIGNAL(updatetime(QByteArray)), this, SLOT(MAJTime(QByteArray)));
    connect(m_threadClient, SIGNAL(updatenouvelles(QByteArray)), this, SLOT(MAJNouvelles(QByteArray)));
}

Client::~Client()
{
    delete ui;
}

void Client::MAJTime(QByteArray Temps)
{

}

void Client::MAJNouvelles(QByteArray Nouvelles)
{

}

void Client::on_btnConnecter_clicked()
{

}
