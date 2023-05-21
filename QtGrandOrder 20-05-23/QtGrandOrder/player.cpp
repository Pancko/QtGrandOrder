
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
    CurrentTurn = playerData.CurrentTurn;
    CharacterList = playerData.CharacterList;
}

void Player::clear()
{
    PlayerName = "";
    CharacterList.clear();
    GameID = 0;
    CurrentTurn = 1;
    Status = "";
}

Player Player::operator =(const Player &playerData)
{
    PlayerName = playerData.PlayerName;
    Status = playerData.Status;
    GameID = playerData.GameID;
    CurrentTurn = playerData.CurrentTurn;
    CharacterList = playerData.CharacterList;

    return *this;
}


QDataStream & operator >> (QDataStream & in, Player & player)
{
    in >> player.PlayerName;
    in >> player.CharacterList;
    in >> player.GameID;
    in >> player.CurrentTurn;
    in >> player.Status;

    return in;
}


QDataStream & operator << (QDataStream & out, const Player & player)
{
    out << player.PlayerName;
    out << player.CharacterList;
    out << player.GameID;
    out << player.CurrentTurn;
    out << player.Status;

    return out;
}


