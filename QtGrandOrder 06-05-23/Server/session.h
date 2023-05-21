
#ifndef SESSION_H
#define SESSION_H

#include "..\QtGrandOrder\player.h"

class Session
{
public:
    Session();
public:
    qintptr Player1socketDescriptor = 0;
    qintptr Player2socketDescriptor = 0;
    int SessionID = 0;
    int TurnCount = 1;
    Player Player1;
    Player Player2;

    QString GameStatus;

    void clear();
};

#endif // SESSION_H
