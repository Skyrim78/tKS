#ifndef CSTATUS_H
#define CSTATUS_H

#include <QMap>
#include <QtSql>


class cstatus
{
public:
    cstatus();

    QMap<QString, QVariant> STATUS;

public slots:
    void setCurrent(int _id);
    QString getName();

    bool testDelete(int _id);
    QMap<QString, QVariant> save(QMap<QString, QVariant> saveMap);
    QString del(int _id);

    QStringList getStatusAll();
    int getIDByName(QString _name);
};

#endif // CSTATUS_H
