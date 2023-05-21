
#include "effect.h"

Effect::Effect()
{

}

Effect::Effect(QString Name, int _Magnitude, int _Turns)
{
    EffectName = Name;
    Magnitude = _Magnitude;
    Turns = _Turns;
}

void Effect::clear()
{
    EffectName = "";
    Magnitude = 0;
    Turns = 0;
}

QDataStream & operator >> (QDataStream & in, Effect & effect)
{
    in >> effect.EffectName >> effect.Magnitude >> effect.Turns;
    return in;
}

QDataStream & operator << (QDataStream & out, Effect const & effect)
{
    out << effect.EffectName << effect.Magnitude << effect.Turns;
    return out;
}
