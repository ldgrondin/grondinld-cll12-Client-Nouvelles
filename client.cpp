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
    connect(&http, SIGNAL(readyRead(const QHttpResponseHeader &)), this,SLOT(readData(const QHttpResponseHeader &)));
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
    QUrl url(Nouvelles);

    //Connection au signal RSS
    http.setHost(url.host());
    connectionId = http.get(url.path());
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

void Client::on_TW_itemActivated(QTreeWidgetItem *item)
{
    ui->WV->load(QUrl(item->text(2)));
    ui->WV->show();
}

void Client::readData(const QHttpResponseHeader &resp)
 {
    //Lis le contenu du signal RSS
     if (resp.statusCode() != 200)
         http.abort();
     else {
         xml.addData(http.readAll());
         parseXml();
     }

 }
//Addition et affichage dans l'arbre des nouvelles
void Client::parseXml()
 {

     while (!xml.atEnd()) {
         xml.readNext();
         if (xml.isStartElement()) {

             if (xml.name() == "item"){

                 if (titleString!=""){
                    feed = new QTreeWidgetItem;
                    feed->setText(0, titleString);
                    feed->setText(2, linkString);
                    ui->TW->addTopLevelItem(feed);

                 }

                 linkString.clear();
                 titleString.clear();
                 dateString.clear();
             }

             currentTag = xml.name().toString();
         } else if (xml.isEndElement()) {
              if (xml.name() == "item") {

                 QTreeWidgetItem *item = new QTreeWidgetItem(feed);
                 item->setText(0, titleString);
                 item->setText(1, dateString);
                 item->setText(2, linkString);
                 ui->TW->addTopLevelItem(item);

                 titleString.clear();
                 linkString.clear();
                 dateString.clear();
             }

         } else if (xml.isCharacters() && !xml.isWhitespace()) {
             if (currentTag == "title")
                 titleString += xml.text().toString();
             else if (currentTag == "link")
                 linkString += xml.text().toString();
             else if (currentTag == "pubDate")
                 dateString += xml.text().toString();
         }
     }
     if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError) {
         qWarning() << "XML ERROR:" << xml.lineNumber() << ": " << xml.errorString();
         http.abort();
     }
     //Ouvre le premier élément du QTreeWidget
     ui->TW->expandItem(ui->TW->itemAt(0,0));

     //Affiche la première nouvelle
     //À voir ......

     //Redimensionne les 2 premières colonnes
     ui->TW->resizeColumnToContents(0);
     ui->TW->resizeColumnToContents(1);
 }
