#ifndef FRES_H
#define FRESS_H

#include <QtGui/QMainWindow>
#include "ui_fress.h"
#include "ui_Calibration_x.h"
#include "calibration_x.h"
#include "about.h"
//Librer�as de open cv
#include "cxcore.h"
#include <highgui.h> 
#include <cv.h>
//Librerias de textos
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Fress : public QMainWindow
{
	Q_OBJECT

public:
	Fress(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Fress();

private slots:
	void on_posiciones_2_clicked();
	void on_exit_clicked();
	void about();
	void on_Start_clicked();
	void on_Stop_clicked();
	void on_Show_clicked();
	void on_Close_clicked();
	void on_calibration_clicked();
	void on_R_clicked();
	void on_G_clicked();
	void on_B_clicked();
	void on_save_clicked();
	void rvertical();
	void rhorizontal();
	void posxyz(IplImage* frame_horizontal, IplImage* frame_vertical,IplImage* imgHSVh1,IplImage* imgHSVv1, double *i, int method);
	void write(IplImage* image, string file);
	void on_Open_clicked();
	void on_set_0_clicked();
	void on_savecalib40_clicked();
	void readfile(string file);
	void writefile(string file);
	void readmodificable(string file);
	void writemodificable(string file);
	double* readint(string path);
	void read_pixel2mm();
	void camera_calibration();
	void camera_calibration2();
	void filter(IplImage* imagexy, IplImage* imagez, IplImage* imagexy_bef, IplImage* imagez_bef);
	void read_calibparam();

private:
	Ui::FressClass ui;
	Form w;		   //Par�metro para mostrar un "About" del software
	Calibration z; //Par�metro de calibraci�n
	int key;
	IplImage* frame_horizontal; //Imagen horizontal
	IplImage* frame_vertical;   //Imagen vertical
	CvCapture* capture_horizontal;  //Asignaci�n de la c�mara web horizontal
	CvCapture* capture_vertical;	//Asignaci�n de la c�mara web horizontal

	//Par�metros de rangos para filtros de colores para hacer una imagen binaria
	int h11, h12, h21, h22, s11, s12, s21, s22, v11, v12, v21, v22;

	IplImage* imgHSV; //Imagen donde se guardar� la imagen en HSV
	IplImage* imgFilteredh; //Imagen donde se guardar� la imagen filtrada
	IplImage* imgFilteredh_bef; //Imagen donde se guardar� la imagen filtrada anterior
	IplImage* imgFilteredv; //Imagen donde se guardar� la imagen filtrada
	IplImage* imgFilteredv_bef; //Imagen donde se guardar� la imagen filtrada anterior

	//Posiciones de x, y ,z de la c�mara, auxiliares de posiciones y transformaci�n de pixeles a mm
	// + correcci�n de error de que los ejes no son perfectamente correspondientes con la posici�n de la c�rmara
	double xyz[4], xyzaux[3], pixel2mm[5]; 
	ofstream position; //Archivo con la posici�n x, y, z obtenidos desde la c�mara

	//Referencias para setear a 0 las posiciones x, y, z
	double refx, refy, refz;
	int modificable;
};

#endif // FRESS_H
