/********************************************************************************
** Form generated from reading UI file 'qtgrandorder.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGRANDORDER_H
#define UI_QTGRANDORDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "clickablelabel.h"
#include "hoveringpushbutton.h"

QT_BEGIN_NAMESPACE

class Ui_QtGrandOrder
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QStackedWidget *m_stackedWidget;
    QWidget *page_AMenu;
    QGridLayout *gridLayout;
    QLineEdit *m_lineEdit;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QPushButton *m_pB_Connect;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QWidget *page_Characters;
    QGridLayout *gridLayout_3;
    QPushButton *Gosling;
    QPushButton *Dante;
    QPushButton *NecoArc;
    QPushButton *Okabe;
    QPushButton *Uzya;
    QPushButton *Cris;
    QLabel *m_label;
    QWidget *page_Game;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_6;
    QLabel *Label_TurnsCount;
    QLabel *OpponentLabel;
    QLabel *Label_Turn;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *CurrentPlayerLabel;
    QFrame *frame_2;
    QGridLayout *gridLayout_9;
    QLabel *m_Label_INFO;
    ClickableLabel *Character03;
    ClickableLabel *Character02;
    ClickableLabel *Character01;
    QLabel *Character01_Stats;
    QLabel *Character02_Stats;
    QLabel *Character03_Stats;
    QFrame *frame;
    QGridLayout *gridLayout_5;
    QPushButton *pB_Attack;
    QPushButton *pB_Character_Right;
    QStackedWidget *m_stackedWidget_Options;
    QWidget *page_attack;
    QGridLayout *gridLayout_7;
    QPushButton *m_pB_BaseAttack;
    QWidget *page_Skills;
    QGridLayout *gridLayout_8;
    HoveringPushButton *m_pB_Skill1;
    HoveringPushButton *m_pB_Skill2;
    HoveringPushButton *m_pB_Skill3;
    HoveringPushButton *m_pB_Ult;
    QWidget *page_Inventory;
    QPushButton *pB_Inventory;
    QPushButton *pB_Character_Left;
    QPushButton *pB_Skill;
    ClickableLabel *Label_CharacterName;
    QFrame *frame_3;
    QGridLayout *gridLayout_10;
    ClickableLabel *Character05;
    ClickableLabel *Character06;
    ClickableLabel *Character04;
    QLabel *Character04_Stats;
    QLabel *Character06_Stats;
    QLabel *Character05_Stats;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QtGrandOrder)
    {
        if (QtGrandOrder->objectName().isEmpty())
            QtGrandOrder->setObjectName("QtGrandOrder");
        QtGrandOrder->resize(967, 618);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QtGrandOrder->sizePolicy().hasHeightForWidth());
        QtGrandOrder->setSizePolicy(sizePolicy);
        QtGrandOrder->setMinimumSize(QSize(960, 580));
        QtGrandOrder->setSizeIncrement(QSize(16, 9));
        centralwidget = new QWidget(QtGrandOrder);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        m_stackedWidget = new QStackedWidget(centralwidget);
        m_stackedWidget->setObjectName("m_stackedWidget");
        page_AMenu = new QWidget();
        page_AMenu->setObjectName("page_AMenu");
        gridLayout = new QGridLayout(page_AMenu);
        gridLayout->setObjectName("gridLayout");
        m_lineEdit = new QLineEdit(page_AMenu);
        m_lineEdit->setObjectName("m_lineEdit");
        QFont font;
        font.setPointSize(14);
        font.setBold(false);
        m_lineEdit->setFont(font);
        m_lineEdit->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_lineEdit, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 1, 1, 1);

        label = new QLabel(page_AMenu);
        label->setObjectName("label");
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8(""));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 1, 1, 1);

        m_pB_Connect = new QPushButton(page_AMenu);
        m_pB_Connect->setObjectName("m_pB_Connect");

        gridLayout->addWidget(m_pB_Connect, 3, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(301, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 1, 1, 1);

        m_stackedWidget->addWidget(page_AMenu);
        page_Characters = new QWidget();
        page_Characters->setObjectName("page_Characters");
        gridLayout_3 = new QGridLayout(page_Characters);
        gridLayout_3->setObjectName("gridLayout_3");
        Gosling = new QPushButton(page_Characters);
        Gosling->setObjectName("Gosling");
        Gosling->setMinimumSize(QSize(0, 60));

        gridLayout_3->addWidget(Gosling, 3, 0, 1, 1);

        Dante = new QPushButton(page_Characters);
        Dante->setObjectName("Dante");
        Dante->setMinimumSize(QSize(0, 60));

        gridLayout_3->addWidget(Dante, 1, 1, 1, 1);

        NecoArc = new QPushButton(page_Characters);
        NecoArc->setObjectName("NecoArc");
        NecoArc->setMinimumSize(QSize(0, 60));

        gridLayout_3->addWidget(NecoArc, 1, 0, 1, 1);

        Okabe = new QPushButton(page_Characters);
        Okabe->setObjectName("Okabe");
        Okabe->setMinimumSize(QSize(0, 60));

        gridLayout_3->addWidget(Okabe, 4, 1, 1, 1);

        Uzya = new QPushButton(page_Characters);
        Uzya->setObjectName("Uzya");
        Uzya->setMinimumSize(QSize(0, 60));

        gridLayout_3->addWidget(Uzya, 4, 0, 1, 1);

        Cris = new QPushButton(page_Characters);
        Cris->setObjectName("Cris");
        Cris->setMinimumSize(QSize(0, 60));

        gridLayout_3->addWidget(Cris, 3, 1, 1, 1);

        m_label = new QLabel(page_Characters);
        m_label->setObjectName("m_label");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(24);
        font2.setBold(true);
        font2.setItalic(false);
        m_label->setFont(font2);
        m_label->setLayoutDirection(Qt::LeftToRight);
        m_label->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(m_label, 0, 0, 1, 2);

        m_stackedWidget->addWidget(page_Characters);
        page_Game = new QWidget();
        page_Game->setObjectName("page_Game");
        gridLayout_4 = new QGridLayout(page_Game);
        gridLayout_4->setObjectName("gridLayout_4");
        groupBox = new QGroupBox(page_Game);
        groupBox->setObjectName("groupBox");
        groupBox->setMaximumSize(QSize(16777215, 50));
        gridLayout_6 = new QGridLayout(groupBox);
        gridLayout_6->setObjectName("gridLayout_6");
        Label_TurnsCount = new QLabel(groupBox);
        Label_TurnsCount->setObjectName("Label_TurnsCount");
        Label_TurnsCount->setFont(font1);

        gridLayout_6->addWidget(Label_TurnsCount, 0, 4, 1, 1);

        OpponentLabel = new QLabel(groupBox);
        OpponentLabel->setObjectName("OpponentLabel");
        OpponentLabel->setMinimumSize(QSize(200, 0));
        OpponentLabel->setFont(font1);
        OpponentLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(OpponentLabel, 0, 6, 1, 1);

        Label_Turn = new QLabel(groupBox);
        Label_Turn->setObjectName("Label_Turn");
        Label_Turn->setFont(font1);

        gridLayout_6->addWidget(Label_Turn, 0, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_4, 0, 5, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        CurrentPlayerLabel = new QLabel(groupBox);
        CurrentPlayerLabel->setObjectName("CurrentPlayerLabel");
        CurrentPlayerLabel->setMinimumSize(QSize(200, 0));
        CurrentPlayerLabel->setFont(font1);

        gridLayout_6->addWidget(CurrentPlayerLabel, 0, 1, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 4);

        frame_2 = new QFrame(page_Game);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_9 = new QGridLayout(frame_2);
        gridLayout_9->setObjectName("gridLayout_9");
        m_Label_INFO = new QLabel(frame_2);
        m_Label_INFO->setObjectName("m_Label_INFO");
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(true);
        m_Label_INFO->setFont(font3);

        gridLayout_9->addWidget(m_Label_INFO, 0, 0, 1, 1);

        Character03 = new ClickableLabel(frame_2);
        Character03->setObjectName("Character03");
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Character03->sizePolicy().hasHeightForWidth());
        Character03->setSizePolicy(sizePolicy1);
        Character03->setMinimumSize(QSize(150, 200));
        Character03->setMaximumSize(QSize(16777215, 16777215));
        QFont font4;
        font4.setBold(true);
        Character03->setFont(font4);
        Character03->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout_9->addWidget(Character03, 1, 2, 1, 1);

        Character02 = new ClickableLabel(frame_2);
        Character02->setObjectName("Character02");
        sizePolicy1.setHeightForWidth(Character02->sizePolicy().hasHeightForWidth());
        Character02->setSizePolicy(sizePolicy1);
        Character02->setMinimumSize(QSize(150, 200));
        Character02->setMaximumSize(QSize(16777215, 16777215));
        Character02->setFont(font4);
        Character02->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout_9->addWidget(Character02, 1, 1, 1, 1);

        Character01 = new ClickableLabel(frame_2);
        Character01->setObjectName("Character01");
        sizePolicy1.setHeightForWidth(Character01->sizePolicy().hasHeightForWidth());
        Character01->setSizePolicy(sizePolicy1);
        Character01->setMinimumSize(QSize(150, 200));
        QFont font5;
        font5.setBold(true);
        font5.setItalic(false);
        font5.setKerning(true);
        Character01->setFont(font5);
        Character01->setStyleSheet(QString::fromUtf8("QLabel{\n"
"border-image: url(F:/Qt_projs/QtGrandOrder/release/CharacterData/Neco Arc_Image.png) 0 0 0 0 stretch stretch;\n"
"}"));
        Character01->setTextFormat(Qt::AutoText);
        Character01->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout_9->addWidget(Character01, 1, 0, 1, 1);

        Character01_Stats = new QLabel(frame_2);
        Character01_Stats->setObjectName("Character01_Stats");
        Character01_Stats->setFont(font4);

        gridLayout_9->addWidget(Character01_Stats, 2, 0, 1, 1);

        Character02_Stats = new QLabel(frame_2);
        Character02_Stats->setObjectName("Character02_Stats");
        Character02_Stats->setFont(font4);

        gridLayout_9->addWidget(Character02_Stats, 2, 1, 1, 1);

        Character03_Stats = new QLabel(frame_2);
        Character03_Stats->setObjectName("Character03_Stats");
        Character03_Stats->setFont(font4);

        gridLayout_9->addWidget(Character03_Stats, 2, 2, 1, 1);


        gridLayout_4->addWidget(frame_2, 3, 0, 1, 2, Qt::AlignBottom);

        frame = new QFrame(page_Game);
        frame->setObjectName("frame");
        frame->setMaximumSize(QSize(16777215, 180));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame);
        gridLayout_5->setObjectName("gridLayout_5");
        pB_Attack = new QPushButton(frame);
        pB_Attack->setObjectName("pB_Attack");
        pB_Attack->setMinimumSize(QSize(120, 35));

        gridLayout_5->addWidget(pB_Attack, 2, 0, 1, 1);

        pB_Character_Right = new QPushButton(frame);
        pB_Character_Right->setObjectName("pB_Character_Right");

        gridLayout_5->addWidget(pB_Character_Right, 1, 2, 1, 1);

        m_stackedWidget_Options = new QStackedWidget(frame);
        m_stackedWidget_Options->setObjectName("m_stackedWidget_Options");
        page_attack = new QWidget();
        page_attack->setObjectName("page_attack");
        gridLayout_7 = new QGridLayout(page_attack);
        gridLayout_7->setObjectName("gridLayout_7");
        m_pB_BaseAttack = new QPushButton(page_attack);
        m_pB_BaseAttack->setObjectName("m_pB_BaseAttack");

        gridLayout_7->addWidget(m_pB_BaseAttack, 0, 0, 1, 1);

        m_stackedWidget_Options->addWidget(page_attack);
        page_Skills = new QWidget();
        page_Skills->setObjectName("page_Skills");
        gridLayout_8 = new QGridLayout(page_Skills);
        gridLayout_8->setObjectName("gridLayout_8");
        m_pB_Skill1 = new HoveringPushButton(page_Skills);
        m_pB_Skill1->setObjectName("m_pB_Skill1");
        m_pB_Skill1->setMinimumSize(QSize(0, 40));

        gridLayout_8->addWidget(m_pB_Skill1, 0, 0, 1, 1);

        m_pB_Skill2 = new HoveringPushButton(page_Skills);
        m_pB_Skill2->setObjectName("m_pB_Skill2");
        m_pB_Skill2->setMinimumSize(QSize(0, 40));

        gridLayout_8->addWidget(m_pB_Skill2, 0, 1, 1, 1);

        m_pB_Skill3 = new HoveringPushButton(page_Skills);
        m_pB_Skill3->setObjectName("m_pB_Skill3");
        m_pB_Skill3->setMinimumSize(QSize(0, 40));

        gridLayout_8->addWidget(m_pB_Skill3, 1, 0, 1, 1);

        m_pB_Ult = new HoveringPushButton(page_Skills);
        m_pB_Ult->setObjectName("m_pB_Ult");
        m_pB_Ult->setMinimumSize(QSize(0, 40));

        gridLayout_8->addWidget(m_pB_Ult, 1, 1, 1, 1);

        m_stackedWidget_Options->addWidget(page_Skills);
        page_Inventory = new QWidget();
        page_Inventory->setObjectName("page_Inventory");
        m_stackedWidget_Options->addWidget(page_Inventory);

        gridLayout_5->addWidget(m_stackedWidget_Options, 2, 1, 3, 2);

        pB_Inventory = new QPushButton(frame);
        pB_Inventory->setObjectName("pB_Inventory");
        pB_Inventory->setMinimumSize(QSize(120, 35));

        gridLayout_5->addWidget(pB_Inventory, 4, 0, 1, 1);

        pB_Character_Left = new QPushButton(frame);
        pB_Character_Left->setObjectName("pB_Character_Left");

        gridLayout_5->addWidget(pB_Character_Left, 1, 1, 1, 1);

        pB_Skill = new QPushButton(frame);
        pB_Skill->setObjectName("pB_Skill");
        pB_Skill->setMinimumSize(QSize(120, 35));

        gridLayout_5->addWidget(pB_Skill, 3, 0, 1, 1);

        Label_CharacterName = new ClickableLabel(frame);
        Label_CharacterName->setObjectName("Label_CharacterName");
        Label_CharacterName->setFont(font);

        gridLayout_5->addWidget(Label_CharacterName, 1, 0, 1, 1);


        gridLayout_4->addWidget(frame, 4, 0, 1, 4);

        frame_3 = new QFrame(page_Game);
        frame_3->setObjectName("frame_3");
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_10 = new QGridLayout(frame_3);
        gridLayout_10->setObjectName("gridLayout_10");
        Character05 = new ClickableLabel(frame_3);
        Character05->setObjectName("Character05");
        sizePolicy1.setHeightForWidth(Character05->sizePolicy().hasHeightForWidth());
        Character05->setSizePolicy(sizePolicy1);
        Character05->setMinimumSize(QSize(150, 200));
        Character05->setMaximumSize(QSize(16777215, 16777215));
        Character05->setFont(font4);
        Character05->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout_10->addWidget(Character05, 0, 2, 1, 1);

        Character06 = new ClickableLabel(frame_3);
        Character06->setObjectName("Character06");
        sizePolicy1.setHeightForWidth(Character06->sizePolicy().hasHeightForWidth());
        Character06->setSizePolicy(sizePolicy1);
        Character06->setMinimumSize(QSize(150, 200));
        Character06->setMaximumSize(QSize(16777215, 16777215));
        Character06->setFont(font4);
        Character06->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout_10->addWidget(Character06, 0, 3, 1, 1);

        Character04 = new ClickableLabel(frame_3);
        Character04->setObjectName("Character04");
        sizePolicy1.setHeightForWidth(Character04->sizePolicy().hasHeightForWidth());
        Character04->setSizePolicy(sizePolicy1);
        Character04->setMinimumSize(QSize(150, 200));
        Character04->setMaximumSize(QSize(16777215, 16777215));
        Character04->setFont(font4);
        Character04->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout_10->addWidget(Character04, 0, 0, 1, 1);

        Character04_Stats = new QLabel(frame_3);
        Character04_Stats->setObjectName("Character04_Stats");
        Character04_Stats->setFont(font4);

        gridLayout_10->addWidget(Character04_Stats, 1, 0, 1, 1);

        Character06_Stats = new QLabel(frame_3);
        Character06_Stats->setObjectName("Character06_Stats");
        Character06_Stats->setFont(font4);

        gridLayout_10->addWidget(Character06_Stats, 1, 3, 1, 1);

        Character05_Stats = new QLabel(frame_3);
        Character05_Stats->setObjectName("Character05_Stats");
        Character05_Stats->setFont(font4);

        gridLayout_10->addWidget(Character05_Stats, 1, 2, 1, 1);


        gridLayout_4->addWidget(frame_3, 3, 2, 1, 2, Qt::AlignTop);

        m_stackedWidget->addWidget(page_Game);

        gridLayout_2->addWidget(m_stackedWidget, 0, 1, 1, 1);

        QtGrandOrder->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QtGrandOrder);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 967, 21));
        QtGrandOrder->setMenuBar(menubar);
        statusbar = new QStatusBar(QtGrandOrder);
        statusbar->setObjectName("statusbar");
        QtGrandOrder->setStatusBar(statusbar);

        retranslateUi(QtGrandOrder);

        m_stackedWidget->setCurrentIndex(2);
        m_stackedWidget_Options->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(QtGrandOrder);
    } // setupUi

    void retranslateUi(QMainWindow *QtGrandOrder)
    {
        QtGrandOrder->setWindowTitle(QCoreApplication::translate("QtGrandOrder", "QtGrandOrder", nullptr));
        label->setText(QCoreApplication::translate("QtGrandOrder", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\270\320\274\321\217:", nullptr));
        m_pB_Connect->setText(QCoreApplication::translate("QtGrandOrder", "Connect", nullptr));
        Gosling->setText(QCoreApplication::translate("QtGrandOrder", "\320\240\320\260\320\271\320\260\320\275 \320\223\320\276\321\201\320\273\320\270\320\275\320\263", nullptr));
        Dante->setText(QCoreApplication::translate("QtGrandOrder", "Dante", nullptr));
        NecoArc->setText(QCoreApplication::translate("QtGrandOrder", "NecoArc", nullptr));
        Okabe->setText(QCoreApplication::translate("QtGrandOrder", "\320\236\320\272\320\260\320\261\320\265", nullptr));
        Uzya->setText(QCoreApplication::translate("QtGrandOrder", "\320\256\320\267\321\217", nullptr));
        Cris->setText(QCoreApplication::translate("QtGrandOrder", "\320\232\321\200\320\270\321\201", nullptr));
        m_label->setText(QCoreApplication::translate("QtGrandOrder", "\320\222\321\213\320\261\320\276\321\200 \320\277\320\265\321\200\321\201\320\276\320\275\320\260\320\266\320\260", nullptr));
        groupBox->setTitle(QString());
        Label_TurnsCount->setText(QCoreApplication::translate("QtGrandOrder", "1", nullptr));
        OpponentLabel->setText(QCoreApplication::translate("QtGrandOrder", "Player 2", nullptr));
        Label_Turn->setText(QCoreApplication::translate("QtGrandOrder", "\320\245\320\276\320\264:", nullptr));
        CurrentPlayerLabel->setText(QCoreApplication::translate("QtGrandOrder", "Player 1", nullptr));
        m_Label_INFO->setText(QCoreApplication::translate("QtGrandOrder", "INFO", nullptr));
        Character01_Stats->setText(QCoreApplication::translate("QtGrandOrder", "<html><head/><body><p>HP</p><p>MP</p></body></html>", nullptr));
        Character02_Stats->setText(QCoreApplication::translate("QtGrandOrder", "TextLabel", nullptr));
        Character03_Stats->setText(QCoreApplication::translate("QtGrandOrder", "TextLabel", nullptr));
        pB_Attack->setText(QCoreApplication::translate("QtGrandOrder", "\320\220\321\202\320\260\320\272\320\260", nullptr));
        pB_Character_Right->setText(QCoreApplication::translate("QtGrandOrder", "-->", nullptr));
        m_pB_BaseAttack->setText(QCoreApplication::translate("QtGrandOrder", "\320\224\320\260\321\202\321\214 \320\277\320\270\320\267\320\264\321\213", nullptr));
        m_pB_Skill1->setText(QCoreApplication::translate("QtGrandOrder", "Skill1", nullptr));
        m_pB_Skill2->setText(QCoreApplication::translate("QtGrandOrder", "Skill2", nullptr));
        m_pB_Skill3->setText(QCoreApplication::translate("QtGrandOrder", "Skill3", nullptr));
        m_pB_Ult->setText(QCoreApplication::translate("QtGrandOrder", "ulti", nullptr));
        pB_Inventory->setText(QCoreApplication::translate("QtGrandOrder", "\320\230\320\275\320\262\320\265\320\275\321\202\320\260\321\200\321\214", nullptr));
        pB_Character_Left->setText(QCoreApplication::translate("QtGrandOrder", "<--", nullptr));
        pB_Skill->setText(QCoreApplication::translate("QtGrandOrder", "\320\235\320\260\320\262\321\213\320\272\320\270", nullptr));
        Label_CharacterName->setText(QCoreApplication::translate("QtGrandOrder", "CharacterName", nullptr));
        Character04_Stats->setText(QCoreApplication::translate("QtGrandOrder", "TextLabel", nullptr));
        Character06_Stats->setText(QCoreApplication::translate("QtGrandOrder", "TextLabel", nullptr));
        Character05_Stats->setText(QCoreApplication::translate("QtGrandOrder", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGrandOrder: public Ui_QtGrandOrder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGRANDORDER_H
