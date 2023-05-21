
#ifndef EFFECT_H
#define EFFECT_H

#include <QObject>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>


class Effect
{
public:
    Effect();
    Effect(QString Name, int Turns);

public:
    QString EffectName;
    //bool IsInstant;
    int Turns;

public:
    void Apply();
    void Remove();

public:
    friend QDataStream & operator >> (QDataStream & in, Effect & effect);
    friend QDataStream & operator << (QDataStream & out, const Effect & effect);
};

#endif // EFFECT_H


/*
DamageAVhp
DamageAVmp
DamageAVep
RestoreAVhp
RestoreAVmp
RestoreAVep
IncreaseAVhp
IncreaseAVmp
*/
