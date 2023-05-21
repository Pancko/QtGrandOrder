
#include "effect.h"

Effect::Effect()
{

}

Effect::Effect(QString Name, int _Turns)
{
    EffectName = Name;
    Turns = _Turns;
}

QDataStream & operator >> (QDataStream & in, Effect & effect)
{
    in >> effect.EffectName >> effect.Turns;
    return in;
}

QDataStream & operator << (QDataStream & out, Effect & effect)
{
    out << effect.EffectName << effect.Turns;
    return out;
}
