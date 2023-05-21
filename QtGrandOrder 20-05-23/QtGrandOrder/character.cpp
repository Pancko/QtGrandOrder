
#include "character.h"

Character::Character(const QJsonObject &jsonData)
{
    CharacterName = jsonData["Name"].toString();
    MaxHP = jsonData["MaxHP"].toInt();
    MaxMP = jsonData["MaxMP"].toInt();
    BaseMPRegen = jsonData["BaseMPRegen"].toInt();
    Defence = jsonData["Defence"].toInt();
    EnergyCost = jsonData["EnergyCost"].toInt();
    BaseAttackDamage = jsonData["BaseAttackDamage"].toInt();

    QJsonObject Skills = jsonData["Skills"].toObject();

    for (int i = 0; i < 3; i++)
    {
        QJsonObject SkillObj = Skills[QString("Skill " + QString::number(i + 1))].toObject();
        QVector<Effect> CurrentEffects;
        for (int j = 1;; j++)
        {
            if(SkillObj.contains("SkillEffect " + QString::number(j)))
            {
                QJsonObject EffectObj = SkillObj["SkillEffect " + QString::number(j)].toObject();
                Effect CurrentEffect(EffectObj["EffectName"].toString(), EffectObj["Magnitude"].toInt(), EffectObj["Turns"].toInt());
                CurrentEffects.push_back(CurrentEffect);
            }
            else break;
        }
        Skill CurrentSkill(SkillObj["SkillName"].toString(), SkillObj["SkillIcon"].toString(),
                           SkillObj["SkillDescription"].toString(),SkillObj["SkillTarget"].toString(),
                           CurrentEffects, SkillObj["Cooldown"].toInt(), SkillObj["MPCost"].toInt());

        CharacterSkills[i] = CurrentSkill;
        SkillsCDStart[i] = 0;
    }

    HP = MaxHP;
    MP = MaxMP;
    Energy = 0;
}

Character::Character(const Character &obj) : QObject()
{
    CharacterName = obj.CharacterName;
    MaxHP = obj.MaxHP;
    MaxMP = obj.MaxMP;
    Defence = obj.Defence;
    EnergyCost = obj.EnergyCost;
    BaseAttackDamage = obj.BaseAttackDamage;
    BaseMPRegen = obj.BaseMPRegen;

    for (int i = 0; i < 3; i++)
    {
        CharacterSkills[i] = obj.CharacterSkills[i];
        SkillsCDStart[i] = obj.SkillsCDStart[i];
    }
    Effects.clear();
    EffectsTurn.clear();
    for (int i = 0; i < obj.Effects.size(); i++)
    {
        Effects.push_back(obj.Effects[i]);
        EffectsTurn.push_back(obj.EffectsTurn[i]);
    }

    HP = obj.HP;
    MP = obj.MP;
    Energy = obj.Energy;
}



Character::Character(QObject *parent)
    : QObject{parent}
{


}

void Character::takeDamage(int damageTaken)
{
    if(HP - damageTaken + Defence > 0)
    {
        HP -= damageTaken + Defence;
    }
    else
    {
        HP = 0;
    }
}

void Character::UseSkill(int SkillNumber, Character *Target)
{
    for (int i = 0; i < CharacterSkills[SkillNumber].SkillEffects.size(); i++)
    {
        Target->ApplyEffect(&CharacterSkills[SkillNumber].SkillEffects[i], Target);
    }
}

