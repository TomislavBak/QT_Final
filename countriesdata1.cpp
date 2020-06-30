#include "countriesdata.h"

CountriesData::CountriesData(QObject *parent)
    : QAbstractListModel(parent)
{
}

void CountriesData::addCountry(const Country &country)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_country << country;
    endInsertRows();
}

int CountriesData::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    Q_UNUSED(parent);
    return m_country.count();
}

QVariantMap CountriesData::get(int row)
{
    QHash<int,QByteArray> names = roleNames();
        QHashIterator<int, QByteArray> i(names);
        QVariantMap res;
        while (i.hasNext()) {
            i.next();
            QModelIndex idx = index(row, 0);
            QVariant data = idx.data(i.key());
            res[i.value()] = data;
            //cout << i.key() << ": " << i.value() << endl;
        }
        return res;
}


//***************************************************************



QVariant CountriesData::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_country.count())
        return QVariant();

    // FIXME: Implement me!
    const Country &country = m_country[index.row()];
    if (role == TypeRole)
        return country.name();
    else if (role == SizeRole)
        return country.prefix_number();
    else if (role == FlagRole)
        return country.flag_number();
    return QVariant();
}

QHash<int, QByteArray> CountriesData::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "name";
    roles[SizeRole] = "prefix_number";
    roles[FlagRole] = "flag_number";
    return roles;
}
//*********************************************************************************************
Country::Country(const QString &name, const QString &flag_number, const QString &prefix_number):m_name(name),m_flag_number(flag_number),m_prefix_number(prefix_number)
{

}

QString Country::name() const
{
    return m_name;
}

QString Country::flag_number() const
{
    return m_flag_number;
}

QString Country::prefix_number() const
{
    return m_prefix_number;
}

