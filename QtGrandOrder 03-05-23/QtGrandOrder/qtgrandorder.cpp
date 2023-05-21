
#include "qtgrandorder.h"
#include "ui_qtgrandorder.h"


QtGrandOrder::QtGrandOrder(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtGrandOrder)
{
    ui->setupUi(this);
    label = new QLabel(this);
    ui->m_pB_Connect->setDisabled(1);
    ui->m_stackedWidget->setCurrentIndex(0);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &QtGrandOrder::slotReadyRead);
    connect(socket, &QAbstractSocket::stateChanged, this, &QtGrandOrder::Disconnect);
    //connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    connect(ui->m_lineEdit, SIGNAL(returnPressed()), this, SLOT(on_m_pB_Connect_clicked()));

    connect(ui->NecoArc, SIGNAL(released()), this, SLOT(CharacterSelection()));
    connect(ui->Dante,   SIGNAL(released()), this, SLOT(CharacterSelection()));
    connect(ui->Gosling, SIGNAL(released()), this, SLOT(CharacterSelection()));
    connect(ui->Cris,    SIGNAL(released()), this, SLOT(CharacterSelection()));
    connect(ui->Uzya,    SIGNAL(released()), this, SLOT(CharacterSelection()));
    connect(ui->Okabe,   SIGNAL(released()), this, SLOT(CharacterSelection()));



    QRegularExpression re("([a-z]|[A-Z]).{2,16}");
    QValidator* validator = new QRegularExpressionValidator (re, this);
    ui->m_lineEdit->setValidator(validator);

    CharactersNames = {"Neco Arc", "Dante", "Ryan Gosling", "Cris", "Uzya", "Okabe"};
    CharacterButtons = {ui->NecoArc, ui->Dante, ui->Gosling, ui->Cris, ui->Uzya, ui->Okabe};

    nextBlockSize = 0;
}

QtGrandOrder::~QtGrandOrder()
{
    delete ui;
}

void QtGrandOrder::on_m_pB_Connect_clicked()
{
    label->clear();
    CurrentPlayer.PlayerName = ui->m_lineEdit->text();
    socket->connectToHost("127.0.0.1", 2253);
    ui->m_stackedWidget->setCurrentIndex(1);
}

void QtGrandOrder::SendToServer(Player &playerData)
{
    //qDebug() << "Data size " << Data.size();
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << quint16(0) << playerData;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    socket->write(Data);
    //qDebug() << "Sent to " << socket->socketDescriptor() << socket->write(Data) << Data.size();
}

void QtGrandOrder::Disconnect()
{
    if(socket->state() == QAbstractSocket::ClosingState)
    {
        ui->m_stackedWidget->setCurrentIndex(0);
        //label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label->setText("Disconnected");
        label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
        label->show();
        //Here is how to change position:
        label->setGeometry(330,185,300,26);
        label->setStyleSheet("color: rgb(255, 41, 45);");
        label->setFont(QFont("Segoe UI", 15, 1 ,false));
    }
}

void QtGrandOrder::GameSetUp()
{
    QVector<QLabel*> CharacterLabels = {ui->Character01, ui->Character02, ui->Character03, ui->Character04, ui->Character05, ui->Character06};
    for(int i = 0; i < CurrentPlayer.CharacterList.size(); i++)
    {
        //qDebug() << "Character show plz" << CurrentPlayer.CharacterList[i].CharacterName;
        CharacterLabels[i]->setStyleSheet("border-image: url(:CharacterData/CharacterData/" + CurrentPlayer.CharacterList[i].CharacterName + "_Image.png) 0 0 0 0 stretch stretch;");
        CharacterLabels[i]->setText("HP: " + QString::number(CurrentPlayer.CharacterList[i].HP) + "/" + QString::number(CurrentPlayer.CharacterList[i].MaxHP));
    }
    for(int i = 0; i < Opponent.CharacterList.size(); i++)
    {
        CharacterLabels[i + 3]->setStyleSheet("border-image: url(:CharacterData/CharacterData/" + Opponent.CharacterList[i].CharacterName + "_Image.png) 0 0 0 0 stretch stretch;");
        CharacterLabels[i + 3]->setText("HP: " + QString::number(Opponent.CharacterList[i].HP) + "/" + QString::number(Opponent.CharacterList[i].MaxHP));
    }

    ui->Label_CharacterName->setText(CurrentPlayer.CharacterList[0].CharacterName);
}

void QtGrandOrder::slotReadyRead()
{
    socket = (QTcpSocket*)sender();
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
                qDebug() << "nextBlockSize = " << nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize)
            {
                break;
            }

            Player playerData;
            in >> playerData;
            nextBlockSize = 0;

            qDebug() << playerData.PlayerName << " Status is " << playerData.Status;

            if (playerData.PlayerName == CurrentPlayer.PlayerName)
            {
                CurrentPlayer = playerData;
                //qDebug() << playerData.PlayerName << " 1Status is " << playerData.Status;
            }
            else if (Opponent.PlayerName == "")
            {
                Opponent = playerData;
                //qDebug() << playerData.PlayerName << " 2Status is " << playerData.Status;
            }
            else if (playerData.PlayerName == Opponent.PlayerName)
            {
                Opponent = playerData;
                //qDebug() << playerData.PlayerName << " 2Status is " << playerData.Status;
            }

            /*if (CurrentPlayer.Status == "Gaming" && Opponent.Status == "InGame")
            {
                CurrentPlayer.Status = "Gaming";
                Opponent.Status = "Gaming";

                GameSetUp();
            }*/

            if(CurrentPlayer.Status == "InGame")
            {
                CurrentPlayer.Status = "Gaming";
                GameSetUp();

                ui->m_stackedWidget->setCurrentIndex(2);
            }
            else if(Opponent.Status == "InGame")
            {
                Opponent.Status = "Gaming";
                GameSetUp();
                qDebug() << "opponent get";

                ui->m_stackedWidget->setCurrentIndex(2);
            }
            else
            {
                for(int i = 0; i < Opponent.CharacterList.size(); i++)
                {
                    if(CharacterButtons[CharactersNames.indexOf(Opponent.CharacterList[i].CharacterName)]->isEnabled())
                    {
                        CharacterButtons[CharactersNames.indexOf(Opponent.CharacterList[i].CharacterName)]->setDisabled(1);
                    }
                }
            }
            //Выдача приколов при хорошей передаче
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
    CharList.setFileName(":CharacterData/CharacterData/" + sender()->objectName() + ".json");
    CharList.open(QIODevice::ReadOnly | QIODevice::Text);
    QString info = CharList.readAll();
    QJsonObject obj = QJsonDocument::fromJson(info.toUtf8()).object();
    CharList.close();

    Character Char(obj);
    CurrentPlayer.CharacterList.push_back(Char);
    if(CurrentPlayer.CharacterList.size() == 3)
    {
        CurrentPlayer.Status = "Ready";
        //отправить сигнал готовности
    }

    qDebug() << Char.CharacterName << CharactersNames.indexOf(Char.CharacterName);

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
    qDebug() << Char.CharacterName;

    CharacterButtons[CharactersNames.indexOf(Char.CharacterName)]->setDisabled(1);
    qDebug() << Char.CharacterName;
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

