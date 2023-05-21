
#ifndef SKILL_H
#define SKILL_H

#include <QObject>
#include "effect.h"


class Skill
{
public:
    Skill();

public:
    Skill(QString Name, QString Icon, QString Description, QString Target, QVector<Effect> Effects, int cooldown, int _MPCost);

public:
    QString SkillName;
    QString SkillIcon;
    QString SkillDescription;
    QString SkillTarget;
    QVector<Effect> SkillEffects;
    int Cooldown;
    int MPCost;

public:
    void CooldownUptime();
    void Use();
    void clear();

public:
    friend QDataStream & operator >> (QDataStream & in, Skill & skill);
    friend QDataStream & operator << (QDataStream & out, const Skill & skill);
};

#endif // SKILL_H
