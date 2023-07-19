#include <QCoreApplication>
#include <mytcpserver.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyTcpServer myTcpServer;
    QJsonObject jsonObject;
    jsonObject["salePrice"] = 56;
    jsonObject["officierID"] = "2%19%1";
    myTcpServer.salesTransaction(jsonObject);
    return a.exec();
}
