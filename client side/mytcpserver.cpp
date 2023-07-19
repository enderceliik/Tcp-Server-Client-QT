#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent)
    : QObject{parent}
{
    // constructor method is temporarily empty
}
QByteArray MyTcpServer::communicateWithServer(QByteArray dispatchData)
{
    QTcpSocket* socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 9999);
    if (socket->waitForConnected(3000))
    {
        qDebug() << "Server connection successfull!";

        socket->write(dispatchData);

        if (socket->waitForBytesWritten(5000))
        {
            qDebug() << "JSON data has been successfully sent to the server.";
        }
        else
        {
            qDebug() << "Failed to send JSON data to server.";
            // return yapisi
        }
        if (socket->waitForReadyRead(2000)) // Sure ayarlanabilir sunucunun durumuna gore
        {
            dispatchData.clear();
            dispatchData = socket->readAll();
        }
    } else {
        qDebug() << "Server connection failed!";
    }
    socket->close();
    socket->deleteLater();
    return dispatchData;
}

void MyTcpServer::salesTransaction(QJsonObject jsonObject)
{
//    QByteArray responseFromServer; // Temprary for now.
    QJsonDocument jsonDocument(jsonObject);
    QByteArray jsonDataByteArray = jsonDocument.toJson();
    QByteArray responseFromServer = communicateWithServer(jsonDataByteArray);
    QJsonParseError jsonParseError;
    jsonDocument = QJsonDocument::fromJson(responseFromServer,&jsonParseError);
    if(jsonParseError.error != QJsonParseError::NoError)
    {
        qDebug() << "JSON Parse error: " << jsonParseError.errorString();
        return;
    }
    if(jsonDocument.isObject())
    {
        QJsonObject jsonObject = jsonDocument.object();
        int salePrice = jsonObject.value("salePrice").toInt();
        QString officierID = jsonObject.value("officierID").toString();
        qDebug() << "Sale price: " + QString::number(salePrice);
        qDebug() << "Officier ID: " + officierID;
    }
}



// multipleconnection
    // wireshark
//    QJsonObject jsonObject;
//    jsonObject["name"] = "John Doe";
//    jsonObject["age"] = 30;
//    QJsonArray jsonArray;
//    QJsonObject obj1;
//    obj1["id"] = 201705;
//    obj1["amount"] = 16;
//    obj1["price"] = 48;
//    jsonArray.append(obj1);

//    QJsonObject obj2;
//    obj2["id"] = 201761;
//    obj2["amount"] = 9;
//    obj2["price"] = 27;
//    jsonArray.append(obj2);


//    QJsonDocument jsonDocument(jsonArray);
//    QByteArray jsonData = jsonDocument.toJson();
//    socket->write(jsonData);
//    if (socket->waitForBytesWritten()) {
//        qDebug() << "JSON data has been successfully sent to the server.";
//    } else {
//        qDebug() << "Failed to send JSON data to server.";
//            return;
//    }





