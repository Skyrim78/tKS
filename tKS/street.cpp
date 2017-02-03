#include "street.h"
#include "ui_street.h"

street::street(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::street)
{
    ui->setupUi(this);

    c_file = new cfile();
    c_city = new cCity();
    c_street = new cStreet();
    c_base = new cBase();

    connect(ui->pushButton_getBase, SIGNAL(clicked(bool)), this, SLOT(uploadBase()));

    connect(ui->pushButton_make, SIGNAL(clicked(bool)), this, SLOT(makeDI()));
    connect(ui->pushButton_makeJSON, SIGNAL(clicked(bool)), this, SLOT(makeDIJSON()));

}

street::~street()
{
    delete ui;
}

void street::uploadCity()
{
    QString _fname = QFileDialog::getOpenFileName(this, "Select", "/HOME", "Excel (*.xlsx)");
    QStringList _cityList = c_file->getCity(_fname, 2, 1, 2);
    qDebug() << "opening and reading file...";

    for (int x = 0; x < _cityList.size(); x++){
        QStringList _line = _cityList.at(x).split("|");
        QMap<QString,QVariant> saveMap;
        saveMap.insert("id", 0);
        saveMap.insert("region", _line.at(0).toInt());
        saveMap.insert("name", _line.at(1));
        QMap<QString,QVariant> _feed = c_city->save(saveMap);
        if (!_feed.value("error").toString().isEmpty()){
            qDebug() << _feed.value("error").toString();
        }
        qDebug() << "work with Database...";
    }
    qDebug() << "done...";
}

void street::uploadStreet()
{
    QString _fname = QFileDialog::getOpenFileName(this, "Select", "/HOME", "Excel (*.xlsx)");
    qDebug() << "opening and reading file...";
    QStringList _streetList = c_file->getStreet(_fname, 3, 1, 2);
    qDebug() << "work with Database...";
    for (int x = 0; x < _streetList.size(); x++){
        QStringList _line = _streetList.at(x).split("|");
        QMap<QString,QVariant> saveMap;
        saveMap.insert("id", 0);
        saveMap.insert("city", _line.at(0).toInt());
        saveMap.insert("name", _line.at(1));
        QMap<QString,QVariant> _feed = c_street->save(saveMap);
        if (!_feed.value("error").toString().isEmpty()){
            qDebug() << _feed.value("error").toString();
        }
    }
    qDebug() << "done...";
}

void street::uploadBase()
{

    QString _fname = QFileDialog::getOpenFileName(this, "Select", "/HOME", "Excel (*.xlsx)");
    qDebug() << "opening and reading file...";
    QMap<QString, QVariant> _map;
    _map.insert("list", 1);
    _map.insert("city", 7);
    _map.insert("street", 8);
    _map.insert("house", 9);
    _map.insert("status", 10);
    _map.insert("discount", 11);

    c_file->uploadBasetoDB(_fname, _map);


//    QStringList _streetList = c_file->getBase(_fname, _map);
//    qDebug() << "work with Database...";
//    for (int x = 0; x < _streetList.size(); x++){
//        QStringList _line = _streetList.at(x).split("|");
//        QMap<QString,QVariant> saveMap;
//        saveMap.insert("id", c_base->getBaseID(_line.at(0).toInt(), _line.at(1).toInt(), _line.at(2)));
//        saveMap.insert("city", _line.at(0).toInt());
//        saveMap.insert("street", _line.at(1).toInt());
//        saveMap.insert("house", _line.at(2));
//        saveMap.insert("status", _line.at(3).toInt());
//        saveMap.insert("discount", _line.at(4).toInt());
//        QMap<QString,QVariant> _feed = c_base->save(saveMap);
//        if (!_feed.value("error").toString().isEmpty()){
//            qDebug() << _feed.value("error").toString();
//        }
//    }
    qDebug() << "done...";
}

void street::makeDI()
{
    QString _fname = QFileDialog::getSaveFileName(this, "Select", "/HOME", "XML (*.xml)");
    if (!_fname.isEmpty()){
        c_file->makeXMLDocumentDI(_fname);
    }
}

void street::makeDIJSON()
{
    QString _fname = QFileDialog::getSaveFileName(this, "Select", "/HOME", "JSON (*.json)");
    if (!_fname.isEmpty()){
        c_file->makeJSONDocumentDI(_fname);
    }
}
