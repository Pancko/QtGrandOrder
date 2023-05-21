
#include "qtgrandorder.h"
#include "ui_qtgrandorder.h"


QtGrandOrder::QtGrandOrder(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtGrandOrder)
{
    ui->setupUi(this);

    //Лейблы для информации
    label = new QLabel(this);
    ui->m_Label_INFO->setText("");
    //---------------------------------------------------------

    //Первоначально заблокированные кнопки действия и установка первой страницы игры (логина)
    ui->m_pB_Connect->setDisabled(1);
    ui->m_pB_BaseAttack->setDisabled(1);
    ui->m_stackedWidget->setCurrentIndex(0);
    //---------------------------------------------------------

    //Настройка сокета
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &QtGrandOrder::slotReadyRead);
    connect(socket, &QAbstractSocket::stateChanged, this, &QtGrandOrder::Disconnect);
    //---------------------------------------------------------

    //Связка клавиши ENTER для ввода имени и валидатор на имя
    connect(ui->m_lineEdit, SIGNAL(returnPressed()), this, SLOT(on_m_pB_Connect_clicked()));
    QRegularExpression re("([a-z]|[A-Z]).{2,16}");
    QValidator* validator = new QRegularExpressionValidator (re, this);
    ui->m_lineEdit->setValidator(validator);
    //---------------------------------------------------------

    //Привязка кнопок выбора персонажей
    connect(ui->NecoArc, SIGNAL(released()), this, SLOT(CharacterSelection()));
    connect(ui->Dante,   SIGNAL(released()), this, SLOT(CharacterSelection()));
    connect(ui->Gosling, SIGNAL(released()), this, SLOT(CharacterSelection()));
    connect(ui->Cris,    SIGNAL(released()), this, SLOT(CharacterSelection()));
    connect(ui->Uzya,    SIGNAL(released()), this, SLOT(CharacterSelection()));
    connect(ui->Okabe,   SIGNAL(released()), this, SLOT(CharacterSelection()));
    //---------------------------------------------------------

    //Привязка картинок персонажей для выбора их активной целью + отображение хп мп
    CharacterLabels = {ui->Character01, ui->Character02, ui->Character03, ui->Character04, ui->Character05, ui->Character06};
    CharacterStats = {ui->Character01_Stats, ui->Character02_Stats, ui->Character03_Stats, ui->Character04_Stats, ui->Character05_Stats, ui->Character06_Stats};
    for(int i = 0; i < 3; i++)
    {
        connect(CharacterLabels[i], SIGNAL(clicked()),this,SLOT(AllyLabelClicked()));
    }
    for(int i = 3; i < 6; i++)
    {
        connect(CharacterLabels[i], SIGNAL(clicked()),this,SLOT(EnemyLabelClicked()));
    }
    //---------------------------------------------------------

    //Вектора для быстрого обращения к персонажу, его кнопке и скиллам
    CharactersNames = {"Neco Arc", "Dante", "Ryan Gosling", "Cris", "Uzya", "Okabe"};
    CharacterButtons = {ui->NecoArc, ui->Dante, ui->Gosling, ui->Cris, ui->Uzya, ui->Okabe};
    SkillsButtons = {ui->m_pB_Skill1, ui->m_pB_Skill2, ui->m_pB_Skill3};
    //---------------------------------------------------------

    //Блок кнопок выбора персонажей в ожидании второго игрока
    for (int i = 0; i < CharacterButtons.size(); i++)
    {
        CharacterButtons[i]->setDisabled(1);
    }
    //---------------------------------------------------------

    //Привязка кнопок скиллов
    for (int i = 0; i < SkillsButtons.size(); i++)
    {
        connect(SkillsButtons[i], SIGNAL(s_hoverEnter()), this ,SLOT(ShowSkillInfo()));
        connect(SkillsButtons[i], SIGNAL(s_hoverLeave()), this ,SLOT(HideSkillInfo()));
        connect(SkillsButtons[i], SIGNAL(clicked()), this, SLOT(SkillUsed()));
        SkillsButtons[i]->setDisabled(true);
    }
    //---------------------------------------------------------

    //Всплывающее окно с информацией (Для скиллов и эффектов)
    frame = new QTextBrowser(this);
    frame->hide();
    //---------------------------------------------------------

    //Всплывающее окно с информацией о персонаже
    connect(ui->Label_CharacterName, SIGNAL(clicked()), this, SLOT(ShowCharacterInfo()));
    //---------------------------------------------------------

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

            if(CurrentPlayer.Status == "Defeat")
            {
                socket->disconnectFromHost();
                break;
            }

            if(CurrentPlayer.Status == "InGame")
            {
                CurrentPlayer.Status = "TurnGoing";
                Opponent.Status = "Waiting";
                ui->m_pB_BaseAttack->setEnabled(1);
                for (int i = 0; i < SkillsButtons.size(); i++)
                {
                    SkillsButtons[i]->setEnabled(1);
                }
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
                for(int j = 0; j < 3; j++)
                {
                    if(ActiveCharacter.SkillsCDStart[j] > 0)
                    {
                        SkillsButtons[j]->setDisabled(1);
                        if (std::max(CurrentPlayer.CurrentTurn, Opponent.CurrentTurn)
                                - ActiveCharacter.SkillsCDStart[j] >= ActiveCharacter.CharacterSkills[j].Cooldown)
                        {
                            SkillsButtons[j]->setEnabled(1);
                        }
                    }
                    else
                    {
                        SkillsButtons[j]->setEnabled(1);
                    }
                }
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

        if(CurrentPlayer.Status == "Defeat")
        {
            label->setStyleSheet("color: rgb(255, 41, 45);");
            label->setText("Defeated");
        }
        else if (CurrentPlayer.Status == "Victory")
        {
            label->setStyleSheet("color: rgb(57, 255, 12);");
            label->setText("Victory");
        }
        else
        {
            label->setStyleSheet("color: rgb(255, 41, 45);");
            label->setText("Disconnected");
        }
        label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
        label->show();
        //Here is how to change position:
        label->setGeometry(330,185,300,26);
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
        CharacterStats[i]->setText("HP: " + QString::number(CurrentPlayer.CharacterList[i].HP) + "/" + QString::number(CurrentPlayer.CharacterList[i].MaxHP)
                                    + "\nMP: " + QString::number(CurrentPlayer.CharacterList[i].MP) + "/" + QString::number(CurrentPlayer.CharacterList[i].MaxMP));
        CharacterLabels[i]->LabelCharacter = CurrentPlayer.CharacterList[i];
    }
    for(int i = 0; i < Opponent.CharacterList.size(); i++)
    {
        CharacterLabels[i + 3]->setStyleSheet("border-image: url(:CharacterData/CharacterData/" + Opponent.CharacterList[i].CharacterName + "_Image.png) 0 0 0 0 stretch stretch;");
        CharacterStats[i + 3]->setText("HP: " + QString::number(Opponent.CharacterList[i].HP) + "/" + QString::number(Opponent.CharacterList[i].MaxHP)
                                        + "\nMP: " + QString::number(Opponent.CharacterList[i].MP) + "/" + QString::number(Opponent.CharacterList[i].MaxMP));
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
        //Выключение погибшего персонажа, автоматическое переключение активного
        if(CurrentPlayer.CharacterList[i].HP == 0)
        {
            CharacterLabels[i]->setDisabled(1);
            ui->m_pB_BaseAttack->setDisabled(1);
            if(CurrentPlayer.CharacterList[i].CharacterName == ActiveCharacter.CharacterName)
            {
                NextAliveRight(i);
                ActiveCharacterSetUp();
            }
        }
        CharacterStats[i]->setText("HP: " + QString::number(CurrentPlayer.CharacterList[i].HP) + "/" + QString::number(CurrentPlayer.CharacterList[i].MaxHP)
                                    + "\nMP: " + QString::number(CurrentPlayer.CharacterList[i].MP) + "/" + QString::number(CurrentPlayer.CharacterList[i].MaxMP));

        //Обновление Активного персонажа новыми данными
        if (CurrentPlayer.CharacterList[i].CharacterName == ActiveCharacter.CharacterName)
        {
            ActiveCharacter = CurrentPlayer.CharacterList[i];
        }

        //Отсчитывает количество оставшихся ходов активным эффектам и удаляет их
        for (int j = 0; j < CurrentPlayer.CharacterList[i].Effects.size(); j++)
        {
            switch(CurrentPlayer.CharacterList[i].EffectNames.indexOf(CurrentPlayer.CharacterList[i].Effects[j].EffectName))
            {
            case 4: //STUN
            {
                CharacterLabels[i]->setDisabled(1);
                ui->m_pB_BaseAttack->setDisabled(1);
                if(CurrentPlayer.CharacterList[i].CharacterName == ActiveCharacter.CharacterName)
                {
                    NextAliveRight(i);
                    if(CurrentPlayer.CharacterList[i].CharacterName != ActiveCharacter.CharacterName)
                    {
                        ActiveCharacterSetUp();
                    }
                }
                break;
            }
            case 5: //HP_REGEN
            {
                CurrentPlayer.CharacterList[i].HP += (CurrentPlayer.CharacterList[i].MaxHP * CurrentPlayer.CharacterList[i].Effects[j].Magnitude)/100;
                break;
            }
            case 6: //HP_VAMP
            {
                CurrentPlayer.CharacterList[i].HP -= (CurrentPlayer.CharacterList[i].MaxHP * CurrentPlayer.CharacterList[i].Effects[j].Magnitude)/100;
                break;
            }
            case 7: //MP_REGEN
            {
                CurrentPlayer.CharacterList[i].MP += (CurrentPlayer.CharacterList[i].MaxMP * CurrentPlayer.CharacterList[i].Effects[j].Magnitude)/100;
                break;
            }
            case 8: //MP_VAMP
            {
                CurrentPlayer.CharacterList[i].MP -= (CurrentPlayer.CharacterList[i].MaxMP * CurrentPlayer.CharacterList[i].Effects[j].Magnitude)/100;
                break;
            }
            case 10: //MP_REGEN+
            {
                CurrentPlayer.CharacterList[i].MP += (CurrentPlayer.CharacterList[i].MaxMP * CurrentPlayer.CharacterList[i].Effects[j].Magnitude)/100;
                break;
            }
            }

            CurrentPlayer.CharacterList[i].EffectsTurn[j]--;
            qDebug() << "Эффект " << CurrentPlayer.CharacterList[i].Effects[j].EffectName << " Ходов осталось " << CurrentPlayer.CharacterList[i].EffectsTurn[j];
            if(CurrentPlayer.CharacterList[i].EffectsTurn[j] == 0)
            {
                if (CurrentPlayer.CharacterList[i].Effects[j].EffectName == "STUN")
                {
                    CharacterLabels[i]->setEnabled(1);
                }
                CurrentPlayer.CharacterList[i].RemoveEffect(j, &ActiveTarget);
                j--;
            }
        }
    }
    for(int i = 0; i < Opponent.CharacterList.size(); i++)
    {
        CharacterStats[i + 3]->setText("HP: " + QString::number(Opponent.CharacterList[i].HP) + "/" + QString::number(Opponent.CharacterList[i].MaxHP)
                                        + "\nMP: " + QString::number(Opponent.CharacterList[i].MP) + "/" + QString::number(Opponent.CharacterList[i].MaxMP));

        //Отсчитывает количество оставшихся ходов активным эффектам и удаляет их
        if (CurrentPlayer.Status == "Waiting")
        {
            for (int j = 0; j < Opponent.CharacterList[i].Effects.size(); j++)
            {
                switch(Opponent.CharacterList[i].EffectNames.indexOf(Opponent.CharacterList[i].Effects[j].EffectName))
                {
                case 4: //STUN
                {
                    CharacterLabels[i]->setDisabled(1);
                    ui->m_pB_BaseAttack->setDisabled(1);
                    if(Opponent.CharacterList[i].CharacterName == ActiveCharacter.CharacterName)
                    {
                        NextAliveRight(i);
                        if(Opponent.CharacterList[i].CharacterName != ActiveCharacter.CharacterName)
                        {
                            ActiveCharacterSetUp();
                        }
                    }
                    break;
                }
                case 5: //HP_REGEN
                {
                    Opponent.CharacterList[i].HP += (Opponent.CharacterList[i].MaxHP * Opponent.CharacterList[i].Effects[j].Magnitude)/100;
                    break;
                }
                case 6: //HP_VAMP
                {
                    Opponent.CharacterList[i].HP -= (Opponent.CharacterList[i].MaxHP * Opponent.CharacterList[i].Effects[j].Magnitude)/100;
                    break;
                }
                case 7: //MP_REGEN
                {
                    Opponent.CharacterList[i].MP += (Opponent.CharacterList[i].MaxMP * Opponent.CharacterList[i].Effects[j].Magnitude)/100;
                    break;
                }
                case 8: //MP_VAMP
                {
                    Opponent.CharacterList[i].MP -= (Opponent.CharacterList[i].MaxMP * Opponent.CharacterList[i].Effects[j].Magnitude)/100;
                    break;
                }
                case 10: //MP_REGEN+
                {
                    Opponent.CharacterList[i].MP += (Opponent.CharacterList[i].MaxMP * Opponent.CharacterList[i].Effects[j].Magnitude)/100;
                    break;
                }
                }

                Opponent.CharacterList[i].EffectsTurn[j]--;
                qDebug() << "Вражеский Эффект " << Opponent.CharacterList[i].Effects[j].EffectName << " Ходов осталось " << Opponent.CharacterList[i].EffectsTurn[j];

                                                                                                                            if(Opponent.CharacterList[i].EffectsTurn[j] == 0)
                {
                    Opponent.CharacterList[i].RemoveEffect(j, &ActiveTarget);
                    j--;
                }
            }
        }

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
    for(int i = pos + 2; i > pos; i--)
    {
        if(CurrentPlayer.CharacterList[i % 3].HP > 0)
        {
            ActiveCharacter = CurrentPlayer.CharacterList[i % 3];
            break;
        }
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
            break;
        }
    }
    if(found == 0)
    {
        Opponent.Status = "TurnGoing";
        CurrentPlayer.Status = "Waiting";
        SendToServer(Opponent);
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
        CurrentPlayer.Status = "Victory";
        Opponent.Status = "Defeat";
        SendToServer(Opponent);
    }
}

