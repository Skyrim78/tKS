#include "ccity.h"

cCity::cCity()
{

}

void cCity::setCurrent(int _id)
{
    CITY.clear();
    QSqlQuery query(QString("SELECT city.name, city.region, region.name "
                            "FROM city "
                            "INNER JOIN region ON (city.region = region.id) "
                            "WHERE city.id = \'%0\' ").arg(_id));
    query.next();
    CITY.insert("name", query.value(0).toString());
    CITY.insert("regionID", query.value(1).toInt());
    CITY.insert("regionName", query.value(2).toString());
}

QString cCity::getName()
{
    return CITY.value("name").toString();
}

int cCity::getRegionID()
{
    return CITY.value("regionID").toInt();
}

QString cCity::getRegionName()
{
    return CITY.value("regionName").toString();
}

bool cCity::testDelete(int _id)
{
    bool res = true;
    QSqlQuery query(QString("SELECT Count(base.id) FROM base WHERE base.city = \'%0\' ").arg(_id));
    query.next();
    if (query.value(0).toInt() > 0){
        res = false;
    }
    return res;
}

QMap<QString, QVariant> cCity::save(QMap<QString, QVariant> saveMap)
{
    QString _error;
    int _lastId = 0;
    if (saveMap.value("id").toInt() == 0){
        QSqlQuery query("INSERT INTO city (name, region) VALUES (?, ?) ");
        query.bindValue(0, saveMap.value("name").toString());
        query.bindValue(1, saveMap.value("region").toInt());
        query.exec();
        if (query.lastError().isValid()){
            _error.append(query.lastError().text());
        } else {
            _lastId = query.lastInsertId().toInt();
        }
    } else {
        QSqlQuery query(QString("UPDATE city SET name = \'%0\', region = \'%1\' WHERE city.id = \'%2\' ")
                        .arg(saveMap.value("name").toString())
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

QString cCity::del(int _id)
{
    QString _error;
    QSqlQuery query(QString("DELETE FROM city WHERE city.id = \'%0\' ").arg(_id));
    query.exec();
    if (query.lastError().isValid()){
        _error.append(query.lastError().text());
    }
    return _error;
}

QStringList cCity::getCityByRegion(int _regionID)
{
    QStringList _list;// 0 id|1 name|2 regionName
    QSqlQuery query(QString("SELECT city.id, city.name, region.name "
                            "FROM city "
                            "INNER JOIN region ON (city.region = region.id) "
                            "WHERE city.id = \'%0\' ").arg(_regionID));
    while (query.next()) {
        _list << QString("%0|%1|%2")
                 .arg(query.value(0).toString())
                 .arg(query.value(1).toString())
                 .arg(query.value(2).toString());
    }
    return _list;
}
