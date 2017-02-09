#ifndef CSTREET_H
#define CSTREET_H

#include <QMap>
#include <QtSql>

class cStreet
{
public:
    cStreet();

    QMap<QString, QVariant> STREET;

public slots:
    void setCurrent(int _id);
    QString getName();
    QString getCity();

    bool testDelete(int _id);
    QMap<QString, QVariant> save(QMap<QString, QVariant> saveMap);
    QString del(int _id);

    QStringList getStreetsByCity(int _city);
    int getIDByName(QString _name, int _cityId);

};

#endif // CSTREET_H
