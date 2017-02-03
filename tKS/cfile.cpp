#include "cfile.h"

cfile::cfile()
{
    c_city = new cCity();
    c_street = new cStreet();
    c_status = new cstatus();
    c_discount = new cdiscount();
    c_base = new cBase();
    c_plan = new cPlan();

}

QStringList cfile::getCity(QString _fname, int _list, int _colReg, int _colCity)
{
    QStringList cityList;
    if (!_fname.isEmpty()){
        excel = new QAxObject("Excel.Application"); //, this);
        excel->setProperty("Visible", 0);
        excel->setProperty("DisplayAlerts", 0);
        wbook = excel->querySubObject("Workbooks");
        book = wbook->querySubObject("Open (const QString&)", _fname);
        sheets = book->querySubObject("Sheets");

        currSheet = sheets->querySubObject("Item(Int)", _list);

        for (int r = 2; r < 25000; r++){
            QAxObject *cellCity = currSheet->querySubObject("Cells(Int, Int)", r, _colCity);
            QString _cityName = cellCity->dynamicCall("Value").toString();
            qDebug() << _cityName;
            if (_cityName.isEmpty()){
                break;
            } else {
                QAxObject *cellReg = currSheet->querySubObject("Cells(Int, Int)", r, _colReg);
                QString _reg = cellReg->dynamicCall("Value").toString();
                cityList << QString("%1|%2")
                           .arg(_reg)
                           .arg(_cityName);
            }
        }

        wbook->dynamicCall("Close()");
        excel->dynamicCall("Quit()");
        delete excel;
    }
    return cityList;
}

QStringList cfile::getStreet(QString _fname, int _list, int _colCity, int _colStreet)
{
    QStringList streetList;
    if (!_fname.isEmpty()){
        excel = new QAxObject("Excel.Application"); //, this);
        excel->setProperty("Visible", 0);
        excel->setProperty("DisplayAlerts", 0);
        wbook = excel->querySubObject("Workbooks");
        book = wbook->querySubObject("Open (const QString&)", _fname);
        sheets = book->querySubObject("Sheets");

        currSheet = sheets->querySubObject("Item(Int)", _list);

        for (int r = 2; r < 25000; r++){
            QAxObject *cellStreet = currSheet->querySubObject("Cells(Int, Int)", r, _colStreet);
            QString _streetName = cellStreet->dynamicCall("Value").toString();
            if (_streetName.isEmpty()){
                break;
            } else {
                QAxObject *cellCity = currSheet->querySubObject("Cells(Int, Int)", r, _colCity);
                int _cityID = c_city->getIDByName(cellCity->dynamicCall("Value").toString());
                streetList << QString("%1|%2")
                                .arg(_cityID)
                                .arg(_streetName);
            }
        }

        wbook->dynamicCall("Close()");
        excel->dynamicCall("Quit()");
        delete excel;
    }
    return streetList;
}

