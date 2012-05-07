#include "thclient.h"

thclient::thclient(QObject *parent) :
    QThread(parent)
{
}

void thclient::run()
{
    QByteArray BATime;
    QByteArray BANouvelles;
    emit (updatetime(BATime));
    emit (updatetime(BANouvelles));
}

