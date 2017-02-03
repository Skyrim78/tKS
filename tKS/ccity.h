#ifndef CCITY_H
#define CCITY_H

#include <QMap>
#include <QtSql>

class cCity
{
public:
    cCity();
    QMap<QString, QVariant> CITY;

public slots:
    void setCurrent(int _id);    
    QString getName();
    int getRegionID();
    QString getRegionName();

    bool testDelete(int _id);
    QMap<QString, QVariant> save(QMap<QString, QVariant> saveMap);
    QString del(int _id);

    QStringList getCityByRegion(int _regionID);
    int getIDByName(QString _name);

};

#endif // CCITY_H
