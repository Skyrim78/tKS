#ifndef CFILE_H
#define CFILE_H

#include <ActiveQt/QAxBase>
#include <ActiveQt/QAxObject>

#include <QtXml>

#include "ccity.h"
#include "cstreet.h"
#include "cstatus.h"
#include "cdiscount.h"
#include "cbase.h"
#include "cplan.h"

#include <QMessageBox>


class cfile
{
public:
    cfile();

    QAxObject *excel;
    QAxObject *wbook;
    QAxObject *book;
    QAxObject *sheets;
    QAxObject *currSheet;

    cCity *c_city;
    cStreet * c_street;
    cstatus *c_status;
    cdiscount *c_discount;
    cBase *c_base;
    cPlan * c_plan;

public slots:
    QStringList getCity(QString _fname, int _list, int _colReg, int _colCity);
    QStringList getStreet(QString _fname, int _list, int _colCity, int _colStreet);
    QStringList getBase(QString _fname, QMap<QString, QVariant> _map);
    void uploadBasetoDB(QString _fname, QMap<QString, QVariant> _map);

    void makeXMLDocumentDI(QString _fname);
    void makeJSONDocumentDI(QString _fname);

};

#endif // CFILE_H