void QtGrandOrder::ActiveCharacterSetUp()
{
    ui->Label_CharacterName->setText(ActiveCharacter.CharacterName);
    for (int i = 0; i < 3; i++)
    {
        SkillsButtons[i]->setText(ActiveCharacter.CharacterSkills[i].SkillName);

        if(ActiveCharacter.SkillsCDStart[i] > 0)
        {
            SkillsButtons[i]->setDisabled(1);
            if (std::max(CurrentPlayer.CurrentTurn, Opponent.CurrentTurn)
                    - ActiveCharacter.SkillsCDStart[i] >= ActiveCharacter.CharacterSkills[i].Cooldown)
            {
            SkillsButtons[i]->setEnabled(1);
            }
        }
    }
    if (CurrentPlayer.Status == "TurnGoing")
    {
        ui->m_pB_BaseAttack->setEnabled(1);
    }
}

//------------------------------------------------------------

//------------------------ BOY ------------------------------- НАДО СДЕЛАТЬ

void QtGrandOrder::on_m_pB_BaseAttack_clicked()
{
    ui->m_Label_INFO->setText("");
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
    }
    CharacterStats[index + 3]->setText("HP: " + QString::number(Opponent.CharacterList[index].HP) + "/" + QString::number(Opponent.CharacterList[index].MaxHP));
    if (CurrentPlayer.Status != "Victory")
    {
        Opponent.Status = "TurnGoing";
        CurrentPlayer.Status = "Waiting";
        ui->m_pB_BaseAttack->setDisabled(1);
        for (int i = 0; i < SkillsButtons.size(); i++)
        {
            SkillsButtons[i]->setDisabled(1);
        }
        SendToServer(Opponent);
    }

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