void Character::ApplyEffect(Effect *effect, Character *Target)
{
    Effects.push_back(*effect);
    EffectsTurn.push_back(effect->Turns);
    switch(EffectNames.indexOf(effect->EffectName))
    {
    case 0: //DMG_UP
    {
        BaseAttackDamage += (BaseAttackDamage * effect->Magnitude)/100;
        break;
    }
    case 1: //DMG_DOWN
    {
        BaseAttackDamage -= (BaseAttackDamage * effect->Magnitude)/100;
        break;
    }
    case 2: //DEF_UP
    {
        Defence += (Defence * effect->Magnitude)/100;
        break;
    }
    case 3: //DEF_DOWN
    {
        Defence -= (Defence * effect->Magnitude)/100;
        break;
    }
    case 4: //STUN
    {
        break;
    }
    case 5: //HP_REGEN
    {
        HP += (MaxHP * effect->Magnitude)/100;
        break;
    }
    case 6: //HP_VAMP
    {
        HP -= (MaxHP * effect->Magnitude)/100;
        break;
    }
    case 7: //MP_REGEN
    {
        MP += (MaxMP * effect->Magnitude)/100;
        break;
    }
    case 8: //MP_VAMP
    {
        MP -= (MaxMP * effect->Magnitude)/100;
        break;
    }
    case 9: //INVUL+BLOCK
    {
        break;
    }
    case 10: //MP_REGEN+
    {
        MP += (MaxMP * effect->Magnitude)/100;
        break;
    }
    case 11: //DEMAIL
    {
        break;
    }
    case 12: //TRACEBACK
    {
        for (int i = 0; i < Effects.size(); i++)
        {
            switch(EffectNames.indexOf(Effects[i].EffectName))
            {
            case 0: //DMG_UP
            {
                Effects[i].Turns++;
                break;
            }
            case 1: //DMG_DOWN
            {
                Effects[i].Turns--;
                break;
            }
            case 2: //DEF_UP
            {
                Effects[i].Turns++;
                break;
            }
            case 3: //DEF_DOWN
            {
                Effects[i].Turns--;
                break;
            }
            case 5: //HP_REGEN
            {
                Effects[i].Turns++;
                break;
            }
            case 7: //MP_REGEN
            {
                Effects[i].Turns++;
                break;
            }
            case 10: //MP_REGEN+
            {
                Effects[i].Turns++;
                break;
            }
            }
        }
        break;
    }
    case 13: //RANDOMDEBUFF
    {
        break;
    }
    case 14: //RANDOMSTATVAMP
    {
        switch(Stat)
        {
        case 0: //HP
        {
            HP += (Target->MaxHP * effect->Magnitude)/100;
            break;
        }
        case 1: //MP
        {
            MP += (Target->MaxMP * effect->Magnitude)/100;
            break;
        }
        case 2: //BaseMPRegen
        {
            BaseMPRegen += (Target->BaseMPRegen * effect->Magnitude)/100;
            break;
        }
        case 3: //Defence
        {
            Defence += (Target->Defence * effect->Magnitude)/100;
            break;
        }
        case 4: //BaseAttackDamage
        {
            BaseAttackDamage += (Target->BaseAttackDamage * effect->Magnitude)/100;
            break;
        }
        }
        break;
    }
    case 15: //RANDOMSTATVAMPTARGET
    {
        switch(Stat)
        {
        case 0: //HP
        {
            HP -= (Target->MaxHP * effect->Magnitude)/100;
            break;
        }
        case 1: //MP
        {
            MP -= (Target->MaxMP * effect->Magnitude)/100;
            break;
        }
        case 2: //BaseMPRegen
        {
            BaseMPRegen -= (Target->BaseMPRegen * effect->Magnitude)/100;
            break;
        }
        case 3: //Defence
        {
            Defence -= (Target->Defence * effect->Magnitude)/100;
            break;
        }
        case 4: //BaseAttackDamage
        {
            BaseAttackDamage -= (Target->BaseAttackDamage * effect->Magnitude)/100;
            break;
        }
        }
        break;
    }
    }
}

void Character::RemoveEffect(int pos, Character *Target)
{
    qDebug() << "Удаляю эффект";
    switch(EffectNames.indexOf(Effects[pos].EffectName))
    {
    case 0: //DMG_UP
    {
        BaseAttackDamage -= (BaseAttackDamage * Effects[pos].Magnitude)/100;
        break;
    }
    case 1: //DMG_DOWN
    {
        BaseAttackDamage += (BaseAttackDamage * Effects[pos].Magnitude)/100;
        break;
    }
    case 2: //DEF_UP
    {
        Defence -= (Defence * Effects[pos].Magnitude)/100;
        break;
    }
    case 3: //DEF_DOWN
    {
        Defence += (Defence * Effects[pos].Magnitude)/100;
        break;
    }
    case 9: //INVUL+BLOCK
    {
        break;
    }
    case 11: //DEMAIL
    {
        break;
    }
    case 13: //RANDOMDEBUFF
    {
        break;
    }
    case 14: //RANDOMSTATVAMP
    {
        switch(Stat)
        {
        case 0: //HP
        {
            HP -= (Target->MaxHP * Effects[pos].Magnitude)/100;
            break;
        }
        case 1: //MP
        {
            MP -= (Target->MaxMP * Effects[pos].Magnitude)/100;
            break;
        }
        case 2: //BaseMPRegen
        {
            BaseMPRegen -= (Target->BaseMPRegen * Effects[pos].Magnitude)/100;
            break;
        }
        case 3: //Defence
        {
            Defence -= (Target->Defence * Effects[pos].Magnitude)/100;
            break;
        }
        case 4: //BaseAttackDamage
        {
            BaseAttackDamage -= (Target->BaseAttackDamage * Effects[pos].Magnitude)/100;
            break;
        }
        }
        break;
    }
    case 15: //RANDOMSTATVAMPTARGET
    {
        switch(Stat)
        {
        case 0: //HP
        {
            HP += (Target->MaxHP * Effects[pos].Magnitude)/100;
            break;
        }
        case 1: //MP
        {
            MP += (Target->MaxMP * Effects[pos].Magnitude)/100;
            break;
        }
        case 2: //BaseMPRegen
        {
            BaseMPRegen += (Target->BaseMPRegen * Effects[pos].Magnitude)/100;
            break;
        }
        case 3: //Defence
        {
            Defence += (Target->Defence * Effects[pos].Magnitude)/100;
            break;
        }
        case 4: //BaseAttackDamage
        {
            BaseAttackDamage += (Target->BaseAttackDamage * Effects[pos].Magnitude)/100;
            break;
        }
        }
        break;
    }
    }
    qDebug() << "Effect list size = " << Effects.size();
    Effects.remove(pos);
    Effects.squeeze();
    EffectsTurn.remove(pos);
    EffectsTurn.squeeze();
    qDebug() << "Effect list size = " << Effects.size();
}

