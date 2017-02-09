#include "cbase.h"

cBase::cBase()
{

}

void cBase::setCurrent(int _id)
{
    BASE.clear();
    QSqlQuery query(QString("SELECT base.city, base.street, base.house, base.status, base.discount "
                            "FROM base "
                            "WHERE base.id = \'%0\' ").arg(_id));
    query.next();
    BASE.insert("city", query.value(0).toInt());
    BASE.insert("street", query.value(1).toInt());
    BASE.insert("house", query.value(2).toString());
    BASE.insert("status", query.value(3).toInt());
    BASE.insert("discount", query.value(4).toInt());
}

int cBase::getCityID()
{
    return BASE.value("city").toInt();
}

int cBase::getStreetID()
{
    return BASE.value("street").toInt();
}

QString cBase::getHouse()
{
    return BASE.value("house").toString();
}

int cBase::getStatusID()
{
    return BASE.value("status").toInt();
}

int cBase::getDiscountID()
{
    return BASE.value("discount").toInt();
}

int cBase::getBaseID(int _city, int _street, QString _house)
{
    int id = 0;
    QSqlQuery query(QString("SELECT base.id FROM base "
                            "WHERE (base.city = \'%0\') AND (base.house = \'%1\') AND (base.street = \'%2\')")
                    .arg(_city)
                    .arg(_house)
                    .arg(_street));
    query.next();
    if (query.isValid()){
        id = query.value(0).toInt();
    }
    return id;
}

bool cBase::testDelete(int _id)
{
    bool res = true;
    return res;
}

QMap<QString, QVariant> cBase::save(QMap<QString, QVariant> saveMap)
{
    QString _error;
    int _lastId = 0;
    if (saveMap.value("id").toInt() == 0){
        QSqlQuery query("INSERT INTO base (city, street, house, status, discount) VALUES (?, ?, ?, ?, ?) ");
        query.bindValue(0, saveMap.value("city").toInt());
        query.bindValue(1, saveMap.value("street").toInt());
        query.bindValue(2, saveMap.value("house").toString());
        query.bindValue(3, saveMap.value("status").toInt());
        query.bindValue(4, saveMap.value("discount").toInt());
        query.exec();
        if (query.lastError().isValid()){
            _error = query.lastError().text();
        } else {
            _lastId = query.lastInsertId().toInt();
        }
    } else {
        QSqlQuery query(QString("UPDATE base SET city = \'%0\', street = \'%1\', house = \'%2\', status = \'%3\', "
                                "discount = \'%4\' WHERE base.id = \'%5\' ")
                        .arg(saveMap.value("city").toInt())
                        .arg(saveMap.value("street").toInt())
                        .arg(saveMap.value("house").toString())
                        .arg(saveMap.value("status").toInt())
                        .arg(saveMap.value("discount").toInt())
                        .arg(saveMap.value("id").toInt()));
        query.exec();
        if (query.lastError().isValid()){
            _error = query.lastError().text();
        } else {
            _lastId = saveMap.value("id").toInt();
        }
    }
    QMap<QString, QVariant> _feed;
    _feed.insert("error", _error);
    _feed.insert("lastId", _lastId);

    return _feed;
}

QString cBase::del(int _id)
{
    QString _error;
    QSqlQuery query(QString("DELETE FROM base WHERE base.id = \'%0\' ").arg(_id));
    query.exec();
    if (query.lastError().isValid()){
        _error.append(query.lastError().text());
    }
    return _error;
}

QStringList cBase::getBaseAll()
{
    QStringList _list;// 0 id|1 city|2 street|3 house|4 name|5 discount
    QSqlQuery query(QString("SELECT base.id, city.name, street.name, base.house, status.name, discount.name "
                            "FROM base "
                            "INNER JOIN city ON (base.city = city.id) "
                            "INNER JOIN street ON (base.street = street.id) "
                            "INNER JOIN status ON (base.status = status.id) "
                            "INNER JOIN discount ON (base.discount = discount.id) "
                            "ORDER BY city.name, street.name "));
    while (query.next()) {
        _list << QString("%0|%1|%2|%3|%4|%5")
                 .arg(query.value(0).toString())
                 .arg(query.value(1).toString())
                 .arg(query.value(2).toString())
                 .arg(query.value(3).toString())
                 .arg(query.value(4).toString())
                 .arg(query.value(5).toString());
    }
    return _list;
}

QStringList cBase::getBaseByCityStreet(int _city, int _street)
{
    QStringList _list;// 0 house|1 name|2 discount
    QSqlQuery query(QString("SELECT base.house, status.name, discount.name "
                            "FROM base "
                            "INNER JOIN status ON (base.status = status.id) "
                            "INNER JOIN discount ON (base.discount = discount.id) "
                            "WHERE (base.city = \'%0\') AND (base.street = \'%1\') "
                            "ORDER BY base.street, base.house ")
                    .arg(_city)
                    .arg(_street));
    while (query.next()) {
        //qDebug() << query.value(0).toString();
        _list << QString("%0|%1|%2")
                 .arg(query.value(0).toString())
                 .arg(query.value(1).toString())
                 .arg(query.value(2).toString());
    }
    return _list;
}
