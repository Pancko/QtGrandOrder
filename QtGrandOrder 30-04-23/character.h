
#ifndef CHARACTER_H
#define CHARACTER_H


#include <QObject>
#include "skill.h"


class Character : public QObject
{
    Q_OBJECT

public:
    Character(const QJsonObject &jsonData);

public:
    QString CharacterName;
    int Speed;
    int MaxHP;
    int MaxMP;
    int EnergyCost;
    int BaseAttackDamage;

    Skill *CharacterSkills[3];
    QVector<Effect> Effects;

    int HP;
    int MP;
    int Energy;

public:
    explicit Character(QObject *parent = nullptr);

public:

    void DoDamage(Character *Target);
    void takeDamage(int damageTaken);
    void UseSkill(int SkillNumber, Character *Target);
    void ApplyEffect(Effect *effect);
    void DeathTriggered();

public:
    friend QDataStream & operator >> (QDataStream & in, Character & character);
    friend QDataStream & operator << (QDataStream & out, Character & character);

signals:

};

#endif // CHARACTER_H
