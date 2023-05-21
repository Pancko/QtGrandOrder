
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

    connect(ui->m_lineEdit, SIGNAL(returnPressed()), this, SLOT(on_m_pB_Connect_clicked()));

    connect(ui->NecoArc, SIGNAL(released()), this, SLOT(CharacterSelection()));
    connect(ui->Dante,   SIGNAL(released()), this, SLOT(CharacterSelection()));
    connect(ui->Gosling, SIGNAL(released()), this, SLOT(CharacterSelection()));
    connect(ui->Cris,    SIGNAL(released()), this, SLOT(CharacterSelection()));
    connect(ui->Uzya,    SIGNAL(released()), this, SLOT(CharacterSelection()));
    connect(ui->Okabe,   SIGNAL(released()), this, SLOT(CharacterSelection()));


    CharacterLabels = {ui->Character01, ui->Character02, ui->Character03, ui->Character04, ui->Character05, ui->Character06};
    for(int i = 0; i < 3; i++)
    {
        connect(CharacterLabels[i], SIGNAL(clicked()),this,SLOT(AllyLabelClicked()));
    }
    for(int i = 3; i < 6; i++)
    {
        connect(CharacterLabels[i], SIGNAL(clicked()),this,SLOT(EnemyLabelClicked()));
    }


    QRegularExpression re("([a-z]|[A-Z]).{2,16}");
    QValidator* validator = new QRegularExpressionValidator (re, this);
    ui->m_lineEdit->setValidator(validator);

    CharactersNames = {"Neco Arc", "Dante", "Ryan Gosling", "Cris", "Uzya", "Okabe"};
    CharacterButtons = {ui->NecoArc, ui->Dante, ui->Gosling, ui->Cris, ui->Uzya, ui->Okabe};
    SkillsButtons = {ui->m_pB_Skill1, ui->m_pB_Skill2, ui->m_pB_Skill3};

    for (int i = 0; i < CharacterButtons.size(); i++)
    {
        CharacterButtons[i]->setDisabled(1);
    }

    ui->m_pB_BaseAttack->setDisabled(1);

    nextBlockSize = 0;
}

QtGrandOrder::~QtGrandOrder()
{
    delete ui;
}

//-----------------Взаимодействие с сервером------------------