QStringList cfile::getBase(QString _fname, QMap<QString, QVariant> _map)
{
    QStringList baseList;
    if (!_fname.isEmpty()){

        excel = new QAxObject("Excel.Application"); //, this);
        excel->setProperty("Visible", 0);
        excel->setProperty("DisplayAlerts", 0);
        wbook = excel->querySubObject("Workbooks");
        book = wbook->querySubObject("Open (const QString&)", _fname);
        sheets = book->querySubObject("Sheets");

        currSheet = sheets->querySubObject("Item(Int)", _map.value("list").toInt());

        for (int r = 2; r < 100000; r++){
            QAxObject *cellCity = currSheet->querySubObject("Cells(Int, Int)", r, _map.value("city").toInt());
            QString _city = cellCity->dynamicCall("Value").toString();
            if (_city.isEmpty()){
                break;
            } else {
                int _cityID = c_city->getIDByName(_city);

                QAxObject *cellStreet = currSheet->querySubObject("Cells(Int, Int)", r, _map.value("street").toInt());
                int _streetID = c_street->getIDByName(cellStreet->dynamicCall("Value").toString());

                QAxObject *cellHouse = currSheet->querySubObject("Cells(Int, Int)", r, _map.value("house").toInt());
                QString _house = cellHouse->dynamicCall("Value").toString();

                QAxObject *cellStatus = currSheet->querySubObject("Cells(Int, Int)", r, _map.value("status").toInt());
                int _statusID = c_status->getIDByName(cellStatus->dynamicCall("Value").toString());

                QAxObject *cellDiscount = currSheet->querySubObject("Cells(Int, Int)", r, _map.value("discount").toInt());
                int _discountID = c_discount->getIDByName(cellDiscount->dynamicCall("Value").toString());

                baseList << QString("%0|%1|%2|%3|%4")
                            .arg(_cityID)
                            .arg(_streetID)
                            .arg(_house)
                            .arg(_statusID)
                            .arg(_discountID);
            }
        }

        wbook->dynamicCall("Close()");
        excel->dynamicCall("Quit()");
        delete excel;
    }
    return baseList;
}

void cfile::uploadBasetoDB(QString _fname, QMap<QString, QVariant> _map)
{
    if (!_fname.isEmpty()){

        excel = new QAxObject("Excel.Application"); //, this);
        excel->setProperty("Visible", 0);
        excel->setProperty("DisplayAlerts", 0);
        wbook = excel->querySubObject("Workbooks");
        book = wbook->querySubObject("Open (const QString&)", _fname);
        sheets = book->querySubObject("Sheets");

        currSheet = sheets->querySubObject("Item(Int)", _map.value("list").toInt());

        for (int r = 2; r < 70000; r++){
            QAxObject *cellCity = currSheet->querySubObject("Cells(Int, Int)", r, _map.value("city").toInt());
            QString _city = cellCity->dynamicCall("Value").toString();
            if (_city.isEmpty()){
                break;
            } else {
                int _cityID = c_city->getIDByName(_city);

                QAxObject *cellStreet = currSheet->querySubObject("Cells(Int, Int)", r, _map.value("street").toInt());
                int _streetID = c_street->getIDByName(cellStreet->dynamicCall("Value").toString());

                QAxObject *cellHouse = currSheet->querySubObject("Cells(Int, Int)", r, _map.value("house").toInt());
                QString _house = cellHouse->dynamicCall("Value").toString();

                QAxObject *cellStatus = currSheet->querySubObject("Cells(Int, Int)", r, _map.value("status").toInt());
                int _statusID = c_status->getIDByName(cellStatus->dynamicCall("Value").toString());

                QAxObject *cellDiscount = currSheet->querySubObject("Cells(Int, Int)", r, _map.value("discount").toInt());
                int _discountID = c_discount->getIDByName(cellDiscount->dynamicCall("Value").toString());

                int _baseID = c_base->getBaseID(_cityID, _streetID, _house);

                QMap<QString, QVariant> saveMap;
                saveMap.insert("id", _baseID);
                saveMap.insert("city", _cityID);
                saveMap.insert("street", _streetID);
                saveMap.insert("house", _house);
                saveMap.insert("status", _statusID);
                saveMap.insert("discount", _discountID);

                QMap<QString, QVariant> _feed = c_base->save(saveMap);
                if (_feed.value("error").toString().size() < 3){
                    qDebug() << _feed.value("lastId").toString();
                } else {
                    qDebug() << _feed.value("error").toString();
                }
            }
        }

        wbook->dynamicCall("Close()");
        excel->dynamicCall("Quit()");
        delete excel;
    }
}

