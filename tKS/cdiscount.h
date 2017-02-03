#ifndef CDISCOUNT_H
#define CDISCOUNT_H

#include <QMap>
#include <QtSql>

class cdiscount
{
public:
    cdiscount();

    QMap<QString, QVariant> DIS;

public slots:
    void setCurrent(int _id);
    QString getName();

    bool testDelete(int _id);
    QMap<QString, QVariant> save(QMap<QString, QVariant> saveMap);
    QString del(int _id);

    QStringList getDiscountAll();
    int getIDByName(QString _name);
};

#endif // CDISCOUNT_H