void QtGrandOrder::on_m_pB_Connect_clicked()
{
    label->clear();
    CurrentPlayer.PlayerName = ui->m_lineEdit->text();
    socket->connectToHost("127.0.0.1", 2253);
    SendToServer(CurrentPlayer);
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
                //qDebug() << "nextBlockSize = " << nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize)
            {
                break;
            }

            Player playerData;
            in >> playerData;
            nextBlockSize = 0;


            if (playerData.PlayerName == CurrentPlayer.PlayerName)
            {
                CurrentPlayer = playerData;
                if (CurrentPlayer.Status == "CharacterSelection")
                {
                    for (int i = 0; i < CharacterButtons.size(); i++)
                    {
                        CharacterButtons[i]->setEnabled(1);
                    }
                    for(int i = 0; i < CurrentPlayer.CharacterList.size(); i++)
                    {
                        CharacterButtons[CharactersNames.indexOf(CurrentPlayer.CharacterList[i].CharacterName)]->setDisabled(1);
                    }
                    for(int i = 0; i < Opponent.CharacterList.size(); i++)
                    {
                        CharacterButtons[CharactersNames.indexOf(Opponent.CharacterList[i].CharacterName)]->setDisabled(1);
                    }
                    break;
                }
                else if ((CurrentPlayer.Status == "CharacterSelected") || (CurrentPlayer.Status == "Ready"))
                {
                    for (int i = 0; i < CharacterButtons.size(); i++)
                    {
                        CharacterButtons[i]->setDisabled(1);
                    }
                    break;
                }
            }
            else if (Opponent.PlayerName == "")
            {
                Opponent = playerData;
                if ((Opponent.Status == "CharacterSelected") || (Opponent.Status == "Ready"))
                {
                    CurrentPlayer.Status = "CharacterSelection";
                    for (int i = 0; i < CharacterButtons.size(); i++)
                    {
                        CharacterButtons[i]->setEnabled(1);
                    }
                    for(int i = 0; i < CurrentPlayer.CharacterList.size(); i++)
                    {
                        CharacterButtons[CharactersNames.indexOf(CurrentPlayer.CharacterList[i].CharacterName)]->setDisabled(1);
                    }
                    for(int i = 0; i < Opponent.CharacterList.size(); i++)
                    {
                        CharacterButtons[CharactersNames.indexOf(Opponent.CharacterList[i].CharacterName)]->setDisabled(1);
                    }
                    break;
                }
                //qDebug() << playerData.PlayerName << " 2Status is " << playerData.Status;
            }
            else if (playerData.PlayerName == Opponent.PlayerName)
            {
                Opponent = playerData;
                if ((Opponent.Status == "CharacterSelected") || (Opponent.Status == "Ready"))
                {
                    CurrentPlayer.Status = "CharacterSelection";
                    for (int i = 0; i < CharacterButtons.size(); i++)
                    {
                        CharacterButtons[i]->setEnabled(1);
                    }
                    for(int i = 0; i < CurrentPlayer.CharacterList.size(); i++)
                    {
                        CharacterButtons[CharactersNames.indexOf(CurrentPlayer.CharacterList[i].CharacterName)]->setDisabled(1);
                    }
                    for(int i = 0; i < Opponent.CharacterList.size(); i++)
                    {
                        CharacterButtons[CharactersNames.indexOf(Opponent.CharacterList[i].CharacterName)]->setDisabled(1);
                    }
                    break;
                }
            }

            if(CurrentPlayer.Status == "InGame")
            {
                CurrentPlayer.Status = "TurnGoing";
                Opponent.Status = "Waiting";
                ui->m_pB_BaseAttack->setEnabled(1);
                GameSetUp();

                ui->m_stackedWidget->setCurrentIndex(2);
            }
            else if(Opponent.Status == "InGame")
            {
                Opponent.Status = "TurnGoing";
                CurrentPlayer.Status = "Waiting";
                GameSetUp();

                ui->m_stackedWidget->setCurrentIndex(2);
            }

            BattleUpdate();
            if (CurrentPlayer.Status == "TurnGoing")
            {
                ui->m_pB_BaseAttack->setEnabled(1);
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

//------------------------------------------------------------


//-------------------Настройка игровой сцены------------------

void QtGrandOrder::GameSetUp()
{
    ui->Label_TurnsCount->setText("1");
    for(int i = 0; i < CurrentPlayer.CharacterList.size(); i++)
    {
        CharacterLabels[i]->setStyleSheet("border-image: url(:CharacterData/CharacterData/" + CurrentPlayer.CharacterList[i].CharacterName + "_Image.png) 0 0 0 0 stretch stretch;");
        CharacterLabels[i]->setText("HP: " + QString::number(CurrentPlayer.CharacterList[i].HP) + "/" + QString::number(CurrentPlayer.CharacterList[i].MaxHP));
        CharacterLabels[i]->LabelCharacter = CurrentPlayer.CharacterList[i];
    }
    for(int i = 0; i < Opponent.CharacterList.size(); i++)
    {
        CharacterLabels[i + 3]->setStyleSheet("border-image: url(:CharacterData/CharacterData/" + Opponent.CharacterList[i].CharacterName + "_Image.png) 0 0 0 0 stretch stretch;");
        CharacterLabels[i + 3]->setText("HP: " + QString::number(Opponent.CharacterList[i].HP) + "/" + QString::number(Opponent.CharacterList[i].MaxHP));
        CharacterLabels[i + 3]->LabelCharacter = Opponent.CharacterList[i];
    }

    ui->CurrentPlayerLabel->setText(CurrentPlayer.PlayerName);
    ui->OpponentLabel->setText(Opponent.PlayerName);

    ActiveCharacter = CurrentPlayer.CharacterList[0];
    ActiveCharacterSetUp();
}

void QtGrandOrder::BattleUpdate()
{
    ui->Label_TurnsCount->setText(QString::number(std::max(CurrentPlayer.CurrentTurn, Opponent.CurrentTurn)));
    for(int i = 0; i < CurrentPlayer.CharacterList.size(); i++)
    {
        if(CurrentPlayer.CharacterList[i].HP == 0)
        {
            CharacterLabels[i]->setDisabled(1);
            if(CurrentPlayer.CharacterList[i].CharacterName == ActiveCharacter.CharacterName)
            {
                NextAliveRight(i);
                ActiveCharacterSetUp();
            }
        }
        CharacterLabels[i]->setText("HP: " + QString::number(CurrentPlayer.CharacterList[i].HP) + "/" + QString::number(CurrentPlayer.CharacterList[i].MaxHP));
    }
    for(int i = 0; i < Opponent.CharacterList.size(); i++)
    {
        CharacterLabels[i + 3]->setText("HP: " + QString::number(Opponent.CharacterList[i].HP) + "/" + QString::number(Opponent.CharacterList[i].MaxHP));
    }
}

//------------------------------------------------------------


//-----------------Выбор персонажа------------------

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

    //qDebug() << Char.CharacterName << CharactersNames.indexOf(Char.CharacterName);

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
}

//--------------------------------------------------


//-----------------Ввод имени игрока------------------

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

//----------------------------------------------------


//-----------Переключение действий------------------

void QtGrandOrder::on_pB_Attack_clicked()
{
    ui->m_stackedWidget_Options->setCurrentIndex(0);
}

void QtGrandOrder::on_pB_Skill_clicked()
{
    ui->m_stackedWidget_Options->setCurrentIndex(1);
}

void QtGrandOrder::on_pB_Inventory_clicked()
{
    ui->m_stackedWidget_Options->setCurrentIndex(2);
}

//--------------------------------------------------


//----------Переключение активного персонажа------------------

void QtGrandOrder::on_pB_Character_Left_clicked()
{
    int CurrentPos = 0;
    for (int i = 0; i < 3; i++)
    {
        if (CurrentPlayer.CharacterList[i].CharacterName == ActiveCharacter.CharacterName)
        {
            CurrentPos = i;
            break;
        }
    }
    NextAliveLeft(CurrentPos);
    ActiveCharacterSetUp();
}

void QtGrandOrder::on_pB_Character_Right_clicked()
{
    int CurrentPos = 0;
    for (int i = 0; i < 3; i++)
    {
        if (CurrentPlayer.CharacterList[i].CharacterName == ActiveCharacter.CharacterName)
        {
            CurrentPos = i;
            break;
        }
    }
    NextAliveRight(CurrentPos);
    ActiveCharacterSetUp();
}

void QtGrandOrder::NextAliveLeft(int pos)
{
    int found = 0;
    for(int i = pos + 2; i > pos; i--)
    {
        if(CurrentPlayer.CharacterList[i % 3].HP > 0)
        {
            ActiveCharacter = CurrentPlayer.CharacterList[i % 3];
            found = 1;
            break;
        }
    }
    if(found == 0)
    {
        ui->m_stackedWidget->setCurrentIndex(0);
        //label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label->setText("Defeated");
        label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
        label->show();
        //Here is how to change position:
        label->setGeometry(330,185,300,26);
        label->setStyleSheet("color: rgb(255, 41, 45);");
        label->setFont(QFont("Segoe UI", 15, 1 ,false));
        CurrentPlayer.Status = "Defeated";
        SendToServer(CurrentPlayer);
    }
}

void QtGrandOrder::NextAliveRight(int pos)
{
    int found = 0;
    for(int i = pos + 1; i < pos + 3; i++)
    {
        if(CurrentPlayer.CharacterList[i % 3].HP > 0)
        {
            ActiveCharacter = CurrentPlayer.CharacterList[i % 3];
            found = 1;
            break;
        }
    }
    if(found == 0)
    {
        ui->m_stackedWidget->setCurrentIndex(0);
        //label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label->setText("Defeated");
        label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
        label->show();
        //Here is how to change position:
        label->setGeometry(330,185,300,26);
        label->setStyleSheet("color: rgb(255, 41, 45);");
        label->setFont(QFont("Segoe UI", 15, 1 ,false));
        CurrentPlayer.Status = "Defeated";
        SendToServer(CurrentPlayer);
    }
}

void QtGrandOrder::NextAliveTargetRight(int pos)
{
    int found = 0;
    for(int i = pos + 1; i < pos + 3; i++)
    {
        if(Opponent.CharacterList[i % 3].HP > 0)
        {
            ActiveTarget = Opponent.CharacterList[i % 3];
            CharacterLabels[i % 3 + 3]->setStyleSheet("border-image: url(:CharacterData/CharacterData/" +
                                                      Opponent.CharacterList[i % 3].CharacterName + "_TargetImage.png) 0 0 0 0 stretch stretch;");
            found = 1;
            break;
        }
    }
    if(found == 0)
    {
        ui->m_stackedWidget->setCurrentIndex(0);
        //label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label->setText("МОЛОДЕЦ");
        label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
        label->show();
        //Here is how to change position:
        label->setGeometry(330,185,300,26);
        label->setStyleSheet("color: rgb(255, 41, 45);");
        label->setFont(QFont("Segoe UI", 15, 1 ,false));
        //CurrentPlayer.Status = "МОЛОДЕЦ";
        //SendToServer(CurrentPlayer);
        //Дисконнект сделать
    }
}

void QtGrandOrder::ActiveCharacterSetUp()
{
    ui->Label_CharacterName->setText(ActiveCharacter.CharacterName);
    for (int i = 0; i < 3; i++)
    {
        SkillsButtons[i]->setText(ActiveCharacter.CharacterSkills[i].SkillName);
    }
}

//------------------------------------------------------------


//------------------------ BOY ------------------------------- НАДО СДЕЛАТЬ

void QtGrandOrder::on_m_pB_BaseAttack_clicked()
{
    int index = 0;
    for (int i = 0; i < 3; i++)
    {
        if(Opponent.CharacterList[i].CharacterName == ActiveTarget.CharacterName)
        {
            index = i;
            break;
        }
    }
    Opponent.CharacterList[index].takeDamage(ActiveCharacter.BaseAttackDamage);
    if(Opponent.CharacterList[index].HP == 0)
    {
        //можно вставить серую картинку
        CharacterLabels[index + 3]->setStyleSheet("border-image: url(:CharacterData/CharacterData/" +
                                                  Opponent.CharacterList[index].CharacterName + "_Image.png) 0 0 0 0 stretch stretch;");
        CharacterLabels[index + 3]->setDisabled(1);
        NextAliveTargetRight(index);
        //переключение таргета на следующего врага
    }
    CharacterLabels[index + 3]->setText("HP: " + QString::number(Opponent.CharacterList[index].HP) + "/" + QString::number(Opponent.CharacterList[index].MaxHP));
    Opponent.Status = "TurnGoing";
    CurrentPlayer.Status = "Waiting";
    ui->m_pB_BaseAttack->setDisabled(1);
    SendToServer(Opponent);
}



//------------------------------------------------------------

//------------Выбор цели и активного персонажа-----------------

void QtGrandOrder::AllyLabelClicked()
{
    ActiveCharacter = qobject_cast<ClickableLabel*>(sender())->LabelCharacter;
    ActiveCharacterSetUp();
}

void QtGrandOrder::EnemyLabelClicked()
{
    int index = 0;
    if (ActiveTarget.CharacterName != "")
    {
        for (int i = 0; i < 3; i++)
        {
            if(Opponent.CharacterList[i].CharacterName == ActiveTarget.CharacterName)
            {
                index = i;
                break;
            }
        }
        CharacterLabels[index + 3]->setStyleSheet("border-image: url(:CharacterData/CharacterData/" +
                                                  Opponent.CharacterList[index].CharacterName + "_Image.png) 0 0 0 0 stretch stretch;");
    }

    ActiveTarget = qobject_cast<ClickableLabel*>(sender())->LabelCharacter;
    for (int i = 0; i < 3; i++)
    {
        if(Opponent.CharacterList[i].CharacterName == ActiveTarget.CharacterName)
        {
            index = i;
            break;
        }
    }
    CharacterLabels[index + 3]->setStyleSheet("border-image: url(:CharacterData/CharacterData/" +
                                              Opponent.CharacterList[index].CharacterName + "_TargetImage.png) 0 0 0 0 stretch stretch;");
}

//------------------------------------------------------------
