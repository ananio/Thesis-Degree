/********************************************************************************
** Form generated from reading UI file 'Calibration_x.ui'
**
** Created: Tue 10. Jul 02:22:01 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIBRATION_X_H
#define UI_CALIBRATION_X_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Calibration
{
public:
    QPushButton *next;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QWidget *Calibration)
    {
        if (Calibration->objectName().isEmpty())
            Calibration->setObjectName(QString::fromUtf8("Calibration"));
        Calibration->resize(364, 167);
        Calibration->setMinimumSize(QSize(364, 167));
        Calibration->setMaximumSize(QSize(364, 167));
        next = new QPushButton(Calibration);
        next->setObjectName(QString::fromUtf8("next"));
        next->setGeometry(QRect(280, 130, 75, 23));
        lineEdit = new QLineEdit(Calibration);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(160, 130, 113, 20));
        label = new QLabel(Calibration);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 10, 301, 101));

        retranslateUi(Calibration);

        QMetaObject::connectSlotsByName(Calibration);
    } // setupUi

    void retranslateUi(QWidget *Calibration)
    {
        Calibration->setWindowTitle(QApplication::translate("Calibration", "Calibration", 0, QApplication::UnicodeUTF8));
        next->setText(QApplication::translate("Calibration", "Ok", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("Calibration", "0", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Calibration", "Esta etapa corresponde a la calibraci\303\263n. Sit\303\272e la\n"
"m\303\241quina lo m\303\241s al centro posible", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Calibration: public Ui_Calibration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATION_X_H
