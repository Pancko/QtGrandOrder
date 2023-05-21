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
    QLabel *Character04;
    QLabel *Character02;
    QFrame *frame;
    QGridLayout *gridLayout_5;
    QLabel *Label_CharacterName;
    QPushButton *pB_Attack;
    QStackedWidget *stackedWidget;
    QWidget *page_attack;
    QWidget *page_Skills;
    QWidget *page_Inventory;
    QPushButton *pB_Character_Left;
    QPushButton *pB_Character_Right;
    QPushButton *pB_Skill;
    QPushButton *pB_Inventory;
    QLabel *Character05;
    QLabel *Character06;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_6;
    QLabel *Label_TurnsCount;
    QLabel *Label_Turn;
    QSpacerItem *horizontalSpacer_3;
    QLabel *Character01;
    QLabel *Character03;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QtGrandOrder)
    {
        if (QtGrandOrder->objectName().isEmpty())
            QtGrandOrder->setObjectName("QtGrandOrder");
        QtGrandOrder->resize(960, 540);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QtGrandOrder->sizePolicy().hasHeightForWidth());
        QtGrandOrder->setSizePolicy(sizePolicy);
        QtGrandOrder->setMinimumSize(QSize(960, 540));
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
        Character04 = new QLabel(page_Game);
        Character04->setObjectName("Character04");
        QFont font3;
        font3.setBold(true);
        Character04->setFont(font3);
        Character04->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout_4->addWidget(Character04, 1, 3, 1, 1);

        Character02 = new QLabel(page_Game);
        Character02->setObjectName("Character02");
        Character02->setMinimumSize(QSize(0, 0));
        Character02->setFont(font3);
        Character02->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout_4->addWidget(Character02, 1, 1, 1, 1);

        frame = new QFrame(page_Game);
        frame->setObjectName("frame");
        frame->setMaximumSize(QSize(16777215, 180));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame);
        gridLayout_5->setObjectName("gridLayout_5");
        Label_CharacterName = new QLabel(frame);
        Label_CharacterName->setObjectName("Label_CharacterName");
        Label_CharacterName->setFont(font);

        gridLayout_5->addWidget(Label_CharacterName, 1, 0, 1, 1);

        pB_Attack = new QPushButton(frame);
        pB_Attack->setObjectName("pB_Attack");
        pB_Attack->setMinimumSize(QSize(120, 35));

        gridLayout_5->addWidget(pB_Attack, 2, 0, 1, 1);

        stackedWidget = new QStackedWidget(frame);
        stackedWidget->setObjectName("stackedWidget");
        page_attack = new QWidget();
        page_attack->setObjectName("page_attack");
        stackedWidget->addWidget(page_attack);
        page_Skills = new QWidget();
        page_Skills->setObjectName("page_Skills");
        stackedWidget->addWidget(page_Skills);
        page_Inventory = new QWidget();
        page_Inventory->setObjectName("page_Inventory");
        stackedWidget->addWidget(page_Inventory);

        gridLayout_5->addWidget(stackedWidget, 2, 1, 3, 2);

        pB_Character_Left = new QPushButton(frame);
        pB_Character_Left->setObjectName("pB_Character_Left");

        gridLayout_5->addWidget(pB_Character_Left, 1, 1, 1, 1);

        pB_Character_Right = new QPushButton(frame);
        pB_Character_Right->setObjectName("pB_Character_Right");

        gridLayout_5->addWidget(pB_Character_Right, 1, 2, 1, 1);

        pB_Skill = new QPushButton(frame);
        pB_Skill->setObjectName("pB_Skill");
        pB_Skill->setMinimumSize(QSize(120, 35));

        gridLayout_5->addWidget(pB_Skill, 3, 0, 1, 1);

        pB_Inventory = new QPushButton(frame);
        pB_Inventory->setObjectName("pB_Inventory");
        pB_Inventory->setMinimumSize(QSize(120, 35));

        gridLayout_5->addWidget(pB_Inventory, 4, 0, 1, 1);


        gridLayout_4->addWidget(frame, 2, 0, 1, 6);

        Character05 = new QLabel(page_Game);
        Character05->setObjectName("Character05");
        Character05->setFont(font3);
        Character05->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout_4->addWidget(Character05, 1, 4, 1, 1);

        Character06 = new QLabel(page_Game);
        Character06->setObjectName("Character06");
        Character06->setFont(font3);
        Character06->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout_4->addWidget(Character06, 1, 5, 1, 1);

        groupBox = new QGroupBox(page_Game);
        groupBox->setObjectName("groupBox");
        groupBox->setMaximumSize(QSize(16777215, 40));
        gridLayout_6 = new QGridLayout(groupBox);
        gridLayout_6->setObjectName("gridLayout_6");
        Label_TurnsCount = new QLabel(groupBox);
        Label_TurnsCount->setObjectName("Label_TurnsCount");
        Label_TurnsCount->setFont(font1);

        gridLayout_6->addWidget(Label_TurnsCount, 0, 1, 1, 1);

        Label_Turn = new QLabel(groupBox);
        Label_Turn->setObjectName("Label_Turn");
        Label_Turn->setFont(font1);

        gridLayout_6->addWidget(Label_Turn, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_3, 0, 2, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 6);

        Character01 = new QLabel(page_Game);
        Character01->setObjectName("Character01");
        Character01->setMinimumSize(QSize(0, 0));
        Character01->setFont(font3);
        Character01->setStyleSheet(QString::fromUtf8("QLabel{\n"
"border-image: url(F:/Qt_projs/QtGrandOrder/release/CharacterData/Neco Arc_Image.png) 0 0 0 0 stretch stretch;\n"
"}"));
        Character01->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout_4->addWidget(Character01, 1, 0, 1, 1);

        Character03 = new QLabel(page_Game);
        Character03->setObjectName("Character03");
        Character03->setMinimumSize(QSize(0, 0));
        Character03->setFont(font3);
        Character03->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout_4->addWidget(Character03, 1, 2, 1, 1);

        m_stackedWidget->addWidget(page_Game);

        gridLayout_2->addWidget(m_stackedWidget, 0, 0, 1, 1);

        QtGrandOrder->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QtGrandOrder);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 960, 22));
        QtGrandOrder->setMenuBar(menubar);
        statusbar = new QStatusBar(QtGrandOrder);
        statusbar->setObjectName("statusbar");
        QtGrandOrder->setStatusBar(statusbar);

        retranslateUi(QtGrandOrder);

        m_stackedWidget->setCurrentIndex(1);
        stackedWidget->setCurrentIndex(2);


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
        Character04->setText(QCoreApplication::translate("QtGrandOrder", "HP: 100/100", nullptr));
        Character02->setText(QCoreApplication::translate("QtGrandOrder", "HP: 100/100", nullptr));
        Label_CharacterName->setText(QCoreApplication::translate("QtGrandOrder", "CharacterName", nullptr));
        pB_Attack->setText(QCoreApplication::translate("QtGrandOrder", "\320\220\321\202\320\260\320\272\320\260", nullptr));
        pB_Character_Left->setText(QCoreApplication::translate("QtGrandOrder", "<--", nullptr));
        pB_Character_Right->setText(QCoreApplication::translate("QtGrandOrder", "-->", nullptr));
        pB_Skill->setText(QCoreApplication::translate("QtGrandOrder", "\320\235\320\260\320\262\321\213\320\272\320\270", nullptr));
        pB_Inventory->setText(QCoreApplication::translate("QtGrandOrder", "\320\230\320\275\320\262\320\265\320\275\321\202\320\260\321\200\321\214", nullptr));
        Character05->setText(QCoreApplication::translate("QtGrandOrder", "HP: 100/100", nullptr));
        Character06->setText(QCoreApplication::translate("QtGrandOrder", "HP: 100/100", nullptr));
        groupBox->setTitle(QString());
        Label_TurnsCount->setText(QCoreApplication::translate("QtGrandOrder", "0", nullptr));
        Label_Turn->setText(QCoreApplication::translate("QtGrandOrder", "\320\245\320\276\320\264:", nullptr));
        Character01->setText(QCoreApplication::translate("QtGrandOrder", "HP: 100/100", nullptr));
        Character03->setText(QCoreApplication::translate("QtGrandOrder", "HP: 100/100", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGrandOrder: public Ui_QtGrandOrder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGRANDORDER_H
