#include "cregion.h"

cRegion::cRegion()
{

}

void cRegion::setCurrent(int _id)
{
    REG.clear();
    QSqlQuery query(QString("SELECT region.name FROM region WHERE region.id = \'%0\' ").arg(_id));
    query.next();
    REG.insert("name", query.value(0).toString());
}

QString cRegion::getName()
{
    return REG.value("name").toString();
}

bool cRegion::testDelete(int _id)
{
    bool res = true;
    QSqlQuery query(QString("SELECT Count(city.id) FROM city WHERE city.region = \'%0\' ").arg(_id));
    query.next();
    if (query.value(0).toInt() > 0){
        res = false;
    }
    return res;
}

QMap<QString, QVariant> cRegion::save(QMap<QString, QVariant> saveMap)
{
    QString _error;
    int _lastId = 0;
    if (saveMap.value("id").toInt() == 0){
        QSqlQuery query("INSERT INTO region (name) VALUES (?) ");
        query.bindValue(0, saveMap.value("name").toString());
        query.exec();
        if (query.lastError().isValid()){
            _error.append(query.lastError().text());
        } else {
            _lastId = query.lastInsertId().toInt();
        }
    } else {
        QSqlQuery query(QString("UPDATE region SET name = \'%0\' WHERE region.id = \'%0\' ")
                        .arg(saveMap.value("name").toString())
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

QString cRegion::del(int _id)
{
    QString _error;
    QSqlQuery query(QString("DELETE FROM region WHERE region.id = \'%0\' ").arg(_id));
    query.exec();
    if (query.lastError().isValid()){
        _error.append(query.lastError().text());
    }
    return _error;
}

QStringList cRegion::getRegionAll()
{
    QStringList _list;// 0 id|1 name
    QSqlQuery query("SELECT region.id, region.name FROM region ORDER BY region.name");
    while (query.next()) {
        _list << QString("%0|%1")
                 .arg(query.value(0).toString())
                 .arg(query.value(1).toString());
    }
    return _list;
}
