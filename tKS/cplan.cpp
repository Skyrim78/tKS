#include "cplan.h"

cPlan::cPlan()
{

}

void cPlan::setCurrent(int _id)
{
    PLAN.clear();
    QSqlQuery query(QString("SELECT plan.name, plan.price, plan.region, region.name "
                            "FROM plan "
                            "INNER JOIN region ON (plan.region = region.id) "
                            "WHERE plan.id = \'%0\' ").arg(_id));
    query.next();
    PLAN.insert("name", query.value(0).toString());
    PLAN.insert("price", query.value(1).toDouble());
    PLAN.insert("regionID", query.value(2).toInt());
    PLAN.insert("regionName", query.value(3).toString());

}

QString cPlan::getName()
{
    return PLAN.value("name").toString();
}

int cPlan::getRegionID()
{
    return PLAN.value("regionID").toInt();
}

QString cPlan::getRegionName()
{
    return PLAN.value("regionName").toString();
}

double cPlan::getPrice()
{
    return PLAN.value("name").toDouble();
}

bool cPlan::testDelete(int _id)
{
    bool res = true;
    return res;
}

QMap<QString, QVariant> cPlan::save(QMap<QString, QVariant> saveMap)
{
    QString _error;
    int _lastId = 0;
    if (saveMap.value("id").toInt() == 0){
        QSqlQuery query("INSERT INTO plan (name, price, region, vid) VALUES (?, ?, ?, ?) ");
        query.bindValue(0, saveMap.value("name").toString());
        query.bindValue(1, saveMap.value("price").toDouble());
        query.bindValue(2, saveMap.value("region").toInt());
        query.bindValue(3, saveMap.value("vid").toInt());
        query.exec();
        if (query.lastError().isValid()){
            _error.append(query.lastError().text());
        } else {
            _lastId = query.lastInsertId().toInt();
        }
    } else {
        QSqlQuery query(QString("UPDATE plan SET name = \'%0\', price = \'%1\', region = \'%2\' "
                                "WHERE plan.id = \'%3\' ")
                        .arg(saveMap.value("name").toString())
                        .arg(saveMap.value("price").toDouble())
                        .arg(saveMap.value("region").toInt())
                        .arg(saveMap.value("id").toInt()));
        query.exec();
        if (query.lastError().isValid()){
            _error.append(query.lastError().text());
        } else {
            _lastId = saveMap.value("id").toInt();
        }
    }
    QMap<QString, QVariant> _feed;
    _feed.insert("error", _error);
    _feed.insert("lastId", _lastId);

    return _feed;
}

QString cPlan::del(int _id)
{
    QString _error;
    QSqlQuery query(QString("DELETE FROM plan WHERE plan.id = \'%0\' ").arg(_id));
    query.exec();
    if (query.lastError().isValid()){
        _error.append(query.lastError().text());
    }
    return _error;
}

QStringList cPlan::getPlansByVid(int _vid)
{
    QStringList _list;// 0 id|1 name|2 price|3 region
    QSqlQuery query(QString("SELECT plan.id, plan.name, plan.price, region.name "
                            "FROM plan "
                            "INNER JOIN region ON (plan.region = region.id) "
                            "WHERE plan.vid = \'%0\' ").arg(_vid));
    while (query.next()) {
        _list << QString("%0|%1|%2|%3")
                 .arg(query.value(0).toString())
                 .arg(query.value(1).toString())
                 .arg(query.value(2).toString())
                 .arg(query.value(3).toString());

    }
    return _list;
}

