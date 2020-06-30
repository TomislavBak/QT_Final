#include "country.h"

Country::Country(QString name,QString flag,QString prefix):mcountryName(name),mflagNumber(flag),mprefixNumber(prefix){}


QString Country::getName() const
{
    return mcountryName;
}

QString Country::getFlagNumber()const
{
    return mflagNumber;
}

QString Country::getPrefixNumber()const
{
    return mprefixNumber;
}


