#ifndef CREGION_H
#define CREGION_H

#include <QMap>
#include <QtSql>

class cRegion
{
public:
    cRegion();
    QMap<QString, QVariant> REG;

public slots:
    void setCurrent(int _id);
    QString getName();

    bool testDelete(int _id);
    QMap<QString, QVariant> save(QMap<QString, QVariant> saveMap);
    QString del(int _id);

    QStringList getRegionAll();
};

#endif // CREGION_H
