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
    QTcpSocket *socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &MyTcpServer::onReadyRead);
//    socket->write("Hello Client! \r\n");
//    socket->flush();
//    socket->waitForBytesWritten(48000);
//    socket->close();
}

void MyTcpServer::onReadyRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
	if(socket)
	{
		QByteArray jsonData = socket->readAll();
//        qDebug() << "Received message from  client: " << data;
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
			QString name = jsonObject.value("name").toString();
			int age = jsonObject.value("age").toInt();
			qDebug() << name;
		}
    }
}
