/********************************************************************************
** Form generated from reading UI file 'first.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRST_H
#define UI_FIRST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_first
{
public:

    void setupUi(QWidget *first)
    {
        if (first->objectName().isEmpty())
            first->setObjectName(QStringLiteral("first"));
        first->resize(743, 608);

        retranslateUi(first);

        QMetaObject::connectSlotsByName(first);
    } // setupUi

    void retranslateUi(QWidget *first)
    {
        first->setWindowTitle(QApplication::translate("first", "first", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class first: public Ui_first {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRST_H
