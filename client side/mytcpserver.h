#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    void salesTransaction(QJsonObject jsonObject);
    QByteArray communicateWithServer(QByteArray dispatchData);

signals:

private:
//    QTcpSocket* socket;
};

#endif // MYTCPSERVER_H
