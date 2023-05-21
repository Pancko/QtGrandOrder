
#include "player.h"

Player::Player(QObject *parent)
    : QObject{parent}
{

}

Player::Player(const Player &playerData)
{
    PlayerName = playerData.PlayerName;
    Status = playerData.Status;
    GameID = playerData.GameID;
    CharacterList = playerData.CharacterList;
}

Player Player::operator =(const Player &playerData)
{
    PlayerName = playerData.PlayerName;
    Status = playerData.Status;
    GameID = playerData.GameID;
    CharacterList = playerData.CharacterList;

    return *this;
}


QDataStream & operator >> (QDataStream & in, Player & player)
{
    in >> player.PlayerName;
    in >> player.CharacterList;
    in >> player.GameID;
    in >> player.Status;

    return in;
}


QDataStream & operator << (QDataStream & out, const Player & player)
{
    out << player.PlayerName;
    out << player.CharacterList;
    out << player.GameID;
    out << player.Status;
    //qDebug() << "data sent";

    return out;
}


