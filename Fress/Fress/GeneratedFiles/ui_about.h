/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created: Tue 10. Jul 02:22:00 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(183, 97);
        Form->setMinimumSize(QSize(183, 97));
        Form->setMaximumSize(QSize(183, 97));
        label = new QLabel(Form);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 70, 46, 13));
        label->setMinimumSize(QSize(46, 13));
        label->setMaximumSize(QSize(46, 13));
        label_2 = new QLabel(Form);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 30, 201, 16));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form", "2012", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Form", "Made by Andres Anania...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
