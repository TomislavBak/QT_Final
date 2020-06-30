#ifndef COUNTRY_H
#define COUNTRY_H
#include<QString>


// Basic container class to store and access data with accessors.
//
class Country
{
public:
    Country(QString,QString,QString);
    QString getName()const;
    QString getFlagNumber()const;
    QString getPrefixNumber()const;


private:
    QString mcountryName;
    QString mflagNumber;
    QString mprefixNumber;

};

#endif // COUNTRY_H
