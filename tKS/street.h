#ifndef STREET_H
#define STREET_H

#include <QWidget>
#include <QFileDialog>

#include "cfile.h"
#include "ccity.h"
#include "cstreet.h"
#include "cbase.h"

namespace Ui {
class street;
}

class street : public QWidget
{
    Q_OBJECT

public:
    explicit street(QWidget *parent = 0);
    ~street();

    cfile *c_file;
    cCity *c_city;
    cStreet *c_street;
    cBase *c_base;

private:
    Ui::street *ui;

public slots:
    void uploadCity();
    void uploadStreet();
    void uploadBase();

    void makeDI();
    void makeDI_JSON();
    void makeDITV_JSON();
    void makeAll_JSON();
};

#endif // STREET_H
