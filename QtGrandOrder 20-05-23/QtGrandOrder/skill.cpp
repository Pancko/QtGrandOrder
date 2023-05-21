
#include "skill.h"

Skill::Skill()
{

}

Skill::Skill(QString Name, QString Icon, QString Description, QString Target, QVector<Effect> Effects, int cooldown, int _MPCost)
{
    SkillName = Name;
    SkillIcon = Icon;
    SkillDescription = Description;
    SkillTarget = Target;
    SkillEffects = Effects;
    Cooldown = cooldown;
    MPCost = _MPCost;
}

void Skill::clear()
{
    SkillName = "";
    SkillIcon = "";
    SkillDescription = "";
    SkillTarget = "";
    SkillEffects.clear();
    Cooldown = 0;
    MPCost = 0;
}

QDataStream & operator >> (QDataStream & in, Skill & skill)
{
    in >> skill.SkillName >> skill.SkillIcon >> skill.SkillDescription >> skill.SkillTarget >> skill.SkillEffects >> skill.Cooldown >> skill.MPCost;

    return in;
}

QDataStream & operator << (QDataStream & out, const Skill & skill)
{
    out << skill.SkillName << skill.SkillIcon << skill.SkillDescription << skill.SkillTarget << skill.SkillEffects << skill.Cooldown << skill.MPCost;

    return out;
}

