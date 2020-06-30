#ifndef COUNTRIESDATA_H
#define COUNTRIESDATA_H

#include <QAbstractListModel>
#include <QStringList>

class Country{
public:
    Country(const QString &name ="", const QString &flag_number="",const QString &prefix_number="");
    QString name() const;
    QString flag_number() const;
    QString prefix_number() const;

private:
    QString m_name;
    QString m_flag_number;
    QString m_prefix_number;
};



class CountriesData : public QAbstractListModel
{
    Q_OBJECT


public:
    enum CountryRoles {
        TypeRole = Qt::UserRole + 1,
        SizeRole,
        FlagRole
    };
    explicit CountriesData(QObject *parent = nullptr);

    void addCountry(const Country &country); // function for adding data
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QString get_name(const QModelIndex &index);
    QString get_flag(const QModelIndex &index);
    QString get_prefix(const QModelIndex &index);
    Q_INVOKABLE QVariantMap get(int row);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
QList<Country> m_country;
};

#endif // COUNTRIESDATA_H
