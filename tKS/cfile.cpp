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

void cfile::getCity(QString _fname, int _list, int _colReg, int _colCity)
{
    qDebug() << "INSERT CITY - START " << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    if (!_fname.isEmpty()){
        excel = new QAxObject("Excel.Application"); //, this);
        excel->setProperty("Visible", 0);
        excel->setProperty("DisplayAlerts", 0);
        wbook = excel->querySubObject("Workbooks");
        book = wbook->querySubObject("Open (const QString&)", _fname);
        sheets = book->querySubObject("Sheets");

        currSheet = sheets->querySubObject("Item(Int)", _list);

        for (int r = 1; r < 25000; r++){
            // Наименование
            QAxObject *cellCity = currSheet->querySubObject("Cells(Int, Int)", r, _colCity);

            //убираем ненужные символы
            QString NAME = c_city->changeName(cellCity->dynamicCall("Value").toString());


            if (NAME.isEmpty()){
                break;
            } else {
                // получаем ID
                int ID = c_city->getIDByName(NAME);
                // регион
                QAxObject *cellReg = currSheet->querySubObject("Cells(Int, Int)", r, _colReg);
                QString REG = cellReg->dynamicCall("Value").toString();
                //собираем map для сохранения
                QMap<QString, QVariant> MAP;
                MAP.insert("id", ID);
                MAP.insert("name", NAME);
                MAP.insert("region", REG);

                QMap<QString, QVariant> FEED = c_city->save(MAP);
                if (!FEED.value("error").toString().isEmpty()){
                    qDebug() << "Error saving CITY: " << FEED.value("error").toString();
                } else {
                    qDebug() << "INSERT CITY - ID: " << FEED.value("lastId").toInt();
                }
            }
        }
        wbook->dynamicCall("Close()");
        excel->dynamicCall("Quit()");
        delete excel;
    }
    qDebug() << "INSERT CITY - OVER " << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void cfile::getStreet(QString _fname, int _list, int _colCity, int _colStreet)
{
    qDebug() << "INSERT STREET - START " << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
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
            QString S_NAME = cellStreet->dynamicCall("Value").toString();
            if (S_NAME.isEmpty()){
                break;
            } else {
                QAxObject *cellCity = currSheet->querySubObject("Cells(Int, Int)", r, _colCity);
                //перед поиском ID города меняем имя
                QString CITY_NAME = c_city->changeName(cellCity->dynamicCall("Value").toString());
                int CITY_ID = c_city->getIDByName(CITY_NAME);
                // получаем ID улицы
                int S_ID = c_street->getIDByName(S_NAME, CITY_ID);
                //собираем map для сохранения
                QMap<QString, QVariant> MAP;
                MAP.insert("id", S_ID);
                MAP.insert("name", S_NAME);
                MAP.insert("city", CITY_ID);

                QMap<QString, QVariant> FEED = c_street->save(MAP);
                if (!FEED.value("error").toString().isEmpty()){
                    qDebug() << "Error saving STREET: " << FEED.value("error").toString();
                } else {
                    qDebug() << "INSERT STREET - ID: " << FEED.value("lastId").toInt();
                }
            }
        }

        wbook->dynamicCall("Close()");
        excel->dynamicCall("Quit()");
        delete excel;
    }
}

