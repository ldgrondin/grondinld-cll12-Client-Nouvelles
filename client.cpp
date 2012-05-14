#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    m_threadClient = new thclient();
    connect(m_threadClient, SIGNAL(updatetime(QByteArray)), this, SLOT(MAJTime(QByteArray)));
    connect(m_threadClient, SIGNAL(updatenouvelles(QByteArray)), this, SLOT(MAJNouvelles(QByteArray)));
    connect(m_threadClient, SIGNAL(updatecouleur(QByteArray)), this, SLOT(MAJCouleur(QByteArray)));
    connect(this,SIGNAL(MAJNouvelle(QByteArray)),m_threadClient,SLOT(changenouvelles(QByteArray)));
}

Client::~Client()
{
    delete ui;
}

void Client::MAJTime(QByteArray Temps)
{
    QString Stemps = Temps.left(9);
    Stemps = Stemps.remove(0,1);
    ui->lblHeure->setText(Stemps);
}

void Client::MAJNouvelles(QByteArray Nouvelles)
{

}

void Client::MAJCouleur(QByteArray Couleur)
{
    this->setPalette(QColor((uchar)Couleur[10],(uchar)Couleur[11],(uchar)Couleur[12]));
}

void Client::on_btnConnecter_clicked()
{
   QByteArray type;
   int Ntype;
   m_threadClient->m_IP = ui->txtIP->text();
   m_threadClient->start();
   Ntype = ui->cbtype->currentIndex();
   type = QByteArray::number(Ntype);
   emit MAJNouvelle(type);
}

void Client::on_btnrafraichir_clicked()
{
    QByteArray type;
    int Ntype;
    Ntype = ui->cbtype->currentIndex();
    type = QByteArray::number(Ntype);
    emit MAJNouvelle(type);
}
