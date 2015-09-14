#ifndef CALIBRATION_X_H
#define CALIBRATION_X_H

#include <QtGui/QMainWindow>
#include <ui_Calibration_x.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Calibration : public QMainWindow
{
	Q_OBJECT

public:
	Calibration(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Calibration();
	double* pixel2mm;  //Parámetros de transformación de pixeles de mm
	double xyz_ini[4]; //Posiciones iniciales de calibracion
	double pos;		   //Variables auxiliares

	void setXYZ(double* xyz_s);
	void setPixel2mm(double* pixel2mm_ui);
	void writepixel2mm(string path);
	void calibration1();

private slots:
	void on_next_clicked();

private:
	Ui::Calibration ui;
	int i;
	double* xyz;
	double distance;
};

#endif // CALIBRATION_X_H
