
#ifndef SKILL_H
#define SKILL_H

#include <QObject>
#include "effect.h"


class Skill
{
public:
    Skill();

public:
    Skill(QString Name, QString Icon, QString Description, QString Target, Effect effect, int cooldown);

public:
    QString SkillName;
    QString SkillIcon;
    QString SkillDescription;
    QString SkillTarget;
    Effect SkillEffect;
    int Cooldown;

public:
    void CooldownUptime();
    void Use();

public:
    friend QDataStream & operator >> (QDataStream & in, Skill & skill);
    friend QDataStream & operator << (QDataStream & out, Skill & skill);
};

#endif // SKILL_H
