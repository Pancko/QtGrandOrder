
#ifndef PLAYER_H
#define PLAYER_H


#include <QObject>
#include "character.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

    Player(const Player &playerData);
public:
    QString PlayerName;
    QVector<Character> CharacterList;

    QString Status;
    //Character *CharacterList[3];

signals:

public:
    Player operator = (const Player &playerData);
    friend QDataStream & operator >> (QDataStream & in, Player & player);
    friend QDataStream & operator << (QDataStream & out, const Player & player);
};

#endif // PLAYER_H
