#include "cdiscount.h"

cdiscount::cdiscount()
{

}

void cdiscount::setCurrent(int _id)
{
    DIS.clear();
    QSqlQuery query(QString("SELECT discount.name FROM discount WHERE discount.id = \'%0\' ").arg(_id));
    query.next();
    DIS.insert("name", query.value(0).toString());
}

QString cdiscount::getName()
{
    return DIS.value("name").toString();
}

bool cdiscount::testDelete(int _id)
{
    bool res = true;
    QSqlQuery query(QString("SELECT Count(base.id) FROM base WHERE base.discount = \'%0\' ").arg(_id));
    query.next();
    if (query.value(0).toInt() > 0){
        res = false;
    }
    return res;
}

QMap<QString, QVariant> cdiscount::save(QMap<QString, QVariant> saveMap)
{
    QString _error;
    int _lastId = 0;
    if (saveMap.value("id").toInt() == 0){
        QSqlQuery query("INSERT INTO discount (name) VALUES (?) ");
        query.bindValue(0, saveMap.value("name").toString());
        query.exec();
        if (query.lastError().isValid()){
            _error.append(query.lastError().text());
        } else {
            _lastId = query.lastInsertId().toInt();
        }
    } else {
        QSqlQuery query(QString("UPDATE discount SET name = \'%0\' WHERE discount.id = \'%0\' ")
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

QString cdiscount::del(int _id)
{
    QString _error;
    QSqlQuery query(QString("DELETE FROM discount WHERE discount.id = \'%0\' ").arg(_id));
    query.exec();
    if (query.lastError().isValid()){
        _error.append(query.lastError().text());
    }
    return _error;
}

QStringList cdiscount::getDiscountAll()
{
    QStringList _list;// 0 id|1 name
    QSqlQuery query("SELECT discount.id, discount.name FROM discount ORDER BY discount.name");
    while (query.next()) {
        _list << QString("%0|%1")
                 .arg(query.value(0).toString())
                 .arg(query.value(1).toString());
    }
    return _list;
}

int cdiscount::getIDByName(QString _name)
{
    int _id = 0;
    QSqlQuery query(QString("SELECT discount.id FROM discount WHERE discount.name = \'%0\' ").arg(_name));
    query.next();
    if (query.isValid()){
        _id = query.value(0).toInt();
    }
    return _id;
}
