
#include "session.h"

Session::Session()
{

}

void Session::clear()
{
    Player1socketDescriptor = 0;
    Player2socketDescriptor = 0;
    GameStatus = "";
    SessionID = 0;
    TurnCount = 1;
    Player1.clear();
    Player2.clear();
}

