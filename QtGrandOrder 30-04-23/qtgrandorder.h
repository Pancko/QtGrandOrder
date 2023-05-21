
#ifndef QTGRANDORDER_H
#define QTGRANDORDER_H

#include <QMainWindow>
#include <QTcpSocket>
#include "player.h"
#include <QStackedWidget>
#include <QFile>


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

    void on_m_pB_Choice1_clicked();

private:
    Ui::QtGrandOrder *ui;
    QTcpSocket *socket;
    QByteArray Data;
    void SendToServer(Player *playerData);
    quint16 nextBlockSize;

    Player CurrentPlayer;

public slots:
    void slotReadyRead();
};

#endif // QTGRANDORDER_H
