#include "cstatus.h"

cstatus::cstatus()
{

}

void cstatus::setCurrent(int _id)
{
    STATUS.clear();
    QSqlQuery query(QString("SELECT status.name FROM status WHERE status.id = \'%0\' ").arg(_id));
    query.next();
    STATUS.insert("name", query.value(0).toString());
}

QString cstatus::getName()
{
    return STATUS.value("name").toString();
}

bool cstatus::testDelete(int _id)
{
    bool res = true;
    QSqlQuery query(QString("SELECT Count(base.id) FROM base WHERE base.status = \'%0\' ").arg(_id));
    query.next();
    if (query.value(0).toInt() > 0){
        res = false;
    }
    return res;
}

QMap<QString, QVariant> cstatus::save(QMap<QString, QVariant> saveMap)
{
    QString _error;
    int _lastId = 0;
    if (saveMap.value("id").toInt() == 0){
        QSqlQuery query("INSERT INTO status (name) VALUES (?) ");
        query.bindValue(0, saveMap.value("name").toString());
        query.exec();
        if (query.lastError().isValid()){
            _error.append(query.lastError().text());
        } else {
            _lastId = query.lastInsertId().toInt();
        }
    } else {
        QSqlQuery query(QString("UPDATE status SET name = \'%0\' WHERE status.id = \'%0\' ")
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

QString cstatus::del(int _id)
{
    QString _error;
    QSqlQuery query(QString("DELETE FROM status WHERE status.id = \'%0\' ").arg(_id));
    query.exec();
    if (query.lastError().isValid()){
        _error.append(query.lastError().text());
    }
    return _error;
}

QStringList cstatus::getStatusAll()
{
    QStringList _list;// 0 id|1 name
    QSqlQuery query("SELECT status.id, status.name FROM status ORDER BY status.name");
    while (query.next()) {
        _list << QString("%0|%1")
                 .arg(query.value(0).toString())
                 .arg(query.value(1).toString());
    }
    return _list;
}
