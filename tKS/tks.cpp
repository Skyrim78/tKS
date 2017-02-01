#include "tks.h"
#include "ui_tks.h"

tKS::tKS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tKS)
{
    ui->setupUi(this);
    connectDB();

    vStreet = new street(this);

    TabWidget  *tab = new TabWidget();
    tab->setTabPosition(TabWidget :: West);
    tab->addTab(vStreet, "Улицы");

    setCentralWidget(tab);

    connect(tab, SIGNAL(currentChanged(int)), this, SLOT(change_tab(int)));
}

tKS::~tKS()
{
    if (DB.isOpen()){
        DB.close();
    }
    delete ui;
}

void tKS::connectDB()
{
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("ks.db3");
    DB.open();
}

void tKS::changeTab(int x)
{
    if (x == 1){
        //vStreet->load();
    }
}
