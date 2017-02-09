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
    connect(ui->pushButton_upCity, SIGNAL(clicked(bool)), this, SLOT(uploadCity()));
    connect(ui->pushButton_upStreet, SIGNAL(clicked(bool)), this, SLOT(uploadStreet()));

    connect(ui->pushButton_make, SIGNAL(clicked(bool)), this, SLOT(makeDI()));
    connect(ui->pushButton_makeJSON_1, SIGNAL(clicked(bool)), this, SLOT(makeDI_JSON()));
    connect(ui->pushButton_makeJSON_2, SIGNAL(clicked(bool)), this, SLOT(makeDITV_JSON()));
    connect(ui->pushButton_makeJSON_3, SIGNAL(clicked(bool)), this, SLOT(makeAll_JSON()));

}

street::~street()
{
    delete ui;
}

void street::uploadCity()
{
    QString _fname = QFileDialog::getOpenFileName(this, "Select", "/HOME", "Excel (*.xlsx)");
    c_file->getCity(_fname, 2, 1, 2);
}

void street::uploadStreet()
{
    QString _fname = QFileDialog::getOpenFileName(this, "Select", "/HOME", "Excel (*.xlsx)");
    c_file->getStreet(_fname, 3, 1, 2);
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

    c_file->getBase(_fname, _map);
    qDebug() << "done...";
}

void street::makeDI()
{
    QString _fname = QFileDialog::getSaveFileName(this, "Select", "/HOME", "XML (*.xml)");
    if (!_fname.isEmpty()){
        c_file->makeXMLDocumentDI(_fname);
    }
}

void street::makeDITV_JSON()
{
    QString _fname = QFileDialog::getSaveFileName(this, "Select", "/HOME", "JSON (*.json)");
    if (!_fname.isEmpty()){
        c_file->makeJSONDocumentDITV(_fname);
    }
}

void street::makeAll_JSON()
{
    QString _fname = QFileDialog::getSaveFileName(this, "Select", "/HOME", "JSON (*.json)");
    if (!_fname.isEmpty()){
        c_file->makeJSONDocumentALL(_fname);
    }
}

void street::makeDI_JSON()
{
    QString _fname = QFileDialog::getSaveFileName(this, "Select", "/HOME", "JSON (*.json)");
    if (!_fname.isEmpty()){
        c_file->makeJSONDocumentDI(_fname);
    }
}
