
#ifndef QTGRANDORDER_H
#define QTGRANDORDER_H

#include <QMainWindow>
#include <QTcpSocket>
#include "player.h"
#include <QStackedWidget>
#include <QFile>
#include <QPushButton>


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

    //Персонажи
    QVector<QString> CharactersNames;
    QVector<QPushButton*> CharacterButtons;

    //Дисконнект
    void Disconnect();

    QLabel *label;

    //Подготовка игрового окна
    void GameSetUp();

public slots:
    void slotReadyRead();
};

#endif // QTGRANDORDER_H
