
#ifndef QTGRANDORDER_H
#define QTGRANDORDER_H

#include <QMainWindow>
#include <QTcpSocket>
#include "player.h"
#include <QStackedWidget>
#include <QFile>
#include <QPushButton>
#include "clickablelabel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class QtGrandOrder; }
QT_END_NAMESPACE

class QtGrandOrder : public QMainWindow

{
    Q_OBJECT

public:
    QtGrandOrder(QWidget *parent = nullptr);
    ~QtGrandOrder();

private slots:
    void on_m_pB_Connect_clicked();

    void CharacterSelection();

    void on_m_lineEdit_textEdited(const QString &arg1);

    void on_pB_Skill_clicked();

    void on_pB_Attack_clicked();

    void on_pB_Inventory_clicked();

    void on_pB_Character_Left_clicked();

    void on_pB_Character_Right_clicked();

    void on_m_pB_BaseAttack_clicked();

    void AllyLabelClicked();

    void EnemyLabelClicked();

private:
    Ui::QtGrandOrder *ui;
    //Приколюхи для сервера
    QTcpSocket *socket;
    QByteArray Data;
    void SendToServer(Player &playerData);
    quint16 nextBlockSize;

    //Игроки
    Player CurrentPlayer;
    Player Opponent;

    //Персонажи и скиллы
    QVector<QString> CharactersNames;
    QVector<QPushButton*> CharacterButtons;
    QVector<ClickableLabel*> CharacterLabels;
    QVector<QPushButton*> SkillsButtons;

    //Активный персонаж и цель
    Character ActiveCharacter;
    Character ActiveTarget;
    void ActiveCharacterSetUp();

    //Дисконнект
    void Disconnect();

    //Disconnect Label
    QLabel *label;

    //Подготовка игрового окна
    void GameSetUp();

    //Апдейт боя
    void BattleUpdate();

    //Боевые моменты
    void NextAliveLeft(int pos);
    void NextAliveRight(int pos);
    void NextAliveTargetLeft(int pos);
    void NextAliveTargetRight(int pos);

public slots:
    void slotReadyRead();
};

#endif // QTGRANDORDER_H
