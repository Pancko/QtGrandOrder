
#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QLocalSocket>
#include <QThread>
#include "..\QtGrandOrder\player.h"
#include "session.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QTcpServer//, public QMainWindow
{
    Q_OBJECT

public:
    Server();
    QTcpSocket *socket;

private:
    QVector<QTcpSocket*> Sockets;
    QVector<qintptr> SocketsDescriptors;
    QByteArray Data;
    void SendToClient(Player &playerData);
    quint16 nextBlockSize;

    QVector<Session> Sessions;

private:
    void Disconnect();

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
};

#endif // SERVER_H
