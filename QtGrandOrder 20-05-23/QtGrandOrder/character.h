
#ifndef CHARACTER_H
#define CHARACTER_H


#include <QObject>
#include "skill.h"


class Character : public QObject
{
    Q_OBJECT

public:
    Character(const QJsonObject &jsonData);
    Character(const Character &obj);

public:
    QString CharacterName;
    int MaxHP;
    int MaxMP;
    int BaseMPRegen;
    int Defence;
    int EnergyCost;
    int BaseAttackDamage;

    QStringList EffectNames{"DMG_UP", "DMG_DOWN", "DEF_UP", "DEF_DOWN", "STUN", "HP_REGEN", "HP_VAMP",
        "MP_REGEN", "MP_VAMP", "INVUL+BLOCK", "MP_REGEN+", "DEMAIL", "TRACEBACK", "RANDOMDEBUFF", "RANDOMSTATVAMP", "RANDOMSTATVAMPTARGET"};

    QStringList PossibleStats = {"HP", "MP", "BaseMPRegen", "Defence", "BaseAttackDamage"};
    int Stat = rand() % 6;

    Skill CharacterSkills[3];
    int SkillsCDStart[3];

    QVector<Effect> Effects;
    QVector<int> EffectsTurn;

    int HP;
    int MP;
    int Energy;

public:
    explicit Character(QObject *parent = nullptr);

public:

    void takeDamage(int damageTaken);
    void UseSkill(int SkillNumber, Character *Target);
    void ApplyEffect(Effect *effect, Character *Target);
    void RemoveEffect(int pos, Character *Target);
    void VampiricEffect(Character *Target, QString Stat, int Magnitude);
    void clear();

    Character operator = (const Character &obj);

public:
    friend QDataStream & operator >> (QDataStream & in, Character & character);
    friend QDataStream & operator << (QDataStream & out, const Character & character);

signals:

};

#endif // CHARACTER_H