void Character::VampiricEffect(Character *Target, QString Stat, int Magnitude)
{
    QStringList PossibleStats = {"HP", "MP", "BaseMPRegen", "Defence", "BaseAttackDamage"};
    switch(PossibleStats.indexOf(Stat))
    {
    case 0: //HP
    {
        HP += (Target->MaxHP * Magnitude)/100;
        break;
    }
    case 1: //MP
    {
        MP += (Target->MaxMP * Magnitude)/100;
        break;
    }
    case 2: //BaseMPRegen
    {
        BaseMPRegen += (Target->BaseMPRegen * Magnitude)/100;
        break;
    }
    case 3: //Defence
    {
        Defence += (Target->Defence * Magnitude)/100;
        break;
    }
    case 4: //BaseAttackDamage
    {
        BaseAttackDamage += (Target->BaseAttackDamage * Magnitude)/100;
        break;
    }
    }
}

void Character::clear()
{
    CharacterName = "";
    MaxHP = 0;
    MaxMP = 0;
    BaseMPRegen = 0;
    Defence = 0;
    EnergyCost = 0;
    BaseAttackDamage = 0;

    CharacterSkills[0].clear();
    CharacterSkills[1].clear();
    CharacterSkills[2].clear();

    SkillsCDStart[0] = 0;
    SkillsCDStart[1] = 0;
    SkillsCDStart[2] = 0;

    Effects.clear();
    EffectsTurn.clear();

    HP = 0;
    MP = 0;
    Energy = 0;
}

Character Character::operator =(const Character &obj)
{
    CharacterName = obj.CharacterName;
    MaxHP = obj.MaxHP;
    MaxMP = obj.MaxMP;
    BaseMPRegen = obj.BaseMPRegen;
    Defence = obj.Defence;
    EnergyCost = obj.EnergyCost;
    BaseAttackDamage = obj.BaseAttackDamage;

    for (int i = 0; i < 3; i++)
    {
        CharacterSkills[i] = obj.CharacterSkills[i];
        SkillsCDStart[i] = obj.SkillsCDStart[i];
    }
    Effects.clear();
    EffectsTurn.clear();
    for (int i = 0; i < obj.Effects.size(); i++)
    {
        Effects.push_back(obj.Effects[i]);
        EffectsTurn.push_back(obj.EffectsTurn[i]);
    }

    HP = obj.HP;
    MP = obj.MP;
    Energy = obj.Energy;

    return *this;
}

QDataStream & operator >> (QDataStream & in, Character & character)
{
    in >> character.CharacterName;
    in >> character.MaxHP;
    in >> character.MaxMP;
    in >> character.BaseMPRegen;
    in >> character.Defence;
    in >> character.EnergyCost;
    in >> character.BaseAttackDamage;

    in >> character.HP;
    in >> character.MP;
    in >> character.Energy;

    for (int i = 0; i < 3; i++)
    {
        in >> character.CharacterSkills[i];
        in >> character.SkillsCDStart[i];
    }
    in >> character.Effects;
    in >> character.EffectsTurn;

    return in;
}

QDataStream & operator << (QDataStream & out, const Character & character)
{
    out << character.CharacterName;
    out << character.MaxHP;
    out << character.MaxMP;
    out << character.BaseMPRegen;
    out << character.Defence;
    out << character.EnergyCost;
    out << character.BaseAttackDamage;

    out << character.HP;
    out << character.MP;
    out << character.Energy;

    for (int i = 0; i < 3; i++)
    {
        out << character.CharacterSkills[i];
        out << character.SkillsCDStart[i];
    }
    out << character.Effects;
    out << character.EffectsTurn;

    return out;
}
