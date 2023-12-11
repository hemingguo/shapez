/********************************************************************************
** Form generated from reading UI file 'second.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECOND_H
#define UI_SECOND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_second
{
public:

    void setupUi(QWidget *second)
    {
        if (second->objectName().isEmpty())
            second->setObjectName(QStringLiteral("second"));
        second->resize(600, 600);

        retranslateUi(second);

        QMetaObject::connectSlotsByName(second);
    } // setupUi

    void retranslateUi(QWidget *second)
    {
        second->setWindowTitle(QApplication::translate("second", "second", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class second: public Ui_second {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECOND_H