void cfile::getBase(QString _fname, QMap<QString, QVariant> _map)
{
    qDebug() << "INSERT BASE - START " << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
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
                int _cityID = c_city->getIDByName(c_city->changeName(_city));

                QAxObject *cellStreet = currSheet->querySubObject("Cells(Int, Int)", r, _map.value("street").toInt());
                int _streetID = c_street->getIDByName(cellStreet->dynamicCall("Value").toString(), _cityID);

                QAxObject *cellHouse = currSheet->querySubObject("Cells(Int, Int)", r, _map.value("house").toInt());
                QString _house = cellHouse->dynamicCall("Value").toString();

                QAxObject *cellStatus = currSheet->querySubObject("Cells(Int, Int)", r, _map.value("status").toInt());
                int _statusID = c_status->getIDByName(cellStatus->dynamicCall("Value").toString());

                QAxObject *cellDiscount = currSheet->querySubObject("Cells(Int, Int)", r, _map.value("discount").toInt());
                int _discountID = c_discount->getIDByName(cellDiscount->dynamicCall("Value").toString());

                int _baseID = c_base->getBaseID(_cityID, _streetID, _house);

                QMap<QString, QVariant> MAP;
                MAP.insert("id", _baseID);
                MAP.insert("city", _cityID);
                MAP.insert("street", _streetID);
                MAP.insert("house", _house);
                MAP.insert("status", _statusID);
                MAP.insert("discount", _discountID);

                QMap<QString, QVariant> FEED = c_base->save(MAP);
                if (!FEED.value("error").toString().isEmpty()){
                    qDebug() << "Error saving BASE: " << FEED.value("error").toString();
                } else {
                    qDebug() << "INSERT BASE - ID: " << FEED.value("lastId").toInt();
                }
            }
        }

        wbook->dynamicCall("Close()");
        excel->dynamicCall("Quit()");
        delete excel;
    }
    qDebug() << "INSERT BASE - FINISH " << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
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
                int _streetID = c_street->getIDByName(cellStreet->dynamicCall("Value").toString(), _cityID);

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
   // QStringList _cityList = c_city->getCityByRegion(1); // только 1 регион
    QStringList _cityList = c_city->getCityAll();

    int _sityCount = _cityList.size(); //5;

    //Города
    for (int x = 0; x < _sityCount; x++){
        int _cityID = _cityList.at(x).split("|").at(0).toInt();
        int _cityRegion = _cityList.at(x).split("|").at(3).toInt();

        QString _cityName = _cityList.at(x).split("|").at(1);

        _doc.append(QString("\t\"%1\":{\n\r").arg(_cityName));
        qDebug() << "_cityID" << _cityID << "_cityName" << _cityName;

        //Улицы
        QStringList _streetList = c_street->getStreetsByCity(_cityID);

        for (int a = 0; a < _streetList.size(); a++){
            int _streetID = _streetList.at(a).split("|").at(0).toInt();
            QString _streetName = _streetList.at(a).split("|").at(1);

            _doc.append(QString("\t\t\"%1\":{\n\r").arg(_streetName));
            qDebug() << "_streetID" << _streetID << "_cityName" << _cityName;

            // номера домов
            QStringList _houseList = c_base->getBaseByCityStreet(_cityID, _streetID);
            qDebug() << _houseList;
            for (int b = 0; b < _houseList.size(); b++){
                if (b == _houseList.size() - 1){
                    _doc.append(QString("\t\t\t\"%0\":[\"%1\", \"%2\"]\n\r")
                                .arg(_houseList.at(b).split("|").at(0))
                                .arg(_houseList.at(b).split("|").at(1))
                                .arg(_houseList.at(b).split("|").at(2)));
                } else {
                    _doc.append(QString("\t\t\t\"%0\":[\"%1\", \"%2\"],\n\r")
                                .arg(_houseList.at(b).split("|").at(0))
                                .arg(_houseList.at(b).split("|").at(1))
                                .arg(_houseList.at(b).split("|").at(2)));
                }
            }
            //**house
            _doc.append("\t\t},\n\r");
        }


        _doc.append("\t\t\"planList\":{\n\r");

        QStringList _planList = c_plan->getPlansByRegion(_cityRegion, 1);
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

void cfile::makeJSONDocumentDITV(QString _fname)
{
    QString _doc = "HomeInternet_TV = {\n\r";
   // QStringList _cityList = c_city->getCityByRegion(1); // только 1 регион
    QStringList _cityList = c_city->getCityAll();

    int _sityCount = _cityList.size(); //5;

    //Города
    for (int x = 0; x < _sityCount; x++){
        int _cityID = _cityList.at(x).split("|").at(0).toInt();
        int _cityRegion = _cityList.at(x).split("|").at(3).toInt();
        QString _cityName = _cityList.at(x).split("|").at(1);

        _doc.append(QString("\t\"%1\":{\n\r").arg(_cityName));
        qDebug() << "_cityID" << _cityID << "_cityName" << _cityName;

        //Улицы
        QStringList _streetList = c_street->getStreetsByCity(_cityID);

        for (int a = 0; a < _streetList.size(); a++){
            int _streetID = _streetList.at(a).split("|").at(0).toInt();
            QString _streetName = _streetList.at(a).split("|").at(1);

            _doc.append(QString("\t\t\"%1\":{\n\r").arg(_streetName));
            qDebug() << "_streetID" << _streetID << "_cityName" << _cityName;

            // номера домов
            QStringList _houseList = c_base->getBaseByCityStreet(_cityID, _streetID);
            qDebug() << _houseList;
            for (int b = 0; b < _houseList.size(); b++){

                if (b == _houseList.size() - 1){
                    _doc.append(QString("\t\t\t\"%0\":[\"%1\", \"%2\"]\n\r")
                                .arg(_houseList.at(b).split("|").at(0))
                                .arg(_houseList.at(b).split("|").at(1))
                                .arg(_houseList.at(b).split("|").at(2)));
                } else {
                    _doc.append(QString("\t\t\t\"%0\":[\"%1\", \"%2\"],\n\r")
                                .arg(_houseList.at(b).split("|").at(0))
                                .arg(_houseList.at(b).split("|").at(1))
                                .arg(_houseList.at(b).split("|").at(2)));
                }
            }
            //**house
            _doc.append("\t\t},\n\r");
        }


        _doc.append("\t\t\"planList\":{\n\r");

        QStringList _planListA = c_plan->getPlansByRegion(_cityRegion, 21);
        _doc.append("\t\t\t\"Акционная АП\":{\n\r");
        for (int a = 0; a < _planListA.size(); a++){
            if (a == _planListA.size() - 1){
                _doc.append(QString("\t\t\t\t\"%0\":\"%1\"\n\r")
                            .arg(_planListA.at(a).split("|").at(1))
                            .arg(_planListA.at(a).split("|").at(2)));
            } else {
                _doc.append(QString("\t\t\t\t\"%0\":\"%1\",\n\r")
                            .arg(_planListA.at(a).split("|").at(1))
                            .arg(_planListA.at(a).split("|").at(2)));
            }
        }
        _doc.append("\t\t\t},\n\r");

        QStringList _planListB = c_plan->getPlansByRegion(_cityRegion, 22);
        _doc.append("\t\t\t\"Стандартная АП\":{\n\r");
        for (int a = 0; a < _planListB.size(); a++){
            if (a == _planListB.size() - 1){
                _doc.append(QString("\t\t\t\t\"%0\":\"%1\"\n\r")
                            .arg(_planListB.at(a).split("|").at(1))
                            .arg(_planListB.at(a).split("|").at(2)));
            } else {
                _doc.append(QString("\t\t\t\t\"%0\":\"%1\",\n\r")
                            .arg(_planListB.at(a).split("|").at(1))
                            .arg(_planListB.at(a).split("|").at(2)));
            }
        }
        _doc.append("\t\t\t}\n\r");


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

void cfile::makeJSONDocumentALL(QString _fname)
{
    QString _doc = "All = {\n\r";
   // QStringList _cityList = c_city->getCityByRegion(1); // только 1 регион
    QStringList _cityList = c_city->getCityAll();

    int _sityCount = _cityList.size(); //5;

    //Города
    for (int x = 0; x < _sityCount; x++){
        int _cityID = _cityList.at(x).split("|").at(0).toInt();
        int _cityRegion = _cityList.at(x).split("|").at(4).toInt(); // region All

        QString _cityName = _cityList.at(x).split("|").at(1);

        _doc.append(QString("\t\"%1\":{\n\r").arg(_cityName));
        //qDebug() << "_cityID" << _cityID << "_cityName" << _cityName;

        //Улицы
        QStringList _streetList = c_street->getStreetsByCity(_cityID);

        for (int a = 0; a < _streetList.size(); a++){
            int _streetID = _streetList.at(a).split("|").at(0).toInt();
            QString _streetName = _streetList.at(a).split("|").at(1);

            _doc.append(QString("\t\t\"%1\":{\n\r").arg(_streetName));
            //qDebug() << "_streetID" << _streetID << "_cityName" << _cityName;

            // номера домов
            QStringList _houseList = c_base->getBaseByCityStreet(_cityID, _streetID);
            //qDebug() << _houseList;
            for (int b = 0; b < _houseList.size(); b++){
                if (b == _houseList.size() - 1){
                    _doc.append(QString("\t\t\t\"%0\":[\"%1\", \"%2\"]\n\r")
                                .arg(_houseList.at(b).split("|").at(0))
                                .arg(_houseList.at(b).split("|").at(1))
                                .arg(_houseList.at(b).split("|").at(2)));
                } else {
                    _doc.append(QString("\t\t\t\"%0\":[\"%1\", \"%2\"],\n\r")
                                .arg(_houseList.at(b).split("|").at(0))
                                .arg(_houseList.at(b).split("|").at(1))
                                .arg(_houseList.at(b).split("|").at(2)));
                }
            }
            //**house
            _doc.append("\t\t},\n\r");
        }


        _doc.append("\t\t\"planList\":{\n\r");

        QStringList _planList = c_plan->getPlansByRegion(_cityRegion, 3);
        if (_planList.size() == 0){

            qDebug()<< _cityName << _cityRegion;
        }

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
    qDebug() << "done";
}
