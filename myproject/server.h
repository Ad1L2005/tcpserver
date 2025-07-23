#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QByteArray>
#include <QTime>
#include "../shared.h"

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QVector<QTcpSocket*> Sockets;

    void SendToClient(QTcpSocket* clientSocket, const QString &str);
    quint16 nextBlockSize;
    QByteArray Data;

private slots:
    void slotReadyRead();
};

#endif // SERVER_H
