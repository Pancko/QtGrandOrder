
#include "qtgrandorder.h"
#include "ui_qtgrandorder.h"


QtGrandOrder::QtGrandOrder(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtGrandOrder)
{
    ui->setupUi(this);
    ui->m_stackedWidget->setCurrentIndex(0);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &QtGrandOrder::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    nextBlockSize = 0;
}

QtGrandOrder::~QtGrandOrder()
{
    delete ui;
}



void QtGrandOrder::on_m_pB_Connect_clicked()
{
    socket->connectToHost("127.0.0.1", 2253);
    ui->m_stackedWidget->setCurrentIndex(1);
}

void QtGrandOrder::SendToServer(Player *playerData)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << quint16(0) << playerData;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    socket->write(Data);
}

void QtGrandOrder::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_5);
    if(in.status() == QDataStream::Ok)
    {
        for(;;)
        {
            if(nextBlockSize == 0)
            {
                if(socket->bytesAvailable() < 2)
                {
                    break;
                }
                in >> nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize)
            {
                break;
            }

            Player playerData;
            in >> playerData;
            nextBlockSize = 0;
            //Выдача приколов (в примере: ui->textBrowser->append(playerData))
        }
    }
    else
    {
        //Выдать ошибку
    }
}


void QtGrandOrder::on_m_pB_Choice1_clicked()
{
    QFile CharList;
    CharList.setFileName("F:/Qt_projs/QtGrandOrder/CharacterData/NecoArc.json");
    CharList.open(QIODevice::ReadOnly | QIODevice::Text);
    QString info = CharList.readAll();
    QJsonObject obj = QJsonDocument::fromJson(info.toUtf8()).object();
    CharList.close();

    Character Char(obj);
    CurrentPlayer.CharacterList[0] = &Char;
    qDebug() << CurrentPlayer.CharacterList[0]->CharacterName;

    ui->m_pB_Choice1->setDisabled(1);
}

