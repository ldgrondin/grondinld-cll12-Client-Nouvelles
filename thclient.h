#ifndef THCLIENT_H
#define THCLIENT_H

#include <QThread>

class thclient : public QThread
{
    Q_OBJECT
public:
    explicit thclient(QObject *parent = 0);

protected:
    void run();

signals:
    void updatetime(QByteArray);
    void updatenouvelles(QByteArray);
    
public slots:
    
};

#endif // THCLIENT_H
