
#include "player.h"

Player::Player(QObject *parent)
    : QObject{parent}
{

}


QDataStream & operator >> (QDataStream & in, Player & player)
{
    in >> player.PlayerName;
    qDebug() << "Name pushed " << player.PlayerName;

    in >> player.CharacterList;
    qDebug() << "vector size =" << player.CharacterList.size();

    return in;
}


QDataStream & operator << (QDataStream & out, const Player & player)
{
    out << player.PlayerName;
    qDebug() << "Sent name " << player.PlayerName;
    out << player.CharacterList;

    return out;
}


