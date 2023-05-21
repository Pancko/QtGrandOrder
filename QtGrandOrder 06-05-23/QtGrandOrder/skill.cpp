
#include "skill.h"

Skill::Skill()
{

}

Skill::Skill(QString Name, QString Icon, QString Description, QString Target, Effect effect, int cooldown)
{
    SkillName = Name;
    SkillIcon = Icon;
    SkillDescription = Description;
    SkillTarget = Target;
    SkillEffect = effect;
    Cooldown = cooldown;
}

void Skill::clear()
{
    SkillName = "";
    SkillIcon = "";
    SkillDescription = "";
    SkillTarget = "";
    SkillEffect.clear();
    Cooldown = 0;
}

QDataStream & operator >> (QDataStream & in, Skill & skill)
{
    in >> skill.SkillName >> skill.SkillIcon >> skill.SkillDescription >> skill.SkillTarget >> skill.SkillEffect >> skill.Cooldown;

    return in;
}

QDataStream & operator << (QDataStream & out, const Skill & skill)
{
    out << skill.SkillName << skill.SkillIcon << skill.SkillDescription << skill.SkillTarget << skill.SkillEffect << skill.Cooldown;

    return out;
}

