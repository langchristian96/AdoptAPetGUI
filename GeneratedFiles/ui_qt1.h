/********************************************************************************
** Form generated from reading UI file 'qt1.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT1_H
#define UI_QT1_H

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

class Ui_QT1Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QT1Class)
    {
        if (QT1Class->objectName().isEmpty())
            QT1Class->setObjectName(QStringLiteral("QT1Class"));
        QT1Class->resize(600, 400);
        menuBar = new QMenuBar(QT1Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QT1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QT1Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QT1Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(QT1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QT1Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QT1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QT1Class->setStatusBar(statusBar);

        retranslateUi(QT1Class);

        QMetaObject::connectSlotsByName(QT1Class);
    } // setupUi

    void retranslateUi(QMainWindow *QT1Class)
    {
        QT1Class->setWindowTitle(QApplication::translate("QT1Class", "QT1", 0));
    } // retranslateUi

};

namespace Ui {
    class QT1Class: public Ui_QT1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT1_H
