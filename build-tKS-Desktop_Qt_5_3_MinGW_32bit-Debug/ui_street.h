/********************************************************************************
** Form generated from reading UI file 'street.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STREET_H
#define UI_STREET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_street
{
public:
    QPushButton *pushButton_make;
    QPushButton *pushButton_getBase;
    QPushButton *pushButton_makeJSON_1;
    QPushButton *pushButton_upStreet;
    QPushButton *pushButton_upCity;
    QPushButton *pushButton_makeJSON_2;
    QPushButton *pushButton_makeJSON_3;

    void setupUi(QWidget *street)
    {
        if (street->objectName().isEmpty())
            street->setObjectName(QStringLiteral("street"));
        street->resize(615, 491);
        pushButton_make = new QPushButton(street);
        pushButton_make->setObjectName(QStringLiteral("pushButton_make"));
        pushButton_make->setGeometry(QRect(470, 200, 93, 28));
        pushButton_getBase = new QPushButton(street);
        pushButton_getBase->setObjectName(QStringLiteral("pushButton_getBase"));
        pushButton_getBase->setGeometry(QRect(90, 100, 93, 28));
        pushButton_makeJSON_1 = new QPushButton(street);
        pushButton_makeJSON_1->setObjectName(QStringLiteral("pushButton_makeJSON_1"));
        pushButton_makeJSON_1->setGeometry(QRect(342, 230, 221, 28));
        pushButton_upStreet = new QPushButton(street);
        pushButton_upStreet->setObjectName(QStringLiteral("pushButton_upStreet"));
        pushButton_upStreet->setGeometry(QRect(90, 20, 93, 28));
        pushButton_upCity = new QPushButton(street);
        pushButton_upCity->setObjectName(QStringLiteral("pushButton_upCity"));
        pushButton_upCity->setGeometry(QRect(90, 60, 93, 28));
        pushButton_makeJSON_2 = new QPushButton(street);
        pushButton_makeJSON_2->setObjectName(QStringLiteral("pushButton_makeJSON_2"));
        pushButton_makeJSON_2->setGeometry(QRect(340, 270, 221, 28));
        pushButton_makeJSON_3 = new QPushButton(street);
        pushButton_makeJSON_3->setObjectName(QStringLiteral("pushButton_makeJSON_3"));
        pushButton_makeJSON_3->setGeometry(QRect(340, 310, 221, 28));

        retranslateUi(street);

        QMetaObject::connectSlotsByName(street);
    } // setupUi

    void retranslateUi(QWidget *street)
    {
        street->setWindowTitle(QApplication::translate("street", "Form", 0));
        pushButton_make->setText(QApplication::translate("street", "make XML", 0));
        pushButton_getBase->setText(QApplication::translate("street", "upload Base", 0));
        pushButton_makeJSON_1->setText(QApplication::translate("street", "make JSON - HomeInternet", 0));
        pushButton_upStreet->setText(QApplication::translate("street", "upload Street", 0));
        pushButton_upCity->setText(QApplication::translate("street", "upload City", 0));
        pushButton_makeJSON_2->setText(QApplication::translate("street", "make JSON - HomeInternet + TV", 0));
        pushButton_makeJSON_3->setText(QApplication::translate("street", "make JSON - All", 0));
    } // retranslateUi

};

namespace Ui {
    class street: public Ui_street {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STREET_H
