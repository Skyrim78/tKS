#include "cstreet.h"

cStreet::cStreet()
{

}

void cStreet::setCurrent(int _id)
{
    STREET.clear();
    QSqlQuery query(QString("SELECT street.name, city.name "
                            "FROM street "
                            "INNER JOIN city ON (street.city = city.id) "
                            "WHERE street.id = \'%0\' ").arg(_id));
    query.next();
    STREET.insert("name", query.value(0).toString());
    STREET.insert("city", query.value(1).toString());
}

QString cStreet::getName()
{
    return STREET.value("name").toString();
}

QString cStreet::getCity()
{
    return STREET.value("city").toString();
}

bool cStreet::testDelete(int _id)
{
    bool res = true;
    QSqlQuery query(QString("SELECT Count(base.id) FROM base WHERE base.street = \'%0\' ").arg(_id));
    query.next();
    if (query.value(0).toInt() > 0){
        res = false;
    }
    return res;
}

QMap<QString, QVariant> cStreet::save(QMap<QString, QVariant> saveMap)
{
    QString _error;
    int _lastId = 0;
    if (saveMap.value("id").toInt() == 0){
        QSqlQuery query("INSERT INTO street (name, city) VALUES (?, ?) ");
        query.bindValue(0, saveMap.value("name").toString());
        query.bindValue(1, saveMap.value("city").toInt());
        query.exec();
        if (query.lastError().isValid()){
            _error.append(query.lastError().text());
        } else {
            _lastId = query.lastInsertId().toInt();
        }
    } else {
        QSqlQuery query(QString("UPDATE street SET name = \'%0\', city = \'%1\' WHERE street.id = \'%2\' ")
                        .arg(saveMap.value("name").toString())
                        .arg(saveMap.value("city").toInt())
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

QString cStreet::del(int _id)
{
    QString _error;
    QSqlQuery query(QString("DELETE FROM street WHERE street.id = \'%0\' ").arg(_id));
    query.exec();
    if (query.lastError().isValid()){
        _error.append(query.lastError().text());
    }
    return _error;
}

QStringList cStreet::getStreetsByCity(int _city)
{
    QStringList _list;// 0 id|1 name|2 cityName
    QSqlQuery query(QString("SELECT street.id, street.name, city.name "
                            "FROM street "
                            "INNER JOIN city ON (street.city = city.id) "
                            "WHERE street.id = \'%0\' ").arg(_city));
    while (query.next()) {
        _list << QString("%0|%1|%2")
                 .arg(query.value(0).toString())
                 .arg(query.value(1).toString())
                 .arg(query.value(2).toString());
    }
    return _list;
}

int cStreet::getIDByName(QString _name)
{
    int _id = 0;
    QSqlQuery query(QString("SELECT street.id FROM street WHERE street.name = \'%0\' ").arg(_name));
    query.next();
    if (query.isValid()){
        _id = query.value(0).toInt();
    }
    return _id;
}
