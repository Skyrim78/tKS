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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_street
{
public:
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_4;
    QToolButton *toolButton;
    QPushButton *pushButton_make;
    QPushButton *pushButton_getBase;
    QPushButton *pushButton_makeJSON;

    void setupUi(QWidget *street)
    {
        if (street->objectName().isEmpty())
            street->setObjectName(QStringLiteral("street"));
        street->resize(615, 491);
        groupBox = new QGroupBox(street);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(100, 10, 490, 125));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_3->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_3->addWidget(pushButton_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_3->addWidget(pushButton_4);

        toolButton = new QToolButton(groupBox);
        toolButton->setObjectName(QStringLiteral("toolButton"));

        horizontalLayout_3->addWidget(toolButton);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        pushButton_make = new QPushButton(street);
        pushButton_make->setObjectName(QStringLiteral("pushButton_make"));
        pushButton_make->setGeometry(QRect(470, 200, 93, 28));
        pushButton_getBase = new QPushButton(street);
        pushButton_getBase->setObjectName(QStringLiteral("pushButton_getBase"));
        pushButton_getBase->setGeometry(QRect(350, 200, 93, 28));
        pushButton_makeJSON = new QPushButton(street);
        pushButton_makeJSON->setObjectName(QStringLiteral("pushButton_makeJSON"));
        pushButton_makeJSON->setGeometry(QRect(470, 230, 93, 28));

        retranslateUi(street);

        QMetaObject::connectSlotsByName(street);
    } // setupUi

    void retranslateUi(QWidget *street)
    {
        street->setWindowTitle(QApplication::translate("street", "Form", 0));
        groupBox->setTitle(QApplication::translate("street", "GroupBox", 0));
        label->setText(QApplication::translate("street", "TextLabel", 0));
        label_2->setText(QApplication::translate("street", "TextLabel", 0));
        pushButton->setText(QApplication::translate("street", "PushButton", 0));
        pushButton_2->setText(QApplication::translate("street", "PushButton", 0));
        pushButton_3->setText(QApplication::translate("street", "PushButton", 0));
        pushButton_4->setText(QApplication::translate("street", "PushButton", 0));
        toolButton->setText(QApplication::translate("street", "...", 0));
        pushButton_make->setText(QApplication::translate("street", "make XML", 0));
        pushButton_getBase->setText(QApplication::translate("street", "get Base", 0));
        pushButton_makeJSON->setText(QApplication::translate("street", "make JSON", 0));
    } // retranslateUi

};

namespace Ui {
    class street: public Ui_street {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STREET_H
