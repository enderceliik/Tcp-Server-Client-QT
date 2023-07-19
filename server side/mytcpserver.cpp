#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    if (!server->listen(QHostAddress::Any, 9999))
    {
        qDebug() << "Server could not started!";
    }
    else
    {
        qDebug() << "Server started!";
    }
}
void MyTcpServer::newConnection()
{
    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &MyTcpServer::onReadyRead);
    // if sorgusu socket dinler sorgusu
//    socket->write("Hello Client! \r\n");
//    socket->flush();
//    socket->waitForBytesWritten(1500);
//    socket->close();
}

void MyTcpServer::onReadyRead()
{
    socket = qobject_cast<QTcpSocket*>(sender());
    if(socket)
    {
        QByteArray jsonData = socket->readAll();
        QJsonParseError jsonParseError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData,&jsonParseError);
        if(jsonParseError.error != QJsonParseError::NoError)
        {
            qDebug() << "JSON Parse error: " << jsonParseError.errorString();
            return;
        }
        if(jsonDocument.isArray())
        {
            QJsonArray jsonArray = jsonDocument.array();
            for (const QJsonValue& value : jsonArray) {
                    qDebug() << value;
                }
        }
        else if(jsonDocument.isObject())
        {
            QJsonObject jsonObject = jsonDocument.object();
            int salePrice = jsonObject.value("salePrice").toInt();
            QString officierID = jsonObject.value("officierID").toString();
            qDebug() << "Sale price: " + QString::number(salePrice);
            qDebug() << "Officier ID: " + officierID;
            jsonObject["salePrice"] = 150;
            jsonObject["officierID"] = "654981";
            QJsonDocument jsonDocument(jsonObject);
            QByteArray jsonData = jsonDocument.toJson();
            socket->write(jsonData);

            if (socket->waitForBytesWritten(5000))
            {
                qDebug() << "JSON data has been successfully sent to the client.";
            }
        }
    }
}
