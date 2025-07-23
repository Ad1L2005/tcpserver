#include "server.h"
#include <QDataStream>
#include <QDebug>
#include "../shared.h"

Server::Server()
{
    if (this->listen(QHostAddress::Any, 2323)) {
        qDebug() << "Server started";
    } else {
        qDebug() << "Server error";
    }
    nextBlockSize = 0;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *clientSocket = new QTcpSocket(this);
    clientSocket->setSocketDescriptor(socketDescriptor);

    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, [=]() {
        Sockets.removeAll(clientSocket);
        clientSocket->deleteLater();
    });

    Sockets.push_back(clientSocket);


}

void Server::slotReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    QDataStream in(clientSocket);
    in.setVersion(QDataStream::Qt_6_2);

    if (in.status() == QDataStream::Ok)
    {
        for(;;)
        {

            if(nextBlockSize == 0)
            {
                qDebug() << "nextBlockSize = 0";
                if(clientSocket -> bytesAvailable() < 2)
                {
                    qDebug() << "Data < 2, break";
                    break;
                }
                in >> nextBlockSize;
                qDebug() << "nextBlockSize = " << nextBlockSize;
            }
            if(clientSocket -> bytesAvailable() < nextBlockSize)
            {
                qDebug() << "Data not full, break";
                break;
            }
            QString str;
            QTime time;
            in >> time >> str;
            nextBlockSize = 0;
            qDebug() << str;
            SendToClient(clientSocket, str);
            break;
        }

    }
    else
    {
        qDebug() << "Ошибка чтения DataStream";
    }
}

void Server::SendToClient(QTcpSocket *clientSocket, const QString &str)
{
    ClientInfo info;
    info.time = QTime::currentTime();
    info.message = str;
    info.clientCount = Sockets.size();

    QByteArray Data;
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);

    out << quint16(0);

    out << info;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));

    for (QTcpSocket* socket : Sockets)
    {
        if (socket && socket->state() == QAbstractSocket::ConnectedState)
        {
            socket->write(Data);
        }
    }
}


