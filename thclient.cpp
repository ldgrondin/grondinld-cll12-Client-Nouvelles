#include "thclient.h"

thclient::thclient(QObject *parent) :
    QThread(parent)
{
}

void thclient::changenouvelles(QByteArray valeur)
{
    SendArray = valeur;
    Send=true;
}

void thclient::run()
{

    QByteArray BARec;
    QTcpSocket Serveur;

    Serveur.connectToHost(m_IP,60123);

    if(Serveur.waitForConnected(2000))
    {

        while(1)
        {
            if(Send)
            {
                Serveur.write(SendArray);
                Send=false;
            }
            Serveur.waitForReadyRead(500);

                BARec.append(Serveur.read(Serveur.bytesAvailable()));
                if(BARec.left(1)=="h")
                {
                    emit (updatetime(BARec));
                    emit (updatecouleur(BARec));
                }

                else if (BARec.left(1)=="n")
                    emit (updatenouvelles(BARec));
                BARec.clear();

        }

        Serveur.disconnectFromHost();
        Serveur.close();

    }
}

