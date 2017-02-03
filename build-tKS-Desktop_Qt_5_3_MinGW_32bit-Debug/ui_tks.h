/********************************************************************************
** Form generated from reading UI file 'tks.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TKS_H
#define UI_TKS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tKS
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *tKS)
    {
        if (tKS->objectName().isEmpty())
            tKS->setObjectName(QStringLiteral("tKS"));
        tKS->resize(854, 545);
        centralWidget = new QWidget(tKS);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tKS->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(tKS);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 854, 26));
        tKS->setMenuBar(menuBar);
        mainToolBar = new QToolBar(tKS);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        tKS->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(tKS);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        tKS->setStatusBar(statusBar);

        retranslateUi(tKS);

        QMetaObject::connectSlotsByName(tKS);
    } // setupUi

    void retranslateUi(QMainWindow *tKS)
    {
        tKS->setWindowTitle(QApplication::translate("tKS", "tKS", 0));
    } // retranslateUi

};

namespace Ui {
    class tKS: public Ui_tKS {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TKS_H
