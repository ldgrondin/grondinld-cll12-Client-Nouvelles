#include "thclient.h"

thclient::thclient(QObject *parent) :
    QThread(parent)
{
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
            while(Serveur.waitForReadyRead())
            {
                BARec.append(Serveur.read(Serveur.bytesAvailable()));
                if(BARec.left(1)=="h")
                {
                    emit (updatetime(BARec));
                    Serveur.write("h");
                }

                else if (BARec.left(1)=="n")
                    emit (updatenouvelles(BARec));
                else
                {
                    emit (updatecouleur(BARec));
                    Serveur.write("c");
                }
            }
        }

        Serveur.disconnectFromHost();
        Serveur.close();

    }
}

