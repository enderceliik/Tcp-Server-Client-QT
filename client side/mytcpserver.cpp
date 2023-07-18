#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent)
    : QObject{parent}
{
    QTcpSocket* socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 9999);
    if (socket->waitForConnected()) {
        qDebug() << "Server connection successful!";
    } else {
        qDebug() << "Server connection failed!";
        return;
    }

    QJsonObject jsonObject;
    jsonObject["name"] = "John Doe";
    jsonObject["age"] = 30;

    QJsonDocument jsonDocument(jsonObject);
    QByteArray jsonData = jsonDocument.toJson();
    socket->write(jsonData);
    if (socket->waitForBytesWritten()) {
        qDebug() << "JSON data has been successfully sent to the server.";
    } else {
        qDebug() << "Failed to send JSON data to server.";
            return;
    }
    if (socket->waitForReadyRead()) {
        QByteArray responseData = socket->readAll();
        qDebug() << "Response from server: " << responseData;
    }
    socket->close();
}
