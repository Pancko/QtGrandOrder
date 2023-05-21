QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../QtGrandOrder/character.cpp \
        ../QtGrandOrder/effect.cpp \
        ../QtGrandOrder/player.cpp \
        ../QtGrandOrder/skill.cpp \
        main.cpp \
        server.cpp \
        session.cpp



HEADERS += \
    ../QtGrandOrder/character.h \
    ../QtGrandOrder/effect.h \
    ../QtGrandOrder/player.h \
    ../QtGrandOrder/skill.h \
    server.h \
    session.h

FORMS += \
    server.ui

    # Default rules for deployment.
    qnx: target.path = /tmp/$${TARGET}/bin
    else: unix:!android: target.path = /opt/$${TARGET}/bin
    !isEmpty(target.path): INSTALLS += target
