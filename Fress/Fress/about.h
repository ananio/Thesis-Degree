#ifndef ABOUT_H
#define ABOUT_H

#include <QtGui/QMainWindow>
#include "ui_about.h"


class Form : public QMainWindow
{
	Q_OBJECT

public:
	Form(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Form();

private:
	Ui::Form ui;
};

#endif // ABOUT_H
