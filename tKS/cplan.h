#ifndef CPLAN_H
#define CPLAN_H

#include <QMap>
#include <QtSql>

class cPlan
{
public:
    cPlan();
    QMap<QString, QVariant> PLAN;

public slots:
    void setCurrent(int _id);
    QString getName();
    int getRegionID();
    QString getRegionName();
    double getPrice();

    bool testDelete(int _id);
    QMap<QString, QVariant> save(QMap<QString, QVariant> saveMap);
    QString del(int _id);

    QStringList getPlansByVid(int _vid);
    QStringList getPlansByRegion(int _region, int _vid);
};

#endif // CPLAN_H
