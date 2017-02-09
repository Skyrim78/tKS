#ifndef CBASE_H
#define CBASE_H

#include <QMap>
#include <QtSql>


class cBase
{
public:
    cBase();
    QMap<QString, QVariant> BASE;

public slots:
    void setCurrent(int _id);
    int getCityID();
    int getStreetID();
    QString getHouse();
    int getStatusID();
    int getDiscountID();

    int getBaseID(int _city, int _street, QString _house);
    bool testDelete(int _id);
    QMap<QString, QVariant> save(QMap<QString, QVariant> saveMap);
    QString del(int _id);

    QStringList getBaseAll();
    QStringList getBaseByCityStreet(int _city, int _street);
};

#endif // CBASE_H
