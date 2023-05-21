
#include "qtgrandorder.h"
#include "ui_qtgrandorder.h"


QtGrandOrder::QtGrandOrder(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtGrandOrder)
{
    ui->setupUi(this);
    ui->m_pB_Connect->setDisabled(1);
    ui->m_stackedWidget->setCurrentIndex(0);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &QtGrandOrder::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    connect(ui->NecoArc, SIGNAL(released()), this, SLOT(CharacterSelection()));
    connect(ui->Dante,   SIGNAL(released()), this, SLOT(CharacterSelection()));
  //connect(ui->NecoArc, SIGNAL(released()), this, SLOT(CharacterSelection()));
  //connect(ui->NecoArc, SIGNAL(released()), this, SLOT(CharacterSelection()));
  //connect(ui->NecoArc, SIGNAL(released()), this, SLOT(CharacterSelection()));
  //connect(ui->NecoArc, SIGNAL(released()), this, SLOT(CharacterSelection()));



    QRegularExpression re("([a-z]|[A-Z]).{2,16}");
    QValidator* validator = new QRegularExpressionValidator (re, this);
    ui->m_lineEdit->setValidator(validator);

    nextBlockSize = 0;
}

QtGrandOrder::~QtGrandOrder()
{
    delete ui;
}

void QtGrandOrder::on_m_pB_Connect_clicked()
{

    CurrentPlayer.PlayerName = ui->m_lineEdit->text();
    socket->connectToHost("127.0.0.1", 2253);
    ui->m_stackedWidget->setCurrentIndex(1);
}

void QtGrandOrder::SendToServer(Player &playerData)
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
            break;
        }
    }
    else
    {
        //Выдать ошибку
    }
}

void QtGrandOrder::CharacterSelection()
{
    QFile CharList;
    CharList.setFileName("F:/Qt_projs/QtGrandOrder/CharacterData/" + sender()->objectName() + ".json");
    CharList.open(QIODevice::ReadOnly | QIODevice::Text);
    QString info = CharList.readAll();
    QJsonObject obj = QJsonDocument::fromJson(info.toUtf8()).object();
    CharList.close();

    Character Char(obj);
    CurrentPlayer.CharacterList.push_back(Char);
    if(CurrentPlayer.CharacterList.size() == 3)
    {
        //отправить сигнал готовности
    }

    qDebug() << CurrentPlayer.CharacterList[CurrentPlayer.CharacterList.size() - 1].CharacterName;

    /*-------------------------------------------------------
    qDebug() << CurrentPlayer.PlayerName;
    qDebug() << CurrentPlayer.CharacterList[0].CharacterName;
    qDebug() << CurrentPlayer.CharacterList[0].Speed;
    qDebug() << CurrentPlayer.CharacterList[0].MaxHP;
    qDebug() << CurrentPlayer.CharacterList[0].MaxMP;
    qDebug() << CurrentPlayer.CharacterList[0].Defence;
    qDebug() << CurrentPlayer.CharacterList[0].EnergyCost;
    qDebug() << CurrentPlayer.CharacterList[0].BaseAttackDamage;
    for(int i = 0; i < 3; i++)
    {
        qDebug() << CurrentPlayer.CharacterList[0].CharacterSkills[i].SkillName
                 << CurrentPlayer.CharacterList[0].CharacterSkills[i].SkillDescription
                 << CurrentPlayer.CharacterList[0].CharacterSkills[i].SkillIcon
                 << CurrentPlayer.CharacterList[0].CharacterSkills[i].SkillTarget
                 << CurrentPlayer.CharacterList[0].CharacterSkills[i].SkillEffect.EffectName
                 << CurrentPlayer.CharacterList[0].CharacterSkills[i].SkillEffect.Turns
                 << CurrentPlayer.CharacterList[0].CharacterSkills[i].Cooldown;
    }
    *///-------------------------------------------------------

    SendToServer(CurrentPlayer);
    //ui->(QPushButton *)sender()->setDisabled(1); - заблокировать кнопку через сервер яхз

    sender()->blockSignals(1);
}





void QtGrandOrder::on_m_lineEdit_textEdited(const QString &arg1)
{
    if(ui->m_lineEdit->text().size() > 2)
    {
        ui->m_pB_Connect->setDisabled(0);
    }
    else
    {
        ui->m_pB_Connect->setDisabled(1);
    }
}

