
#include "player.h"

Player::Player(QObject *parent)
    : QObject{parent}
{

}


QDataStream & operator << (QDataStream & in, Player & player)
{
    in >> player.PlayerName;
    for(int i = 0; i < 3; i++)
    {
        in >> *player.CharacterList[i];
    }
    return in;
}


QDataStream & operator >> (QDataStream & out, Player & player)
{
    out << player.PlayerName;
    for(int i = 0; i < 3; i++)
    {
        out << *player.CharacterList[i];
    }
    return out;
}