//---------- Скиллы: информация и использование --------------

void QtGrandOrder::ShowSkillInfo()
{
    Skill ActiveSkill = ActiveCharacter.CharacterSkills[SkillsButtons.indexOf(sender())];
    frame->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    frame->setText(ActiveSkill.SkillDescription + "\nПерезарядка: " + QString::number(ActiveSkill.Cooldown) + " ходов\nСтоимость: " + QString::number(ActiveSkill.MPCost) + " MP");
    frame->setGeometry(QCursor::pos().x(), QCursor::pos().y(), 350, 90);
    frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
    frame->setLineWidth(2);
    frame->show();
}

void QtGrandOrder::HideSkillInfo()
{
    frame->hide();
}

void QtGrandOrder::SkillUsed()
{
    if (ActiveCharacter.MP >= ActiveCharacter.CharacterSkills[SkillsButtons.indexOf(sender())].MPCost)
    {
        ui->m_Label_INFO->setText("");
        ActiveCharacter.SkillsCDStart[SkillsButtons.indexOf(sender())] = std::max(CurrentPlayer.CurrentTurn, Opponent.CurrentTurn);
        ActiveCharacter.MP -= ActiveCharacter.CharacterSkills[SkillsButtons.indexOf(sender())].MPCost;
        for (int i = 0; i < 3; i++)
        {
            if(CurrentPlayer.CharacterList[i].CharacterName == ActiveCharacter.CharacterName)
            {
                CharacterStats[i]->setText("HP: " + QString::number(CurrentPlayer.CharacterList[i].HP) + "/" + QString::number(CurrentPlayer.CharacterList[i].MaxHP)
                                            + "\nMP: " + QString::number(CurrentPlayer.CharacterList[i].MP) + "/" + QString::number(CurrentPlayer.CharacterList[i].MaxMP));
                break;
            }
        }

        SkillsButtons[SkillsButtons.indexOf(sender())]->setDisabled(1);

        switch(Targets.indexOf(ActiveCharacter.CharacterSkills[SkillsButtons.indexOf(sender())].SkillTarget))
        {
        case 0: //SELF
        {
            ActiveCharacter.UseSkill(SkillsButtons.indexOf(sender()), &ActiveCharacter);
            for (int i = 0; i < 3; i++)
            {
                if (ActiveCharacter.CharacterName == CurrentPlayer.CharacterList[i].CharacterName)
                {
                    CurrentPlayer.CharacterList[i] = ActiveCharacter;
                    break;
                }
            }
            SendToServer(CurrentPlayer);
            break;
        }
        case 1: //ENEMY
        {
            if(ActiveCharacter.CharacterSkills[SkillsButtons.indexOf(sender())].SkillName == "I am inside your walls")
            {
                Effect VampTarget("RANDOMSTATVAMPTARGET", 10, 3);
                ActiveCharacter.Stat = rand() % 6;
                ActiveTarget.Stat = ActiveCharacter.Stat;
                ActiveCharacter.ApplyEffect(&ActiveCharacter.CharacterSkills[SkillsButtons.indexOf(sender())].SkillEffects[0], &ActiveTarget);
                ActiveTarget.ApplyEffect(&VampTarget, &ActiveTarget);
            }
            else
            {
                ActiveCharacter.UseSkill(SkillsButtons.indexOf(sender()), &ActiveTarget);
            }

            //Запись в оппонента для передачи
            for (int i = 0; i < 3; i++)
            {
                if(Opponent.CharacterList[i].CharacterName == ActiveTarget.CharacterName)
                {
                    Opponent.CharacterList[i] = ActiveTarget;
                    break;
                }
            }

            SendToServer(Opponent);
            break;
        }
        case 2: //ALLY
        {
            SendToServer(CurrentPlayer);
            break;
        }
        case 3: //ALLALLY
        {
            for (int i = 0; i < 3; i++)
            {
                ActiveCharacter.UseSkill(SkillsButtons.indexOf(sender()), &CurrentPlayer.CharacterList[i]);
            }
            //ActiveCharacter.UseSkill(SkillsButtons.indexOf(sender()), &ActiveCharacter);
            SendToServer(CurrentPlayer);
            break;
        }
        case 4: //ALLENEMY
        {
            for (int i = 0; i < 3; i++)
            {
                ActiveCharacter.UseSkill(SkillsButtons.indexOf(sender()), &Opponent.CharacterList[i]);
            }
            SendToServer(Opponent);
            break;
        }
        case 5: //RANDOMENEMY
        {
            int i = rand() % 3;
            ActiveCharacter.UseSkill(SkillsButtons.indexOf(sender()), &Opponent.CharacterList[i]);
            SendToServer(Opponent);
            break;
        }
        }
    }
    else
    {
        ui->m_Label_INFO->setText("Недостаточно маны");
    }
}

//------------------------------------------------------------

//---------------- Информация о персонаже --------------------

void QtGrandOrder::ShowCharacterInfo()
{
    QString info;
    info = "BaseMPRegen = " + QString::number(ActiveCharacter.BaseMPRegen) + "\nDefence = " + QString::number(ActiveCharacter.Defence)
           + "\nAttack = " + QString::number(ActiveCharacter.BaseAttackDamage);
    for (int i = 0; i < ActiveCharacter.Effects.size(); i++)
    {
        info += "\nEffect name = " + ActiveCharacter.Effects[i].EffectName + "\nMagnitude = " + QString::number(ActiveCharacter.Effects[i].Magnitude)
                + "\nTurns = " + QString::number(ActiveCharacter.Effects[i].Turns);
    }

    frame->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    frame->setText(info);
    frame->setGeometry(QCursor::pos().x(), QCursor::pos().y(), 350, 200);
    frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
    frame->setLineWidth(2);
    frame->show();
}

//------------------------------------------------------------
