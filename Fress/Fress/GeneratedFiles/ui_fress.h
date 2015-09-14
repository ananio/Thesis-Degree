/********************************************************************************
** Form generated from reading UI file 'fress.ui'
**
** Created: Tue 10. Jul 02:22:01 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRESS_H
#define UI_FRESS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FressClass
{
public:
    QAction *actionAbout;
    QAction *action;
    QAction *actionAbout_2;
    QWidget *centralWidget;
    QGroupBox *groupBox_2;
    QLabel *label_7;
    QLineEdit *z_2;
    QLabel *label_8;
    QLineEdit *y_2;
    QLineEdit *x_2;
    QLabel *label_9;
    QRadioButton *mm;
    QRadioButton *inches;
    QGroupBox *groupBox;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QCheckBox *workingall;
    QPushButton *exit;
    QPushButton *Start;
    QPushButton *Stop;
    QGroupBox *groupBox_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *Show;
    QPushButton *Close;
    QSlider *h1;
    QSlider *s1;
    QSlider *v1;
    QSlider *h2;
    QSlider *s2;
    QSlider *v2;
    QPushButton *R;
    QPushButton *G;
    QPushButton *B;
    QRadioButton *rhorizontal;
    QRadioButton *rvertical;
    QCheckBox *workingcalibration;
    QPushButton *save;
    QLabel *label_6;
    QLabel *label_13;
    QLineEdit *thr_1;
    QLabel *label_16;
    QLineEdit *thr_2;
    QLineEdit *thr_3;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QCheckBox *filter1;
    QGroupBox *groupBox_3;
    QPushButton *Open;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QLabel *label_5;
    QGroupBox *groupBox_5;
    QLineEdit *y40e;
    QLineEdit *x40e;
    QLabel *labelalal;
    QLabel *label_10;
    QLineEdit *x40;
    QLabel *label_21;
    QLineEdit *xm40;
    QLabel *label_22;
    QLineEdit *ym40;
    QLabel *label_28;
    QLineEdit *y40;
    QLabel *label_29;
    QLineEdit *zm40;
    QLabel *label_30;
    QLineEdit *z40;
    QLabel *label_31;
    QPushButton *savecalib40;
    QCheckBox *move_correction;
    QLabel *label_11;
    QLabel *label_24;
    QLineEdit *ym40e;
    QLineEdit *xm40e;
    QPushButton *set_0;
    QPushButton *calibration;
    QGroupBox *groupBox_6;
    QSlider *brightness;
    QSlider *vbrightness;
    QLabel *label_14;
    QLabel *label_15;
    QSlider *brightness_2;
    QSlider *brightness_3;
    QLabel *label_20;
    QLabel *label_23;
    QGroupBox *groupBox_7;
    QLineEdit *f1;
    QLineEdit *f2;
    QLineEdit *f3;
    QCheckBox *plotxy;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QMenuBar *menuBar;
    QMenu *menuAbout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FressClass)
    {
        if (FressClass->objectName().isEmpty())
            FressClass->setObjectName(QString::fromUtf8("FressClass"));
        FressClass->resize(427, 650);
        FressClass->setMinimumSize(QSize(427, 650));
        FressClass->setMaximumSize(QSize(427, 650));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../Memoria/1327458073_Space_Art.ico"), QSize(), QIcon::Normal, QIcon::Off);
        FressClass->setWindowIcon(icon);
        actionAbout = new QAction(FressClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        action = new QAction(FressClass);
        action->setObjectName(QString::fromUtf8("action"));
        action->setCheckable(false);
        actionAbout_2 = new QAction(FressClass);
        actionAbout_2->setObjectName(QString::fromUtf8("actionAbout_2"));
        centralWidget = new QWidget(FressClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 40, 221, 111));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 80, 46, 13));
        z_2 = new QLineEdit(groupBox_2);
        z_2->setObjectName(QString::fromUtf8("z_2"));
        z_2->setGeometry(QRect(20, 80, 113, 20));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 20, 46, 13));
        y_2 = new QLineEdit(groupBox_2);
        y_2->setObjectName(QString::fromUtf8("y_2"));
        y_2->setGeometry(QRect(20, 50, 113, 20));
        x_2 = new QLineEdit(groupBox_2);
        x_2->setObjectName(QString::fromUtf8("x_2"));
        x_2->setGeometry(QRect(20, 20, 113, 21));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 50, 46, 13));
        mm = new QRadioButton(groupBox_2);
        mm->setObjectName(QString::fromUtf8("mm"));
        mm->setGeometry(QRect(150, 20, 82, 17));
        mm->setChecked(true);
        inches = new QRadioButton(groupBox_2);
        inches->setObjectName(QString::fromUtf8("inches"));
        inches->setGeometry(QRect(150, 40, 82, 17));
        inches->setChecked(false);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(250, 40, 141, 111));
        checkBox_4 = new QCheckBox(groupBox);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(30, 50, 70, 17));
        checkBox_4->setChecked(true);
        checkBox_5 = new QCheckBox(groupBox);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setGeometry(QRect(30, 80, 70, 17));
        checkBox_5->setChecked(true);
        workingall = new QCheckBox(groupBox);
        workingall->setObjectName(QString::fromUtf8("workingall"));
        workingall->setEnabled(false);
        workingall->setGeometry(QRect(10, 20, 70, 17));
        exit = new QPushButton(centralWidget);
        exit->setObjectName(QString::fromUtf8("exit"));
        exit->setGeometry(QRect(300, 570, 75, 23));
        Start = new QPushButton(centralWidget);
        Start->setObjectName(QString::fromUtf8("Start"));
        Start->setGeometry(QRect(130, 570, 75, 23));
        Stop = new QPushButton(centralWidget);
        Stop->setObjectName(QString::fromUtf8("Stop"));
        Stop->setGeometry(QRect(220, 570, 75, 23));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(20, 260, 371, 161));
        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(250, 40, 46, 13));
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(250, 60, 46, 13));
        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(250, 80, 46, 13));
        Show = new QPushButton(groupBox_4);
        Show->setObjectName(QString::fromUtf8("Show"));
        Show->setGeometry(QRect(270, 70, 81, 23));
        Close = new QPushButton(groupBox_4);
        Close->setObjectName(QString::fromUtf8("Close"));
        Close->setGeometry(QRect(270, 130, 81, 23));
        h1 = new QSlider(groupBox_4);
        h1->setObjectName(QString::fromUtf8("h1"));
        h1->setGeometry(QRect(10, 40, 111, 19));
        h1->setMouseTracking(false);
        h1->setAutoFillBackground(false);
        h1->setMinimum(-1);
        h1->setMaximum(256);
        h1->setValue(26);
        h1->setOrientation(Qt::Horizontal);
        h1->setInvertedAppearance(false);
        h1->setInvertedControls(false);
        h1->setTickPosition(QSlider::NoTicks);
        s1 = new QSlider(groupBox_4);
        s1->setObjectName(QString::fromUtf8("s1"));
        s1->setGeometry(QRect(10, 60, 111, 19));
        s1->setMinimum(-1);
        s1->setMaximum(256);
        s1->setValue(87);
        s1->setOrientation(Qt::Horizontal);
        v1 = new QSlider(groupBox_4);
        v1->setObjectName(QString::fromUtf8("v1"));
        v1->setGeometry(QRect(10, 80, 111, 19));
        v1->setMinimum(-1);
        v1->setMaximum(256);
        v1->setValue(123);
        v1->setOrientation(Qt::Horizontal);
        h2 = new QSlider(groupBox_4);
        h2->setObjectName(QString::fromUtf8("h2"));
        h2->setGeometry(QRect(130, 40, 111, 19));
        h2->setMouseTracking(false);
        h2->setMinimum(-1);
        h2->setMaximum(256);
        h2->setValue(96);
        h2->setOrientation(Qt::Horizontal);
        s2 = new QSlider(groupBox_4);
        s2->setObjectName(QString::fromUtf8("s2"));
        s2->setGeometry(QRect(130, 60, 111, 19));
        s2->setMinimum(-1);
        s2->setMaximum(256);
        s2->setValue(199);
        s2->setOrientation(Qt::Horizontal);
        v2 = new QSlider(groupBox_4);
        v2->setObjectName(QString::fromUtf8("v2"));
        v2->setGeometry(QRect(130, 80, 111, 19));
        v2->setMinimum(-1);
        v2->setMaximum(256);
        v2->setValue(255);
        v2->setOrientation(Qt::Horizontal);
        R = new QPushButton(groupBox_4);
        R->setObjectName(QString::fromUtf8("R"));
        R->setGeometry(QRect(270, 40, 21, 23));
        G = new QPushButton(groupBox_4);
        G->setObjectName(QString::fromUtf8("G"));
        G->setGeometry(QRect(300, 40, 21, 23));
        B = new QPushButton(groupBox_4);
        B->setObjectName(QString::fromUtf8("B"));
        B->setGeometry(QRect(330, 40, 21, 23));
        rhorizontal = new QRadioButton(groupBox_4);
        rhorizontal->setObjectName(QString::fromUtf8("rhorizontal"));
        rhorizontal->setGeometry(QRect(270, 10, 82, 17));
        rhorizontal->setChecked(true);
        rvertical = new QRadioButton(groupBox_4);
        rvertical->setObjectName(QString::fromUtf8("rvertical"));
        rvertical->setGeometry(QRect(210, 10, 82, 17));
        workingcalibration = new QCheckBox(groupBox_4);
        workingcalibration->setObjectName(QString::fromUtf8("workingcalibration"));
        workingcalibration->setEnabled(false);
        workingcalibration->setGeometry(QRect(10, 100, 70, 17));
        save = new QPushButton(groupBox_4);
        save->setObjectName(QString::fromUtf8("save"));
        save->setGeometry(QRect(270, 100, 81, 23));
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 20, 46, 13));
        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(130, 20, 46, 13));
        thr_1 = new QLineEdit(groupBox_4);
        thr_1->setObjectName(QString::fromUtf8("thr_1"));
        thr_1->setGeometry(QRect(220, 130, 31, 20));
        label_16 = new QLabel(groupBox_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(140, 110, 61, 16));
        thr_2 = new QLineEdit(groupBox_4);
        thr_2->setObjectName(QString::fromUtf8("thr_2"));
        thr_2->setGeometry(QRect(160, 130, 31, 20));
        thr_3 = new QLineEdit(groupBox_4);
        thr_3->setObjectName(QString::fromUtf8("thr_3"));
        thr_3->setGeometry(QRect(100, 130, 31, 20));
        label_17 = new QLabel(groupBox_4);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(90, 130, 46, 13));
        label_18 = new QLabel(groupBox_4);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(150, 130, 46, 13));
        label_19 = new QLabel(groupBox_4);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(210, 130, 46, 13));
        filter1 = new QCheckBox(groupBox_4);
        filter1->setObjectName(QString::fromUtf8("filter1"));
        filter1->setGeometry(QRect(10, 130, 81, 17));
        filter1->setChecked(true);
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 150, 371, 51));
        Open = new QPushButton(groupBox_3);
        Open->setObjectName(QString::fromUtf8("Open"));
        Open->setGeometry(QRect(280, 20, 75, 23));
        lineEdit = new QLineEdit(groupBox_3);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(30, 20, 241, 20));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 20, 46, 13));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 20, 46, 13));
        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(20, 420, 371, 141));
        y40e = new QLineEdit(groupBox_5);
        y40e->setObjectName(QString::fromUtf8("y40e"));
        y40e->setGeometry(QRect(260, 20, 31, 20));
        x40e = new QLineEdit(groupBox_5);
        x40e->setObjectName(QString::fromUtf8("x40e"));
        x40e->setGeometry(QRect(260, 50, 31, 20));
        labelalal = new QLabel(groupBox_5);
        labelalal->setObjectName(QString::fromUtf8("labelalal"));
        labelalal->setGeometry(QRect(240, 50, 46, 13));
        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(240, 20, 46, 13));
        x40 = new QLineEdit(groupBox_5);
        x40->setObjectName(QString::fromUtf8("x40"));
        x40->setGeometry(QRect(100, 20, 51, 20));
        label_21 = new QLabel(groupBox_5);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(80, 20, 46, 13));
        xm40 = new QLineEdit(groupBox_5);
        xm40->setObjectName(QString::fromUtf8("xm40"));
        xm40->setGeometry(QRect(180, 20, 51, 20));
        label_22 = new QLabel(groupBox_5);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(160, 20, 46, 13));
        ym40 = new QLineEdit(groupBox_5);
        ym40->setObjectName(QString::fromUtf8("ym40"));
        ym40->setGeometry(QRect(180, 50, 51, 20));
        label_28 = new QLabel(groupBox_5);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(80, 50, 46, 13));
        y40 = new QLineEdit(groupBox_5);
        y40->setObjectName(QString::fromUtf8("y40"));
        y40->setGeometry(QRect(100, 50, 51, 20));
        label_29 = new QLabel(groupBox_5);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(160, 50, 46, 13));
        zm40 = new QLineEdit(groupBox_5);
        zm40->setObjectName(QString::fromUtf8("zm40"));
        zm40->setGeometry(QRect(180, 80, 51, 20));
        label_30 = new QLabel(groupBox_5);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(80, 80, 46, 13));
        z40 = new QLineEdit(groupBox_5);
        z40->setObjectName(QString::fromUtf8("z40"));
        z40->setGeometry(QRect(100, 80, 51, 20));
        label_31 = new QLabel(groupBox_5);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(160, 80, 46, 13));
        savecalib40 = new QPushButton(groupBox_5);
        savecalib40->setObjectName(QString::fromUtf8("savecalib40"));
        savecalib40->setGeometry(QRect(230, 110, 75, 23));
        move_correction = new QCheckBox(groupBox_5);
        move_correction->setObjectName(QString::fromUtf8("move_correction"));
        move_correction->setGeometry(QRect(30, 110, 181, 17));
        move_correction->setChecked(true);
        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(300, 20, 46, 13));
        label_24 = new QLabel(groupBox_5);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(300, 50, 46, 13));
        ym40e = new QLineEdit(groupBox_5);
        ym40e->setObjectName(QString::fromUtf8("ym40e"));
        ym40e->setGeometry(QRect(330, 20, 31, 20));
        xm40e = new QLineEdit(groupBox_5);
        xm40e->setObjectName(QString::fromUtf8("xm40e"));
        xm40e->setGeometry(QRect(330, 50, 31, 20));
        set_0 = new QPushButton(groupBox_5);
        set_0->setObjectName(QString::fromUtf8("set_0"));
        set_0->setGeometry(QRect(10, 20, 61, 23));
        calibration = new QPushButton(groupBox_5);
        calibration->setObjectName(QString::fromUtf8("calibration"));
        calibration->setGeometry(QRect(10, 50, 61, 23));
        groupBox_6 = new QGroupBox(centralWidget);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(20, 200, 371, 61));
        brightness = new QSlider(groupBox_6);
        brightness->setObjectName(QString::fromUtf8("brightness"));
        brightness->setGeometry(QRect(180, 40, 71, 20));
        brightness->setMouseTracking(false);
        brightness->setAutoFillBackground(false);
        brightness->setMinimum(-128);
        brightness->setMaximum(128);
        brightness->setValue(0);
        brightness->setOrientation(Qt::Horizontal);
        brightness->setInvertedAppearance(false);
        brightness->setInvertedControls(false);
        brightness->setTickPosition(QSlider::NoTicks);
        vbrightness = new QSlider(groupBox_6);
        vbrightness->setObjectName(QString::fromUtf8("vbrightness"));
        vbrightness->setGeometry(QRect(280, 40, 81, 20));
        vbrightness->setMouseTracking(false);
        vbrightness->setAutoFillBackground(false);
        vbrightness->setMinimum(-128);
        vbrightness->setMaximum(128);
        vbrightness->setValue(0);
        vbrightness->setOrientation(Qt::Horizontal);
        vbrightness->setInvertedAppearance(false);
        vbrightness->setInvertedControls(false);
        vbrightness->setTickPosition(QSlider::NoTicks);
        label_14 = new QLabel(groupBox_6);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(170, 20, 91, 20));
        label_15 = new QLabel(groupBox_6);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(270, 20, 91, 20));
        brightness_2 = new QSlider(groupBox_6);
        brightness_2->setObjectName(QString::fromUtf8("brightness_2"));
        brightness_2->setGeometry(QRect(10, 40, 71, 20));
        brightness_2->setMouseTracking(false);
        brightness_2->setAutoFillBackground(false);
        brightness_2->setMinimum(-13);
        brightness_2->setMaximum(-1);
        brightness_2->setValue(-5);
        brightness_2->setOrientation(Qt::Horizontal);
        brightness_2->setInvertedAppearance(false);
        brightness_2->setInvertedControls(false);
        brightness_2->setTickPosition(QSlider::NoTicks);
        brightness_3 = new QSlider(groupBox_6);
        brightness_3->setObjectName(QString::fromUtf8("brightness_3"));
        brightness_3->setGeometry(QRect(90, 40, 71, 20));
        brightness_3->setMouseTracking(false);
        brightness_3->setAutoFillBackground(false);
        brightness_3->setMinimum(-13);
        brightness_3->setMaximum(-1);
        brightness_3->setValue(-5);
        brightness_3->setOrientation(Qt::Horizontal);
        brightness_3->setInvertedAppearance(false);
        brightness_3->setInvertedControls(false);
        brightness_3->setTickPosition(QSlider::NoTicks);
        label_20 = new QLabel(groupBox_6);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(20, 20, 71, 16));
        label_23 = new QLabel(groupBox_6);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(90, 20, 71, 16));
        groupBox_7 = new QGroupBox(centralWidget);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(20, 0, 371, 41));
        f1 = new QLineEdit(groupBox_7);
        f1->setObjectName(QString::fromUtf8("f1"));
        f1->setGeometry(QRect(150, 10, 21, 21));
        f2 = new QLineEdit(groupBox_7);
        f2->setObjectName(QString::fromUtf8("f2"));
        f2->setGeometry(QRect(240, 10, 21, 21));
        f3 = new QLineEdit(groupBox_7);
        f3->setObjectName(QString::fromUtf8("f3"));
        f3->setGeometry(QRect(320, 10, 21, 21));
        plotxy = new QCheckBox(groupBox_7);
        plotxy->setObjectName(QString::fromUtf8("plotxy"));
        plotxy->setGeometry(QRect(30, 10, 70, 17));
        plotxy->setChecked(true);
        label_25 = new QLabel(groupBox_7);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(110, 10, 61, 16));
        label_26 = new QLabel(groupBox_7);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(190, 10, 61, 16));
        label_27 = new QLabel(groupBox_7);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(270, 10, 61, 16));
        f1->raise();
        f2->raise();
        f3->raise();
        plotxy->raise();
        label_25->raise();
        label_26->raise();
        groupBox_2->raise();
        label_27->raise();
        FressClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FressClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 427, 20));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        FressClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FressClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(false);
        mainToolBar->setMinimumSize(QSize(427, 12));
        FressClass->addToolBar(Qt::BottomToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FressClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        FressClass->setStatusBar(statusBar);

        menuBar->addAction(menuAbout->menuAction());
        menuAbout->addAction(actionAbout_2);

        retranslateUi(FressClass);

        QMetaObject::connectSlotsByName(FressClass);
    } // setupUi

    void retranslateUi(QMainWindow *FressClass)
    {
        FressClass->setWindowTitle(QApplication::translate("FressClass", "Fress", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("FressClass", "About", 0, QApplication::UnicodeUTF8));
        action->setText(QApplication::translate("FressClass", "About...", 0, QApplication::UnicodeUTF8));
        actionAbout_2->setText(QApplication::translate("FressClass", "About...", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("FressClass", "Position", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FressClass", "z", 0, QApplication::UnicodeUTF8));
        z_2->setText(QApplication::translate("FressClass", "0", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("FressClass", "x", 0, QApplication::UnicodeUTF8));
        y_2->setText(QApplication::translate("FressClass", "0", 0, QApplication::UnicodeUTF8));
        x_2->setText(QApplication::translate("FressClass", "0", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("FressClass", "y", 0, QApplication::UnicodeUTF8));
        mm->setText(QApplication::translate("FressClass", "mm", 0, QApplication::UnicodeUTF8));
        inches->setText(QApplication::translate("FressClass", "inches", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("FressClass", "Show position", 0, QApplication::UnicodeUTF8));
        checkBox_4->setText(QApplication::translate("FressClass", "Horizontal", 0, QApplication::UnicodeUTF8));
        checkBox_5->setText(QApplication::translate("FressClass", "Vertical", 0, QApplication::UnicodeUTF8));
        workingall->setText(QApplication::translate("FressClass", "Working...", 0, QApplication::UnicodeUTF8));
        exit->setText(QApplication::translate("FressClass", "Exit", 0, QApplication::UnicodeUTF8));
        Start->setText(QApplication::translate("FressClass", "Start", 0, QApplication::UnicodeUTF8));
        Stop->setText(QApplication::translate("FressClass", "Stop", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("FressClass", "Color calibration", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FressClass", "h", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FressClass", "s", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FressClass", "v", 0, QApplication::UnicodeUTF8));
        Show->setText(QApplication::translate("FressClass", "Show", 0, QApplication::UnicodeUTF8));
        Close->setText(QApplication::translate("FressClass", "Close", 0, QApplication::UnicodeUTF8));
        R->setText(QApplication::translate("FressClass", "R", 0, QApplication::UnicodeUTF8));
        G->setText(QApplication::translate("FressClass", "G", 0, QApplication::UnicodeUTF8));
        B->setText(QApplication::translate("FressClass", "B", 0, QApplication::UnicodeUTF8));
        rhorizontal->setText(QApplication::translate("FressClass", "Horizontal", 0, QApplication::UnicodeUTF8));
        rvertical->setText(QApplication::translate("FressClass", "Vertical", 0, QApplication::UnicodeUTF8));
        workingcalibration->setText(QApplication::translate("FressClass", "Working...", 0, QApplication::UnicodeUTF8));
        save->setText(QApplication::translate("FressClass", "Save", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FressClass", "Min", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("FressClass", "Max", 0, QApplication::UnicodeUTF8));
        thr_1->setText(QApplication::translate("FressClass", "35", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("FressClass", "Threshold", 0, QApplication::UnicodeUTF8));
        thr_2->setText(QApplication::translate("FressClass", "20", 0, QApplication::UnicodeUTF8));
        thr_3->setText(QApplication::translate("FressClass", "10", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("FressClass", "H", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("FressClass", "S", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("FressClass", "V", 0, QApplication::UnicodeUTF8));
        filter1->setText(QApplication::translate("FressClass", "Undistorted", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("FressClass", "Communication file", 0, QApplication::UnicodeUTF8));
        Open->setText(QApplication::translate("FressClass", "Open...", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("FressClass", "C:\\Mach3\\position.txt", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FressClass", "File", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FressClass", "File", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("FressClass", "Parameters calibration", 0, QApplication::UnicodeUTF8));
        y40e->setInputMask(QString());
        y40e->setText(QApplication::translate("FressClass", "0", 0, QApplication::UnicodeUTF8));
        x40e->setText(QApplication::translate("FressClass", "0", 0, QApplication::UnicodeUTF8));
        labelalal->setText(QApplication::translate("FressClass", "xe", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("FressClass", "ye", 0, QApplication::UnicodeUTF8));
        x40->setInputMask(QString());
        x40->setText(QApplication::translate("FressClass", "0", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("FressClass", "x", 0, QApplication::UnicodeUTF8));
        xm40->setInputMask(QString());
        xm40->setText(QApplication::translate("FressClass", "0", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("FressClass", "-x", 0, QApplication::UnicodeUTF8));
        ym40->setInputMask(QString());
        ym40->setText(QApplication::translate("FressClass", "0", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("FressClass", "y", 0, QApplication::UnicodeUTF8));
        y40->setInputMask(QString());
        y40->setText(QApplication::translate("FressClass", "0", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("FressClass", "-y", 0, QApplication::UnicodeUTF8));
        zm40->setInputMask(QString());
        zm40->setText(QApplication::translate("FressClass", "0", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("FressClass", "z", 0, QApplication::UnicodeUTF8));
        z40->setInputMask(QString());
        z40->setText(QApplication::translate("FressClass", "0", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("FressClass", "-z", 0, QApplication::UnicodeUTF8));
        savecalib40->setText(QApplication::translate("FressClass", "Save", 0, QApplication::UnicodeUTF8));
        move_correction->setText(QApplication::translate("FressClass", "Move correction", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("FressClass", "-ye", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("FressClass", "-xe", 0, QApplication::UnicodeUTF8));
        ym40e->setInputMask(QString());
        ym40e->setText(QApplication::translate("FressClass", "0", 0, QApplication::UnicodeUTF8));
        xm40e->setText(QApplication::translate("FressClass", "0", 0, QApplication::UnicodeUTF8));
        set_0->setText(QApplication::translate("FressClass", "Set 0", 0, QApplication::UnicodeUTF8));
        calibration->setText(QApplication::translate("FressClass", "Calibration", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("FressClass", "Camera calibration", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("FressClass", "Horizonal Brightness", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("FressClass", "Vertical Brightness", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("FressClass", "Exposition 1", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("FressClass", "Exposition 2", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("FressClass", "Filter", 0, QApplication::UnicodeUTF8));
        f1->setText(QApplication::translate("FressClass", "1", 0, QApplication::UnicodeUTF8));
        f2->setText(QApplication::translate("FressClass", "0", 0, QApplication::UnicodeUTF8));
        f3->setText(QApplication::translate("FressClass", "0", 0, QApplication::UnicodeUTF8));
        plotxy->setText(QApplication::translate("FressClass", "Plot_xyz", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("FressClass", "Imagen", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("FressClass", "Imagen-1", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("FressClass", "Imagen-2", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("FressClass", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FressClass: public Ui_FressClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRESS_H
