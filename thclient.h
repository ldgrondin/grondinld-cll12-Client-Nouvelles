#ifndef THCLIENT_H
#define THCLIENT_H

#include <QThread>
#include <QTcpSocket>

class thclient : public QThread
{
    Q_OBJECT
public:
    explicit thclient(QObject *parent = 0);
    QString m_IP;

protected:
    void run();

private slots:
    void changenouvelles(QByteArray);

signals:
    void updatetime(QByteArray);
    void updatenouvelles(QByteArray);
    void updatecouleur(QByteArray);
    
public slots:
    
private:
    QByteArray SendArray;
    bool Send;
};

#endif // THCLIENT_H
