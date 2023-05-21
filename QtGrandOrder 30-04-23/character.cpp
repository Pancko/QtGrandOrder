
#include "character.h"

Character::Character(const QJsonObject &jsonData)
{
    CharacterName = jsonData["Name"].toString();
    Speed = jsonData["Speed"].toInt();
    MaxHP = jsonData["MaxHP"].toInt();
    MaxMP = jsonData["MaxMP"].toInt();
    EnergyCost = jsonData["EnergyCost"].toInt();
    BaseAttackDamage = jsonData["BaseAttackDamage"].toInt();

    for (int i = 0; i < 3; i++)
    {
        QJsonObject SkillObj = jsonData["Skill " + QString::number(i + 1)].toObject();
        QJsonObject EffectObj = SkillObj["SkillEffect"].toObject();

        Effect CurrentEffect(EffectObj["EffectName"].toString(), EffectObj["Turns"].toInt());

        Skill CurrentSkill(SkillObj["SkillName"].toString(), SkillObj["SkillIcon"].toString(),
                           SkillObj["SkillDescription"].toString(),SkillObj["SkillTarget"].toString(),
                           CurrentEffect, SkillObj["Cooldown"].toInt());

        CharacterSkills[i] = &CurrentSkill;
    }

    HP = MaxHP;
    MP = MaxMP;
    Energy = 0;

    /*
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
    */
}

Character::Character(QObject *parent)
    : QObject{parent}
{


}

void Character::DoDamage(Character *Target)
{
    Target->takeDamage(BaseAttackDamage);
}

void Character::takeDamage(int damageTaken)
{
    if(HP - damageTaken > 0){
        HP -=damageTaken;
    }
    else
    {
        HP = 0;
        DeathTriggered();
    }
}

void Character::UseSkill(int SkillNumber, Character *Target)
{
    Target->ApplyEffect(&CharacterSkills[SkillNumber]->SkillEffect);
    if(CharacterSkills[SkillNumber]->SkillEffect.Turns)
    {
        Effects.push_front(CharacterSkills[SkillNumber]->SkillEffect);
        //Block the skill button for a Cooldown
    }
}

void Character::ApplyEffect(Effect *effect)
{

}

void Character::DeathTriggered()
{

}

QDataStream & operator >> (QDataStream & in, Character & character)
{
    in >> character.CharacterName;
    in >> character.Speed;
    in >> character.MaxHP;
    in >> character.MaxMP;
    in >> character.EnergyCost;
    in >> character.BaseAttackDamage;

    in >> character.HP;
    in >> character.MP;
    in >> character.Energy;

    for (int i = 0; i < 3; i++)
    {
        in >> *character.CharacterSkills[i];
    }
    for (int i = 0; i < character.Effects.size(); i++)
    {
        in >> character.Effects[i];
    }

    return in;
}

QDataStream & operator << (QDataStream & out, Character & character)
{
    out << character.CharacterName;
    out << character.Speed;
    out << character.MaxHP;
    out << character.MaxMP;
    out << character.EnergyCost;
    out << character.BaseAttackDamage;

    out << character.HP;
    out << character.MP;
    out << character.Energy;

    for (int i = 0; i < 3; i++)
    {
        out << *character.CharacterSkills[i];
    }
    for (int i = 0; i < character.Effects.size(); i++)
    {
        out << character.Effects[i];
    }

    return out;
}