void cfile::makeXMLDocumentDI(QString _fname)
{
    QDomDocument _doc;

    QDomProcessingInstruction _ver = _doc.createProcessingInstruction("xml", "version = '1.0' encoding = 'utf-8'");
    _doc.appendChild(_ver);

    QDomElement _root = _doc.createElement("DI");
    _doc.appendChild(_root);

    QStringList _cityList = c_city->getCityByRegion(1); // только 1 регион
    for (int x = 0; x < 5; x++){
        QString _cityName = _cityList.at(x).split("|").at(1);

        QDomElement tag_city = _doc.createElement("city");
        tag_city.setAttribute("name", _cityName);
        _root.appendChild(tag_city);

        QDomElement tag_addList = _doc.createElement("address-list");
        tag_city.appendChild(tag_addList);

        QStringList _addressList = c_base->getBaseByCity(_cityList.at(x).split("|").at(0).toInt());
        for (int a = 0; a < _addressList.size(); a++){
            QDomElement tag_address = _doc.createElement("address");
            tag_address.setAttribute("street", _addressList.at(a).split("|").at(1));
            tag_address.setAttribute("house", _addressList.at(a).split("|").at(2));
            tag_address.setAttribute("status", _addressList.at(a).split("|").at(3));
            tag_address.setAttribute("discount", _addressList.at(a).split("|").at(4));
            tag_addList.appendChild(tag_address);
        }

        QDomElement tag_planList = _doc.createElement("plan-list");
        tag_city.appendChild(tag_planList);

        QStringList _planList = c_plan->getPlansByRegion(1, 1);
        for (int a = 0; a < _planList.size(); a++){
            QDomElement tag_plan = _doc.createElement("plan");
            tag_plan.setAttribute("name", _planList.at(a).split("|").at(1));
            tag_plan.setAttribute("price", _planList.at(a).split("|").at(2));
            tag_planList.appendChild(tag_plan);
        }
    }

    //QString _xml = _doc.toString();

    QByteArray _ar = _doc.toByteArray();
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QString _xml = codec->toUnicode(_ar);


    QFile file(_fname);
    if (file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        out << _xml;
        file.close();
    }
}

void cfile::makeJSONDocumentDI(QString _fname)
{
    QString _doc = "HomeInternet = {\n\r";
    QStringList _cityList = c_city->getCityByRegion(1); // только 1 регион

    int _sityCount = 5;

    for (int x = 0; x < _sityCount; x++){
        QString _cityName = _cityList.at(x).split("|").at(1);

        _doc.append(QString("\t\"%1\":{\n\r").arg(_cityName));

        QStringList _addressList = c_base->getBaseByCity(_cityList.at(x).split("|").at(0).toInt());
        for (int a = 0; a < _addressList.size(); a++){
            _doc.append(QString("\t\t\"address\":[\"%0\", \"%1\", \"%2\", \"%3\"],\n\r")
                        .arg(_addressList.at(a).split("|").at(1))
                        .arg(_addressList.at(a).split("|").at(2))
                        .arg(_addressList.at(a).split("|").at(3))
                        .arg(_addressList.at(a).split("|").at(4)));
        }
        _doc.append("\t\t\"planList\":{\n\r");

        QStringList _planList = c_plan->getPlansByRegion(1, 1);
        for (int a = 0; a < _planList.size(); a++){
            if (a == _planList.size() - 1){
                _doc.append(QString("\t\t\t\"%0\":\"%1\"\n\r")
                            .arg(_planList.at(a).split("|").at(1))
                            .arg(_planList.at(a).split("|").at(2)));
            } else {
                _doc.append(QString("\t\t\t\"%0\":\"%1\",\n\r")
                            .arg(_planList.at(a).split("|").at(1))
                            .arg(_planList.at(a).split("|").at(2)));
            }
        }
        _doc.append("\t\t}\n\r");
        if (x == _sityCount - 1){
            _doc.append("\t}\n\r");
        } else {
            _doc.append("\t},\n\r");
        }
    }
    _doc.append("}\n\r");

    QByteArray _ar = _doc.toUtf8();
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QString _xml = codec->toUnicode(_ar);


    QFile file(_fname);
    if (file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        out << _xml;
        file.close();
    }
}
