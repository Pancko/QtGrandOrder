
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
    Player Player1;
    Player Player2;
};

#endif // SESSION_H
