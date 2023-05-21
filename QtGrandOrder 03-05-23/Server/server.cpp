
#include "server.h"

Server::Server()
{
    if(this->listen(QHostAddress::Any, 2253))
    {
        qDebug() << "Server started";
    }
    else
    {
        qDebug() << "Error";
    }
    Sessions.resize(1);
    nextBlockSize = 0;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QAbstractSocket::stateChanged, this, &Server::Disconnect);
    //connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    Sockets.push_back(socket);
    SocketsDescriptors.push_back(socketDescriptor);

    qDebug() << "sessions size =" << Sessions.size();
    for (int i = 0; i < Sessions.size(); i++)
    {
        if (!(Sessions[i].Player1socketDescriptor) || !(Sessions[i].Player2socketDescriptor))
        {
            if(!Sessions[i].Player1socketDescriptor)
            {
                Sessions[i].Player1socketDescriptor = socketDescriptor;
                Sessions[i].Player1.GameID = i;
                qDebug() << "Client "<< socketDescriptor << "connected to session" << i;
                break;
            }
            else
            {
                Sessions[i].Player2socketDescriptor = socketDescriptor;
                Sessions[i].Player2.GameID = i;
                qDebug() << "Client "<< socketDescriptor << "connected to session" << i;
                if (i == Sessions.size() - 1)
                {
                    Sessions.resize(Sessions.size() + 1);
                }
                break;
            }
        }
    }
}

void Server::slotReadyRead()
{
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_5);
    if(in.status() == QDataStream::Ok)
    {
        qDebug() << "reading...";

        for(;;)
        {
            if(nextBlockSize == 0)
            {
                qDebug() << "nextBlockSize = 0";

                if(socket->bytesAvailable() < 2)
                {
                    qDebug() << "Data < 2, break";
                    break;
                }
                in >> nextBlockSize;
                qDebug() << "nextBlockSize = " << nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize)
            {
                qDebug() << "Data not full, break";
                break;
            }

            Player playerData;
            in >> playerData;

            if(playerData.GameID == 0)
            {
                for (int i = 0; i < Sessions.size(); i++)
                {
                    if ((Sessions[i].Player1socketDescriptor == socket->socketDescriptor()) ||
                        (Sessions[i].Player2socketDescriptor == socket->socketDescriptor()))
                    {
                        playerData.GameID = i + 1;
                        break;
                    }
                }
            }

            if(Sessions[playerData.GameID - 1].Player1.PlayerName == "")
            {
                Sessions[playerData.GameID - 1].Player1 = playerData;
            }
            else if (playerData.PlayerName == Sessions[playerData.GameID - 1].Player1.PlayerName)
            {
                Sessions[playerData.GameID - 1].Player1 = playerData;
            }
            else if (Sessions[playerData.GameID - 1].Player2.PlayerName == "")
            {
                Sessions[playerData.GameID - 1].Player2 = playerData;
            }
            else if (playerData.PlayerName == Sessions[playerData.GameID - 1].Player2.PlayerName)
            {
                Sessions[playerData.GameID - 1].Player2 = playerData;
            }

            if(Sessions[playerData.GameID - 1].Player1.Status == "Ready" && Sessions[playerData.GameID - 1].Player2.Status == "Ready")
            {
                Sessions[playerData.GameID - 1].Player1.Status = "InGame";
                Sessions[playerData.GameID - 1].Player2.Status = "InGame";
            }

            if(socket->socketDescriptor() == Sessions[playerData.GameID - 1].Player1socketDescriptor)
            {
                SendToClient(Sessions[playerData.GameID - 1].Player1);
            }
            else
            {
                SendToClient(Sessions[playerData.GameID - 1].Player2);
            }
            nextBlockSize = 0;

            qDebug() << "1 Player - " << Sessions[playerData.GameID - 1].Player1.PlayerName
                                      << Sessions[playerData.GameID - 1].Player1.Status << "Session" << Sessions[playerData.GameID - 1].Player1.GameID - 1;
            qDebug() << "2 Player - " << Sessions[playerData.GameID - 1].Player2.PlayerName
                                      << Sessions[playerData.GameID - 1].Player2.Status << "Session" << Sessions[playerData.GameID - 1].Player2.GameID - 1;

            break;
        }
    }
    else
    {
        qDebug() << "QDataStream error";
    }
}

void Server::SendToClient(Player &playerData)
{
    Data.clear();
    qDebug() << "Sending to client " << playerData.PlayerName;
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << quint16(0) << playerData;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    for (int i = 0; i < Sockets.size(); i++)
    {
        Sockets[i]->write(Data);
    }
}

void Server::Disconnect()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    qintptr DisconnectedDescriptor;
    if(client->state() == QAbstractSocket::ClosingState)
    {
        for(int i = 0; i < Sockets.size(); i++)
        {
            if(Sockets[i]->socketDescriptor() != SocketsDescriptors[i])
            {
                Sockets.remove(i);
                Sockets.squeeze();
                DisconnectedDescriptor = SocketsDescriptors[i];
                SocketsDescriptors.remove(i);
                SocketsDescriptors.squeeze();
                break;
            }
        }
        qDebug() << "Client" << DisconnectedDescriptor << "Disconnected";
        if(client)
        {
            for (int i = 0; i < Sessions.size(); i++)
            {
                if((Sessions[i].Player1socketDescriptor == DisconnectedDescriptor) ||
                    (Sessions[i].Player2socketDescriptor == DisconnectedDescriptor))
                {
                    if(Sessions[i].Player1socketDescriptor == DisconnectedDescriptor)
                    {
                        QLocalSocket AnotherPlayer;
                        AnotherPlayer.setSocketDescriptor(Sessions[i].Player2socketDescriptor);
                        AnotherPlayer.disconnect();
                        //disconnect 2 player
                    }
                    else
                    {
                        QLocalSocket AnotherPlayer;
                        AnotherPlayer.setSocketDescriptor(Sessions[i].Player1socketDescriptor);
                        AnotherPlayer.disconnect();
                        //disconnect 1 player
                    }
                    Sessions[i].Player1socketDescriptor = 0;
                    Sessions[i].Player2socketDescriptor = 0;
                    Sessions[i].Player1.PlayerName = "";
                    Sessions[i].Player2.PlayerName = "";
                    Sessions[i].Player1.Status = "";
                    Sessions[i].Player2.Status = "";
                    break;
                }
            }

            client->deleteLater();
        }
        else
        {
            // Handle error
        }
    }

}

