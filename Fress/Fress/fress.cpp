#include "fress.h"
#include "about.h"
#include <string>
#include <ctime>
#include <QtGui\qfiledialog.h>
#include <strmif.h>
#include <dshow.h>
#include <Ks.h>				// Required by KsMedia.h
#include <KsMedia.h>		// For KSPROPERTY_CAMERACONTROL_FLAGS_*

using std::ofstream;

/**
* Función para seleccionar colores con clicks
*
* int event: Parámetro de eventos
* int x: Posición x en pixeles de selección
* int y: Posición y en pixeles de selección 
* int flags: Marcación 
* void* param: Memoria de parámetros
*
**/
void mouseHandler(int event, int x, int y, int flags, void* param);

/**
* Función que lee parámetros de un csv
**/
void lastposition();

//Función que no sirve debido al largo lapso de tiempo que utiliza (promedio de 20 posiciones)
double mean_all(double arreglo[20],int cant_prom);

//Parámetros para estimar el centroide, el de mejor resultado es el 1
int method = 1, sigmagaussxy=100, sigmagaussz=100; //Método para determinar la posicion, y sigmas de la gaussiana que se utiliza

//Ponderación de imágenes (Se hace directamente sobre el software
double ponderacion1=0.4, ponderacion2=0.3, ponderacion3=0.3; //Ponderaciones del filtro de tiempo 

//Parámetros delta de la selección de colores a través del click
int thr_1 = 10, thr_2 = 20, thr_3 = 80;

//Parámetros de rangos de colores
int h11z=0, h12z=0, s11z=0, s12z=0, v11z=0, v12z=0;

//Variables booleanas para activar y desactivar filtros
bool flag_thrz = false, flag_fxyz = false,
	flag_calibration = true, flag_gauss_filter = true, erode = true;

//Parámetros de filtros gaussianos, de eliminación y de dilatacion de bordes
int gauss1 = 5, gauss2 = 5, cant_erode = 4, cant_dilate = 2;

//Parámetro de transformación de mm a pies
const double mm2inches = 0.0393700787;

//
double pixel2mm_x, pixel2mm_y, pixel2mm_z, pixel2mm_rep[5], calibparam[10] = {0};

//Parámetros de distorción del lente de la cámara horizontal
CvMat *intrinsic = NULL, *distortion = NULL;

//Mapas con distorciones del lente horizontal
IplImage* mapx, *mapy;

//Variables auxliares de posición y poisición inicial de calibración
double xyzr[3], xyz_ini[4];

//Histórico de posiciones
double pos_xyz_h[4][20] = {0}; //Posición XYZ historico

//Posiciones del mach3
float xmach1, xmach2, ymach1, ymach2, zmach1, zmach2;

//Posiciones de la cámara
float xcam1, xcam2, ycam1, ycam2, zcam1, zcam2;

/**
* Constructor que inicializa las variables
*
* QWidget *parent, Qt::WFlags flags: Parámetros internos de QT
**/
Fress::Fress(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	
	//Configuracion QT4
	ui.setupUi(this);

	xmach1=0; 
	xmach2=0; 
	ymach1=0; 
	ymach2=0; 
	zmach1=0; 
	zmach2=0;
	xcam1=0; 
	xcam2=0; 
	ycam1=0; 
	ycam2=0; 
	zcam1=0; 
	zcam2=0;

	h11 = ui.h1->value();
	h12 = ui.h2->value();
	s11 = ui.s1->value();
	s12 = ui.s2->value();
	v11 = ui.v1->value();
	v12 = ui.v2->value();

	s21 = ui.s1->value();
	s22 = ui.s2->value();
	h21 = ui.h1->value();
	h22 = ui.h2->value();
	v21 = ui.v1->value();
	v22 = ui.v2->value();

	readfile("datos.csv");

	refx = 0;
	refy = 0;
	refz = 0;

	xyz[0] = 0;
	xyz[1] = 0;
	xyz[2] = 0; 

    xyzr[0] = 0;
	xyzr[1] = 0;
	xyzr[2] = 0; 

	xyzaux[0] = 0;
	xyzaux[1] = 0;
	xyzaux[2] = 0; 

	read_pixel2mm();

	z.setXYZ(xyzr);
	z.setPixel2mm(pixel2mm);
	read_calibparam();

	intrinsic = (CvMat*)cvLoad("C:\\Mach3\\Intrinsics.xml");
	distortion = (CvMat*)cvLoad("C:\\Mach3\\Distortion.xml");

	//Conecta al hace click
	connect(ui.actionAbout_2, SIGNAL(triggered()), this, SLOT(about())); 
	connect(ui.rhorizontal, SIGNAL(clicked()), this, SLOT(rhorizontal())); 
	connect(ui.rvertical, SIGNAL(clicked()), this, SLOT(rvertical()));
	/*
	connect(ui.rhorizontal, SIGNAL(clicked()), this, SLOT(rhorizontal())); 
	connect(ui.rvertical, SIGNAL(clicked()), this, SLOT(rvertical())); 
	*/
}

Fress::~Fress()
{

}

/**
* Funcion que activa el boton "Refrescar"
*/
void Fress::on_posiciones_2_clicked(){
	close();
}

/**
* Funcion para cerrar el programa
*/
void Fress::on_exit_clicked(){
	ui.workingall->setChecked(0);
	ui.workingcalibration->setChecked(0);
	close();
}

/**
* Funcion que muestra la pantalla about
*/
void Fress::about(){
	w.show();
}

/**
* Funcion que activa el boton Start y que abre las cámaras, estima la pocisión del punto 
* y genera la posición final relativa en mm
*/
void Fress::on_Start_clicked(){
	clock_t start;
	if(!ui.workingall->checkState() && !ui.workingcalibration->checkState()){
		ui.workingall->setChecked(1);
		//Inicializacion de parametros de las camaras

		IplImage* medicionxy, *medicionz;

		frame_horizontal = NULL;
		frame_vertical = NULL;
		capture_horizontal = NULL;
		capture_vertical = NULL;
		
		xyz[0] = ui.x_2->text().toDouble();
		xyz[1] = ui.y_2->text().toDouble();
		xyz[2] = ui.z_2->text().toDouble();

		IplImage *destination = NULL;

		while(capture_horizontal == NULL) capture_horizontal = cvCaptureFromCAM(0);
		while(capture_vertical == NULL) capture_vertical = cvCaptureFromCAM(1);
		
		cvSetCaptureProperty( capture_horizontal, CV_CAP_PROP_FRAME_WIDTH, 1280 );
		cvSetCaptureProperty( capture_horizontal, CV_CAP_PROP_FRAME_HEIGHT, 1024 );

		cvSetCaptureProperty( capture_vertical, CV_CAP_PROP_FRAME_WIDTH, 1280 );
		cvSetCaptureProperty( capture_vertical, CV_CAP_PROP_FRAME_HEIGHT, 1024 );
		
		cvNamedWindow( "Horizontal", 1 );
		cvNamedWindow( "Vertical", 1 );
		double xm=0, ym=0, zm=0;

		if(capture_horizontal && capture_vertical){

			frame_horizontal = cvQueryFrame( capture_horizontal );
			imgHSV = cvCreateImage( cvGetSize(frame_horizontal), frame_horizontal->depth, 3 ); 

			medicionxy = cvCreateImage( cvGetSize(frame_horizontal), frame_horizontal->depth, 3 );
			medicionz = cvCreateImage( cvGetSize(frame_horizontal), frame_horizontal->depth, 3 );

			imgFilteredh = cvCreateImage( cvGetSize(frame_horizontal), frame_horizontal->depth, 1 ); 
			imgFilteredv = cvCreateImage( cvGetSize(frame_horizontal), frame_horizontal->depth, 1 ); 
			imgFilteredh_bef = cvCreateImage( cvGetSize(frame_horizontal), frame_horizontal->depth, 1 ); 
			imgFilteredv_bef = cvCreateImage( cvGetSize(frame_horizontal), frame_horizontal->depth, 1 ); 
			IplImage* imagexy, *imagexy2, *imagexy3;
			IplImage* imagez, *imagez2, *imagez3;

			IplImage* imgHSVv = cvCreateImage( cvGetSize(frame_horizontal), frame_horizontal->depth, 3 ); 
			IplImage* imgHSVh = cvCreateImage( cvGetSize(frame_horizontal), frame_horizontal->depth, 3 ); 

			if(ui.checkBox_4->checkState()) cvMoveWindow( "Horizontal",100,100);
			if(ui.checkBox_5->checkState()) cvMoveWindow( "Vertical",700,100);
			//camera_calibration();
			//camera_calibration2();
			int kl = 0;
			int klm = 0;
			while(1){
				start = clock();
				double diff;
				frame_horizontal = cvQueryFrame( capture_horizontal );
				
				ponderacion1= ui.f1->text().toDouble();
				ponderacion2= ui.f2->text().toDouble();
				ponderacion3= ui.f3->text().toDouble();

				if(ui.filter1->isChecked()){
					// Build the undistort map used for all subsequent frames.
					mapx = cvCreateImage( cvGetSize(frame_horizontal), IPL_DEPTH_32F, 1 );
					mapy = cvCreateImage( cvGetSize(frame_horizontal), IPL_DEPTH_32F, 1 );
					cvInitUndistortMap(intrinsic,distortion,mapx,mapy);

					IplImage *t = cvCloneImage(frame_horizontal);
					cvRemap( t, frame_horizontal, mapx, mapy );  // Undistort image
					cvReleaseImage(&t);
					cvReleaseImage(&mapx);
					cvReleaseImage(&mapy);
				}
				if(flag_gauss_filter)
					cvSmooth( frame_horizontal, frame_horizontal,CV_GAUSSIAN,gauss1,gauss2);

				cvFlip(frame_horizontal,frame_horizontal,1);

				frame_vertical = cvQueryFrame( capture_vertical );
				if(flag_gauss_filter)
					cvSmooth( frame_vertical, frame_vertical,CV_GAUSSIAN,gauss1,gauss2);

				cvFlip(frame_vertical,frame_vertical,1);
				if(kl == 0){
					imagexy3 = cvCloneImage(frame_horizontal);
					imagez3 = cvCloneImage(frame_vertical);
					imagexy2 = cvCloneImage(frame_horizontal);
					imagez2 = cvCloneImage(frame_vertical);
					imagexy = cvCloneImage(frame_horizontal);
					imagez = cvCloneImage(frame_vertical);
				}

				cvConvertScale(frame_horizontal, frame_horizontal, ponderacion1);
				cvConvertScale(frame_vertical, frame_vertical, ponderacion1);

				cvReleaseImageData(imagexy3);
				cvReleaseImageData(imagez3);
				imagexy3 = cvCloneImage(imagexy2);
				imagez3 = cvCloneImage(imagez2);

				cvConvertScale(imagexy2, imagexy2, ponderacion2);
				cvConvertScale(imagez2, imagez2, ponderacion2);

				cvConvertScale(imagexy3, imagexy3, ponderacion3);
				cvConvertScale(imagez3, imagez3, ponderacion3);

				cvAdd(frame_horizontal, imagexy2, frame_horizontal);
				cvAdd(frame_horizontal, imagexy3, frame_horizontal);
				cvAdd(frame_vertical, imagez2, frame_vertical);
				cvAdd(frame_vertical, imagez3, frame_vertical);

				cvReleaseImageData(imagexy2);
				cvReleaseImageData(imagez2);
				imagexy2 = cvCloneImage(frame_horizontal);
				imagez2 = cvCloneImage(frame_vertical);

				cvAddS(frame_horizontal, cvScalar(ui.brightness->value(),ui.brightness->value(),ui.brightness->value()), frame_horizontal);
				cvAddS(frame_vertical, cvScalar(ui.vbrightness->value(),ui.vbrightness->value(),ui.vbrightness->value()), frame_vertical);

				cvCvtColor(frame_horizontal, imgHSV, CV_BGR2HSV); //Transformacion a HSV
				cvInRangeS(imgHSV,cvScalar(h11,s11,v11),cvScalar(h12,s12,v12), imgFilteredh);
				imgHSVh = cvCloneImage(imgHSV);

				cvCvtColor(frame_vertical, imgHSV, CV_BGR2HSV); //Transformacion a HSV
				cvInRangeS(imgHSV,cvScalar(h21,s21,v21),cvScalar(h22,s22,v22), imgFilteredv);
				imgHSVv = cvCloneImage(imgHSV);

				cvReleaseImageData(imagexy);
				cvReleaseImageData(imagez);
				imagexy = cvCloneImage(imgFilteredh);
				imagez = cvCloneImage(imgFilteredv);

				if(kl != 0){
					kl = 2;
					//filter(imgFilteredh, imgFilteredv, imgFilteredh_bef, imgFilteredv_bef);
				}

				if(erode){
					cvErode( imgFilteredh, imgFilteredh, NULL, cant_erode);
					cvDilate( imgFilteredh, imgFilteredh, NULL, cant_dilate);
					cvErode( imgFilteredv, imgFilteredv, NULL, cant_erode);
					cvDilate( imgFilteredv, imgFilteredv, NULL, cant_dilate);
				}
				xm = xyz[0];
				ym = xyz[1];
				zm = xyz[2];

				posxyz(imgFilteredh,imgFilteredv,imgHSVh,imgHSVv,xyz,method);

				/*
				pos_xyz_h[0][0] = xyz[0];
				pos_xyz_h[1][0] = xyz[1];
				pos_xyz_h[2][0] = xyz[2];
				pos_xyz_h[3][0] = xyz[3];

				for(int ij = 19; ij>0; ij--){
					pos_xyz_h[0][ij] = pos_xyz_h[0][ij-1];
					pos_xyz_h[1][ij] = pos_xyz_h[1][ij-1];
					pos_xyz_h[2][ij] = pos_xyz_h[2][ij-1];
					pos_xyz_h[3][ij] = pos_xyz_h[3][ij-1];
				}
		
				xyz[0] = mean_all(pos_xyz_h[0], 3);
				xyz[1] = mean_all(pos_xyz_h[1], 3);
				xyz[2] = mean_all(pos_xyz_h[2], 3);
*/

				//Comentar y descomentar el otro
			/*
				QString aux;
				Sleep(10);
				aux.setNum(xyz[0]);
				ui.x_2->setText(aux);
				aux.setNum(xyz[1]);
				ui.y_2->setText(aux);
				aux.setNum(xyz[2]);
				ui.z_2->setText(aux);
				*/

				if(kl != 2) kl = 1;

				cvReleaseImageData(imgHSVh);
				cvReleaseImageData(imgHSVv);

				cvReleaseImageData(imgFilteredh_bef);
				cvReleaseImageData(imgFilteredv_bef);
				imgFilteredh_bef = cvCloneImage(imagexy);
				imgFilteredv_bef = cvCloneImage(imagez);

				xyzr[0] = xyz[0];
				xyzr[1] = xyz[1];
				xyzr[2] = xyz[2];

				cvCircle(frame_horizontal, cvPoint(xyz[1],xyz[0]), 5, cvScalar(0,255,0), 3); //Dibuja un punto sobre la posicion
				cvCircle(frame_vertical, cvPoint(xyz[3],xyz[2]), 5, cvScalar(0,255,0), 3); //Dibuja un punto sobre la posicion

				if(ui.checkBox_5->checkState()){
					destination = cvCreateImage( cvSize((int)((frame_vertical->width*30)/100) , (int)((frame_vertical->height*30)/100) ),frame_vertical->depth, frame_vertical->nChannels );
					cvResize(frame_vertical, destination);
					cvLine(destination, cvPoint(0,(frame_vertical->height*30)/200), cvPoint((frame_vertical->width*30)/100,(frame_vertical->height*30)/200), cvScalar(0,100,0));
					cvLine(destination, cvPoint((frame_vertical->width*30)/200,0), cvPoint((frame_vertical->width*30)/200,(frame_vertical->height*30)/100), cvScalar(0,100,0));
					cvShowImage( "Vertical",  destination);
					cvReleaseImageData(destination);
				}
				if(ui.checkBox_4->checkState()){ 
					destination = cvCreateImage( cvSize((int)((frame_horizontal->width*30)/100) , (int)((frame_horizontal->height*30)/100) ),frame_horizontal->depth, frame_horizontal->nChannels );
					cvResize(frame_horizontal, destination);
					cvLine(destination, cvPoint(0,(frame_vertical->height*30)/200), cvPoint((frame_vertical->width*30)/100,(frame_vertical->height*30)/200), cvScalar(0,100,0));
					cvLine(destination, cvPoint((frame_vertical->width*30)/200,0), cvPoint((frame_vertical->width*30)/200,(frame_vertical->height*30)/100), cvScalar(0,100,0));
					cvShowImage( "Horizontal", destination);
					cvReleaseImageData(destination);
				}
				
				xyz[0] = xyz[0] - xyz_ini[0];
				xyz[1] = xyz[1] - xyz_ini[1];
				xyz[2] = xyz[2] - xyz_ini[2];
				xyz[3] = xyz[3] - xyz_ini[3];

				if(ui.mm->isChecked()){
					xyz[0] = pixel2mm[0]*xyz[0];
					xyz[1] = pixel2mm[1]*xyz[1];
					xyz[2] = pixel2mm[2]*xyz[2]; 
				}else if(ui.inches->isChecked()){
					xyz[0] = pixel2mm[0]*xyz[0]*mm2inches;
					xyz[1] = pixel2mm[1]*xyz[1]*mm2inches;
					xyz[2] = pixel2mm[2]*xyz[2]*mm2inches; 
				}

				double calibx = 1;
				double caliby = 1;
				double calibz = 1;

				//calib en x
				if(-xyz[0] > 20 && -xyz[0] < -20)
				//if( (-xyz[0]>rangox1 && -xyz[0]<rangox2) || (-xyz[0] < 0.02 && -xyz[0] > -0.02) )
					calibx = 1;
				else if(-xyz[0]>0)
					calibx = abs(40./calibparam[0]);
					//calibx = abs((40./calibparam[0])*pow(abs(calibparam[0]),1./35)/pow(abs(xyz[0]),1./35));
				else if(-xyz[0]<0)
					calibx = abs(40./calibparam[1]);
					//calibx = abs((40./calibparam[1])*pow(abs(calibparam[1]),1./35)/pow(abs(xyz[0]),1./35));
				else
					calibx = 1;

				//calib en y
				if(xyz[1] > 20 && xyz[1] < -20)
				//if((xyz[1]>rangoy1 && xyz[1]<rangoy2) || (xyz[1] < 0.02 && xyz[1] > -0.02) )
					caliby = 1;
				else if(xyz[1]>0)
					caliby = abs(40./calibparam[2]);
					//caliby = abs((40./calibparam[2])*pow(abs(calibparam[2]),1./35)/pow(abs(xyz[1]),1./35));
				else if(xyz[1]<0)
					caliby = abs(40./calibparam[3]);
					//caliby = abs((40./calibparam[3])*pow(abs(calibparam[3]),1./35)/pow(abs(xyz[1]),1./35));
				else
					caliby = 1;
				

				//calib en z
				if( xyz[2] < 0.02 && xyz[2] > -0.02 )
					calibz = 1;
				else if(xyz[2]>0)
					calibz = abs((7./calibparam[4])*pow(abs(calibparam[4]),1./35)/pow(abs(xyz[2]),1./35));
				else if(xyz[2]<0)
					calibz = abs((7./calibparam[5])*pow(abs(calibparam[5]),1./35)/pow(abs(xyz[2]),1./35));
				else
					calibz = 1;

				if(ui.move_correction->isChecked()){
					double xyz0_aux;
					double xyz1_aux;

					if(xyz[1]>0)
						xyz0_aux = xyz[0] + calibparam[8]*xyz[1]/40.;
					else if(xyz[1]<0)
						xyz0_aux = xyz[0] + calibparam[9]*xyz[1]/40.;

					if(-xyz[0]>0)
						xyz1_aux = xyz[1] - calibparam[6]*xyz[0]/40.;
					else if(-xyz[0]<0)
						xyz1_aux = xyz[1] - calibparam[7]*xyz[0]/40.;

					xyz[0] = xyz0_aux;
					xyz[1] = xyz1_aux;
				}

				xyz[0] = xyz[0]*calibx;
				xyz[1] = xyz[1]*caliby;
				xyz[2] = xyz[2]*calibz;

				xyzaux[0] = xyz[0];
				xyzaux[1] = xyz[1];
				xyzaux[2] = xyz[2];

				xyz[0] = xyz[0] - refx;
				xyz[1] = xyz[1] - refy;
				xyz[2] = xyz[2] - refz;

				if(!ui.plotxy->isChecked()){
					cvSet(medicionxy, cvScalar(0,0,0));
					cvDestroyWindow("Ploteo");
				}
				else{
					cvLine(medicionxy,cvPoint((ym+refy+pixel2mm[1]*xyz_ini[1])/pixel2mm[1],(xm+refx+pixel2mm[0]*xyz_ini[0])/pixel2mm[0]),cvPoint((xyz[1]+refy+pixel2mm[1]*xyz_ini[1])/pixel2mm[1],(xyz[0]+refx+pixel2mm[0]*xyz_ini[0])/pixel2mm[0]),cvScalar(30+7*(xyz[2]+10),0,0),5);
					//cvLine(medicionxy,cvPoint((ycam2+refy+pixel2mm[1]*xyz_ini[1])/pixel2mm[1],(xcam2+refx+pixel2mm[0]*xyz_ini[0])/pixel2mm[0]),cvPoint((ycam1+refy+pixel2mm[1]*xyz_ini[1])/pixel2mm[1],(xcam1+refx+pixel2mm[0]*xyz_ini[0])/pixel2mm[0]),cvScalar(255,0,0),3);
					//cvLine(medicionxy,cvPoint((ymach2+refy+pixel2mm[1]*xyz_ini[1])/pixel2mm[1],(xmach2+refx+pixel2mm[0]*xyz_ini[0])/pixel2mm[0]),cvPoint((ymach1+refy+pixel2mm[1]*xyz_ini[1])/pixel2mm[1],(xmach1+refx+pixel2mm[0]*xyz_ini[0])/pixel2mm[0]),cvScalar(0,120+10*(xyz[2]+refz+pixel2mm[2]*xyz_ini[2]*xyz_ini[2]),0),3);
					destination = cvCreateImage( cvSize((int)((medicionxy->width*30)/100) , (int)((medicionxy->height*30)/100) ),medicionxy->depth, medicionxy->nChannels );
					cvResize(medicionxy, destination);
					cvShowImage("Ploteo",destination);
				}
				//Var para transformar numero a string
				QString aux;
				Sleep(10);

				aux.setNum(-xyz[0]);
				//aux.setNum(calibx);
				ui.x_2->setText(aux);

				//aux.setNum(xyz[1]);
				//aux.setNum(caliby);
				//aux.setNum(pixel2mm[4]);
				//ui.y_2->setText(aux);

				aux.setNum(xyz[2]);
				//aux.setNum(calibz);
				ui.z_2->setText(aux);
				
				readmodificable("C:\\Mach3\\comunicacion.txt");
				if(modificable == 1){
					position.open(ui.lineEdit->text().toStdString());
					
					position << -xyz[0] << endl;
					position << xyz[1] << endl;
					position << xyz[2] << endl;

					position << "" << endl;
					position.close();
					//lastposition();
					writemodificable("C:\\Mach3\\comunicacion.txt");
				}

				cvReleaseImageData(imagexy3);
				cvReleaseImageData(imagez3);
				cvReleaseImageData(imagexy);
				cvReleaseImageData(imagez);

				//Comprueba que al menos una pantalla este abierta para el manejo de la tecla
				if( !cvGetWindowHandle("Vertical") && !cvGetWindowHandle("Horizontal") ) cvShowImage( "Vertical", frame_vertical );
				key = cvWaitKey(10);
				if( (char) key == 27 || !ui.workingall->checkState())
					break;	

				diff = (std::clock() - start)/(double)CLOCKS_PER_SEC;
				aux.setNum(diff);
				//aux.setNum(caliby);
				//aux.setNum(pixel2mm[4]);
				ui.y_2->setText(aux);
			}
		}

		cvReleaseCapture( &capture_horizontal );
		cvDestroyWindow("Horizontal");
		cvDestroyWindow("Ploteo");
		cvReleaseCapture( &capture_vertical );
		cvDestroyWindow("Vertical");
		ui.workingall->setChecked(0);
	}

}

/**
* Funcion que detiene el programa al presionar el botón Stop
*/
void Fress::on_Stop_clicked(){
	ui.workingall->setChecked(0);
	ui.workingcalibration->setChecked(0);
}

/**
* Funcion que visualiza las camaras de calibracion y permite seleccionar 
* un pixel para filtrar el color al presionar el botón Show
*/
void Fress::on_Show_clicked(){
	
	if(!ui.workingall->checkState() && !ui.workingcalibration->checkState()){
		ui.workingcalibration->setChecked(1);

		IplImage *destination = NULL;

		//Inicializacion de parametros de las camaras
		frame_horizontal = NULL;
		frame_vertical = NULL;

		imgHSV = NULL; //Imagen donde se guardará la imagen en HSV
		imgFilteredv = NULL; //Imagen donde se guardará la imagen filtrada
		imgFilteredh = NULL; //Imagen donde se guardará la imagen filtrada

		capture_horizontal = NULL;
		capture_vertical = NULL;
		
		while(capture_horizontal == NULL) capture_horizontal = cvCaptureFromCAM(0);
		while(capture_vertical == NULL) capture_vertical = cvCaptureFromCAM(1);

		//cvSetCaptureProperty( capture_horizontal, CV_CAP_PROP_FRAME_WIDTH, 1280 );
		//cvSetCaptureProperty( capture_horizontal, CV_CAP_PROP_FRAME_HEIGHT, 1024 );

		//cvSetCaptureProperty( capture_vertical, CV_CAP_PROP_FRAME_WIDTH, 1280 );
		//cvSetCaptureProperty( capture_vertical, CV_CAP_PROP_FRAME_HEIGHT, 1024 );

		cvNamedWindow("Imagen");
		cvNamedWindow("Separada");

		frame_horizontal = cvQueryFrame( capture_horizontal );
		
		imgHSV = cvCreateImage( cvGetSize(frame_horizontal), frame_horizontal->depth, 3 ); 
		imgFilteredh = cvCreateImage( cvGetSize(frame_horizontal), frame_horizontal->depth, 1 ); 
		imgFilteredv = cvCreateImage( cvGetSize(frame_horizontal), frame_horizontal->depth, 1 ); 
		//camera_calibration();
		//camera_calibration2();
		if(capture_horizontal && capture_vertical){
			while(1){
				thr_1 = ui.thr_1->text().toInt();
				thr_2 = ui.thr_2->text().toInt();
				thr_3 = ui.thr_3->text().toInt();

				if(ui.rhorizontal->isChecked()){
					if(flag_thrz){
						flag_thrz = false;
						ui.h1->setValue(h11z);
						ui.h2->setValue(h12z);
						ui.v1->setValue(v11z);
						ui.v2->setValue(v12z);
						ui.s1->setValue(s11z);
						ui.s2->setValue(s12z);
					}

					frame_horizontal = cvQueryFrame( capture_horizontal );

					if(flag_gauss_filter)
						cvSmooth( frame_horizontal, frame_horizontal,CV_GAUSSIAN,gauss1,gauss2);

					cvSetMouseCallback("Imagen", mouseHandler, (void*)frame_horizontal);

					cvAddS(frame_horizontal, cvScalar(ui.brightness->value(),ui.brightness->value(),ui.brightness->value()), frame_horizontal);
		
					cvFlip(frame_horizontal,frame_horizontal,1);

					cvCvtColor(frame_horizontal, imgHSV, CV_BGR2HSV); //Transformacion a HSV
					cvInRangeS(imgHSV,cvScalar(ui.h1->value(),ui.s1->value(),ui.v1->value()),cvScalar(ui.h2->value(),ui.s2->value(),ui.v2->value()), imgFilteredh);

					//destination = cvCreateImage( cvSize((int)((frame_horizontal->width*30)/100) , (int)((frame_horizontal->height*30)/100) ),frame_horizontal->depth, frame_horizontal->nChannels );
					//cvResize(frame_horizontal, destination);
					cvShowImage("Imagen", frame_horizontal);

					//destination = cvCreateImage( cvSize((int)((imgFilteredh->width*30)/100) , (int)((imgFilteredh->height*30)/100) ),imgFilteredh->depth, imgFilteredh->nChannels );
					//cvResize(imgFilteredh, destination);
					if(erode){
						cvErode( imgFilteredh, imgFilteredh, NULL, cant_erode);
						cvDilate( imgFilteredh, imgFilteredh, NULL, cant_dilate);
					}
					cvShowImage("Separada", imgFilteredh);

				}else if(ui.rvertical->isChecked()){
					if(flag_thrz){
						flag_thrz = false;
						ui.h1->setValue(h11z);
						ui.h2->setValue(h12z);
						ui.v1->setValue(v11z);
						ui.v2->setValue(v12z);
						ui.s1->setValue(s11z);
						ui.s2->setValue(s12z);
					}

					frame_vertical = cvQueryFrame( capture_vertical );

					if(flag_gauss_filter)
						cvSmooth( frame_vertical, frame_vertical,CV_GAUSSIAN,gauss1,gauss2);

					cvSetMouseCallback("Imagen", mouseHandler, (void*)frame_vertical);
					cvAddS(frame_vertical, cvScalar(ui.vbrightness->value(),ui.vbrightness->value(),ui.vbrightness->value()), frame_vertical);

					cvFlip(frame_vertical,frame_vertical,1);
					cvCvtColor(frame_vertical, imgHSV, CV_BGR2HSV); //Transformacion a HSV
					cvInRangeS(imgHSV,cvScalar(ui.h1->value(),ui.s1->value(),ui.v1->value()),cvScalar(ui.h2->value(),ui.s2->value(),ui.v2->value()), imgFilteredv);

					//destination = cvCreateImage( cvSize((int)((frame_vertical->width*30)/100) , (int)((frame_vertical->height*30)/100) ),frame_vertical->depth, frame_vertical->nChannels );
					//cvResize(frame_vertical, destination);
					cvShowImage("Imagen", frame_vertical);
					//destination = cvCreateImage( cvSize((int)((imgFilteredv->width*30)/100) , (int)((imgFilteredv->height*30)/100) ),imgFilteredv->depth, imgFilteredv->nChannels );
					//cvResize(imgFilteredv, destination);
					if(erode){
						cvErode( imgFilteredv, imgFilteredv, NULL, cant_erode);
						cvDilate( imgFilteredv, imgFilteredv, NULL, cant_dilate);
					}
					cvShowImage("Separada", imgFilteredv);

				}
				key = cvWaitKey(10);
				if( (char) key == 27 || !ui.workingcalibration->checkState())
					break;	
			}
		}

		cvReleaseCapture( &capture_horizontal );
		cvDestroyWindow("Imagen");

		cvReleaseCapture( &capture_vertical );
		cvDestroyWindow("Separada");

		ui.workingcalibration->setChecked(0);
	}	
}

/**
* Cierra la pantalla de calibracion al presionar el botón Close
*/
void Fress::on_Close_clicked(){
	ui.workingcalibration->setChecked(0);
}

/**
* Manda a Rojo la calibración de los parametros  al presionar el botón R
*/
void Fress::on_R_clicked(){
	ui.h1->setValue(131);
	ui.h2->setValue(190);
	ui.s1->setValue(113);
	ui.s2->setValue(225);
	ui.v1->setValue(40);
	ui.v2->setValue(255);
}

/**
* Manda a Verde la calibración de los parametros  al presionar el botón G
*/
void Fress::on_G_clicked(){
	ui.h1->setValue(60);
	ui.h2->setValue(96);
	ui.s1->setValue(87);
	ui.s2->setValue(199);
	ui.v1->setValue(123);
	ui.v2->setValue(255);
}

/**
* Manda a Azul la calibración de los parametros  al presionar el botón B
*/
void Fress::on_B_clicked(){
	ui.h1->setValue(0);
	ui.h2->setValue(250);
	ui.s1->setValue(180);
	ui.s2->setValue(255);
	ui.v1->setValue(128);
	ui.v2->setValue(237);


}

/**
* Muestra los parámetros guardados para la imagen vertical
*/
void Fress::rvertical(){
	ui.h1->setValue(h21);
	ui.h2->setValue(h22);
	ui.s1->setValue(s21);
	ui.s2->setValue(s22);
	ui.v1->setValue(v21);
	ui.v2->setValue(v22);
}

/**
* Muestra los parámetros guardados para la imagen horizontal
*/
void Fress::rhorizontal(){
	ui.h1->setValue(h11);
	ui.h2->setValue(h12);
	ui.s1->setValue(s11);
	ui.s2->setValue(s12);
	ui.v1->setValue(v11);
	ui.v2->setValue(v12);
}

/**
* Guarda los parametros de las barras  al presionar el botón save
*/
void Fress::on_save_clicked(){
	if(ui.rhorizontal->isChecked()){
		h11 = ui.h1->value();
		h12 = ui.h2->value();
		s11 = ui.s1->value();
		s12 = ui.s2->value();
		v11 = ui.v1->value();
		v12 = ui.v2->value();
	}
	if(ui.rvertical->isChecked()){
		h21 = ui.h1->value();
		h22 = ui.h2->value();
		s21 = ui.s1->value();
		s22 = ui.s2->value();
		v21 = ui.v1->value();
		v22 = ui.v2->value();
	}
	writefile("datos.csv");
}

/**
* Retorna la posición xy en el arreglo de 3 dimensiones
* Method = 1, usa una imagen binaria para determinar la posición del centroide
* Method = 2, usa la intensidad de los pixeles para determinar la posición del centroide
* Method = 3, usa la intensidad de los pixeles para determinar la posición del centroide + una gaussiana para dar prioridad al centro
* Method = valores anteriores, usa el método de OpenCV para determinar la posición (Más lento)
*
* IplImage* imagexy: Imagen horozontal 
* IplImage* imagez: Imagen vertical 
* IplImage* imageHSVh: Imagen horizontal en hsv
* IplImage* imageHSVv: Imagen vertical en hsvs
* double *xyz: Posiciones x, y, z de los puntos de la cámara
* int method: Método de estimación de centroide
*/
void Fress::posxyz(IplImage* imagexy, IplImage* imagez,IplImage* imageHSVh, IplImage* imageHSVv, double *xyz, int method){

	double xyz_aux[4];

	xyz_aux[0] = xyz[0];
	xyz_aux[1] = xyz[1];
	xyz_aux[2] = xyz[2];
	xyz_aux[3] = xyz[3];
	

	if(method==1){
		int width, height;

		width = imagexy->width;
		height = imagexy->height;
		int posx=0, posy=0, suma=0, suma2 = 0, posx2 = 0, posy2 = 0, valor1=0, valor2=0;

		suma = 0;
		suma2 = 0;
		for(int i=0; i<height; i++){
			for(int j=0; j<width; j++){
				valor1 = (int)((uchar *)(imagexy->imageData + i*imagexy->widthStep))[j*imagexy->nChannels +0];
				valor2 = (int)((uchar *)(imagez->imageData + i*imagez->widthStep))[j*imagez->nChannels +0];
				if(valor1>0){
					posx+=i;
					posy+=j;
					suma++;
				}
				if(valor2>0){
					posx2+=i;
					posy2+=j;
					suma2++;
				}
			}
		}

		if(suma>0){
			if(suma == 0)
				suma = 1;
			if(suma2 == 0)
				suma2 = 1;

			xyz[0] = (double)posx/suma;
			xyz[1] = (double)posy/suma;
			xyz[2] = (double)posx2/suma2;
			xyz[3] = (double)posy2/suma2;
		}else{
			xyz[0] = 0;
			xyz[1] = 0;
			xyz[2] = 0;
			xyz[3] = 0;
		}

	}else if(method==2){
		int width, height;

		width = imagexy->width;
		height = imagexy->height;
		double posx=0, posy=0, suma=0, suma2 = 0, posx2 = 0, posy2 = 0, valor1 = 0, valor2 = 0;
		suma = 0;
		suma2 = 0;
	
		for(int i=0; i<height; i++){

			for(int j=0; j<width; j++){
				valor2 = (double)((uchar *)(imagexy->imageData + i*imagexy->widthStep))[j*imagexy->nChannels +0];

				if(valor2>0){
					valor1 = (double)((uchar *)(imageHSVh->imageData + i*imageHSVh->widthStep))[j*imageHSVh->nChannels +2];

					posx+=i*(double)valor1;
					posy+=j*(double)valor1;
					suma+=(double)valor1;
				}

				valor2 = (double)((uchar *)(imagez->imageData + i*imagez->widthStep))[j*imagez->nChannels +0];
				if(valor2>0){
					valor1 = (double)((uchar *)(imageHSVv->imageData + i*imageHSVv->widthStep))[j*imageHSVv->nChannels +2];

					posx2+=i*(double)valor1;
					posy2+=j*(double)valor1;
					suma2+=(double)valor1;
				}
			}
		}
		if(suma>0){
			if(suma == 0)
				suma = 1;
			if(suma2 == 0)
				suma2 = 1;

			xyz[0] = posx/suma;
			xyz[1] = posy/suma;
			xyz[2] = posx2/suma2;
			xyz[3] = posy2/suma2;
		}else{
			xyz[0] = 0;
			xyz[1] = 0;
			xyz[2] = 0;
			xyz[3] = 0;
		}

	}else if(method==3){
		int width, height;

		width = imagexy->width;
		height = imagexy->height;
		double posx=0, posy=0, suma=0, suma2 = 0, posx2 = 0, posy2 = 0, valor1 = 0, valor2 = 0;
		suma = 0;
		suma2 = 0;
		double gauss =0;

		for(int i=0; i<height; i++){
			for(int j=0; j<width; j++){
				valor2 = (double)((uchar *)(imagexy->imageData + i*imagexy->widthStep))[j*imagexy->nChannels +0];
				if(valor2>0){
					valor1 = (double)((uchar *)(imageHSVh->imageData + i*imageHSVh->widthStep))[j*imageHSVh->nChannels +2];
					
					if(!flag_fxyz){
						posx+=i*(double)valor1;
						posy+=j*(double)valor1;
						suma+=(double)valor1;
					}else{
						double deltax_s = (xyz[0]-i+1)*(xyz[0]-i+1);
						double deltay_s = (xyz[1]-j+1)*(xyz[1]-j+1);
						double sigma = 1/(2*3.141592*sigmagaussxy*sigmagaussxy);
						gauss = sigma*exp(-(deltax_s+deltay_s)*sigma);

						posx+=i*(double)valor1*gauss;
						posy+=j*(double)valor1*gauss;
						suma+=(double)valor1*gauss;
					}
				}
				valor2 = (double)((uchar *)(imagez->imageData + i*imagez->widthStep))[j*imagez->nChannels +0];
				if(valor2>0){
					valor1 = (double)((uchar *)(imageHSVv->imageData + i*imageHSVv->widthStep))[j*imageHSVv->nChannels +2];

					if(!flag_fxyz){
						posx2+=i*(double)valor1;
						posy2+=j*(double)valor1;
						suma2+=(double)valor1;
					}else{
						double deltax_s = (xyz[2]-i+1)*(xyz[2]-i+1);
						double deltay_s = (xyz[3]-j+1)*(xyz[3]-j+1);
						double sigma = 1/(2*3.141592*sigmagaussxy*sigmagaussxy);
						gauss = sigma*exp(-(deltax_s+deltay_s)*sigma);

						posx2+=i*(double)valor1*gauss;
						posy2+=j*(double)valor1*gauss;
						suma2+=(double)valor1*gauss;
					}
				}
			}
		}

		if(suma>0){
			if(suma == 0)
				suma = 1;
			if(suma2 == 0)
				suma2 = 1;

			xyz[0] = posx/suma;
			xyz[1] = posy/suma;
			xyz[2] = posx2/suma2;
			xyz[3] = posy2/suma2;
		}else{
			xyz[0] = 0;
			xyz[1] = 0;
			xyz[2] = 0;
			xyz[3] = 0;
		}
		flag_fxyz = true;
	}else{
		CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
        cvMoments(imagexy, moments, 1);
		double moment10 = cvGetSpatialMoment(moments, 1, 0);
        double moment01 = cvGetSpatialMoment(moments, 0, 1);
		double area = cvGetCentralMoment(moments, 0, 0);
		
		xyz[0] = moment01/area;
        xyz[1] = moment10/area;

		cvMoments(imagez, moments, 1);
		moment10 = cvGetSpatialMoment(moments, 1, 0);
        moment01 = cvGetSpatialMoment(moments, 0, 1);
		area = cvGetCentralMoment(moments, 0, 0);

		xyz[2] = moment10/area;
		xyz[3] = moment01/area;
		
		if(xyz[0]<0 || xyz[0] != xyz[0]) xyz[0] = 0;
		if(xyz[1]<0 || xyz[1] != xyz[1]) xyz[1] = 0;
		if(xyz[2]<0 || xyz[2] != xyz[2]) xyz[2] = 0;
		if(xyz[3]<0 || xyz[3] != xyz[3]) xyz[3] = 0;
		
		free(moments);
	}
	/*
	double delta = 50;
	if( abs(xyz_aux[0] - xyz[0]) > delta || abs(xyz_aux[1] - xyz[1]) > delta || abs(xyz_aux[2] - xyz[2])>delta ){
		xyz[0] = xyz_aux[0];
		xyz[1] = xyz_aux[1];
		xyz[2] = xyz_aux[2];
		xyz[3] = xyz_aux[3];
	}
	*/
}

/**
* Imprime valores en un archivo de texto "String"
*/
void Fress::write(IplImage* image, string file){
	string line;
	ofstream myfile(file);
	int width, height;
	CvScalar s;

	width = image->width;
	height = image->height;

	if (myfile.is_open())
	{
		myfile << width;
		myfile << "x";
		myfile << height;
		myfile << "\n";
		for(int i=0; i<height; i++){
			for(int j=0; j<width; j++){
				s = cvGet2D(image,i,j);
				myfile << s.val[0];
				myfile << " ";
			}
			myfile << "\n";
		}
		myfile.close();
	}else cout << "Unable to open file"; 
}

/**
* Permite seleccionar un archivo de un directorio y guardarlo en la pantalla de Fress
* al presionar el boton Open
**/
void Fress::on_Open_clicked(){
	QString filename = QFileDialog::getOpenFileName(0, "Get open file name", "C:\\Mach3\\", "Text (*.txt)");
	ui.lineEdit->setText(filename);
}

/**
* Función que setea la posición actual como el 0 de fress al presionar el boton set 0
**/
void Fress::on_set_0_clicked(){
	refx = xyzaux[0];
	refy = xyzaux[1];
	refz = xyzaux[2];
}

/**
* Lee archivo de configuración y utiliza estos parámetros de configuracion
* del filtro de colores
*
* string path: Dirección del archivo de comunicación
**/
void Fress::readfile(string file){
	string line;
	ifstream myfile(file);

	if (myfile.is_open())
	{
		myfile >> h11;
		myfile >> h12;
		myfile >> s11;
		myfile >> s12;
		myfile >> v11;
		myfile >> v12;

		myfile >> s21;
		myfile >> s22;
		myfile >> h21;
		myfile >> h22;
		myfile >> v21;
		myfile >> v22;

		int value = 0;
		myfile >> value;
		ui.brightness->setValue(value);
		myfile >> value;
		ui.vbrightness->setValue(value);
		myfile >> value;
		ui.brightness_2->setValue(value);
		myfile >> value;
		ui.brightness_3->setValue(value);

		myfile.close();
	}
	rvertical();
	rhorizontal();
}

/**
* Guarda en archivo los parámetros configuración de los filtros de colores
*
* string path: Dirección del archivo de comunicación
**/
void Fress::writefile(string file){
	string line;
	ofstream myfile(file);

	if (myfile.is_open())
	{
		
		myfile << h11;
		myfile << "\n";
		myfile << h12;
		myfile << "\n";
		myfile << s11;
		myfile << "\n";
		myfile << s12;
		myfile << "\n";
		myfile << v11;
		myfile << "\n";
		myfile << v12;
		myfile << "\n";

		myfile << s21;
		myfile << "\n";
		myfile << s22;
		myfile << "\n";
		myfile << h21;
		myfile << "\n";
		myfile << h22;
		myfile << "\n";
		myfile << v21;
		myfile << "\n";
		myfile << v22;
		myfile << "\n";
		myfile << ui.brightness->value();
		myfile << "\n";
		myfile << ui.vbrightness->value();
		myfile << "\n";
		myfile << ui.brightness_2->value();
		myfile << "\n";
		myfile << ui.brightness_3->value();

		myfile.close();
	}
}

/**
* Lee el archivo de comunicación y lo guarda en modificable
*
* string path: Dirección del archivo de comunicación
**/
void Fress::readmodificable(string path){
	string line;
	ifstream myfile(path);
	if (myfile.is_open())
	{
		myfile >> line;
	}
	const char *line_char = line.c_str();
	modificable = atoi(line_char);
	myfile.close();
}

/**
* Lee el entero de un archivo "path" y lo retorna
*
* string path: Dirección del archivo de comunicación
*/
double * Fress::readint(string path){
	string line;
	ifstream myfile(path);
	double values[9] = {0};
	double value;

	for(int i = 0; i<9; i++){
		if (myfile.is_open())
		{
			myfile >> line;
			const char *line_char = line.c_str();
			value = atof(line_char);
			values[i] = value;
		}else{
			values[i]  = 0.0001;
		}
	}
	myfile.close();
	return values;
}

/**
* Escribe 0 en el archivo de comunicación
*
* string path: Dirección del archivo de comunicación
*/
void Fress::writemodificable(string path){
	string line;
	ofstream myfile(path);
	if (myfile.is_open())
	{
		myfile << 0;
	}
	myfile.close();
}

/**
* Función para seleccionar colores con clicks
*
* int event: Parámetro de eventos
* int x: Posición x en pixeles de selección
* int y: Posición y en pixeles de selección 
* int flags: Marcación 
* void* param: Memoria de parámetros
**/
void mouseHandler(int event, int x, int y, int flags, void* param){
	
    IplImage* img0, * img1, *imgHSV ;
    uchar*    ptr;

    img0 = (IplImage*) param;
    img1 = cvCloneImage(img0);
 
    if (event == CV_EVENT_LBUTTONDOWN)
    {
		flag_thrz = true;
        /* read pixel */
		imgHSV = cvCreateImage( cvGetSize(img1), img1->depth, 3 ); 
		cvCvtColor(img1, imgHSV, CV_BGR2HSV);
        ptr = cvPtr2D(imgHSV, y, x, NULL);

		h11z=ptr[0]-thr_3;
		h12z=ptr[0]+thr_3;
		s11z=ptr[1]-thr_2;
		s12z=ptr[1]+thr_2;
		v11z=ptr[2]-thr_1;
		v12z=ptr[2]+thr_1;
    }
}

/**
* Función que llama a la calibración al presionar el boton Calibration
*/
void Fress::on_calibration_clicked(){
	if(ui.workingall->isChecked()){
		z.pos = xyz[0];
		z.show();
	}
}

/**
* Lee los parámetros de transformación desde un archivo
*/
void Fress::read_pixel2mm(){
	double* pos;
	pos = readint("C:\\Mach3\\pixel2unit.txt");

	for(int i = 0; i<5; i++)
		pixel2mm[i] = pos[i];

	for(int i = 0; i<4; i++)
		xyz_ini[i] = pos[i+5];
}

/**
* Apaga white balance si las cámaras lo permiten
**/
void Fress::camera_calibration(){
	if(!flag_calibration) return; 
	//IAMCameraControl *pCameraControl = NULL;
	IBaseFilter *pFilter = NULL;
	IAMVideoProcAmp *m_pProcAmp = NULL;
	HRESULT hr;

	// Create the System Device Enumerator.
	ICreateDevEnum *pSysDevEnum = NULL;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void **)&pSysDevEnum);
	if(FAILED(hr))
	{
		fprintf(stderr, "ERROR: Unable to create system device enumerator.\n");
		//return pCameraControl;
	}

	// Obtain a class enumerator for the video input device category.
	IEnumMoniker *pEnumCat = NULL;
	hr = pSysDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnumCat, 0);

	if(hr == S_OK) 
	{
		// Enumerate the monikers.
		IMoniker *pMoniker = NULL;
		ULONG cFetched;
		while(pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
		{
			IPropertyBag *pPropBag;
			hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pPropBag);
			if(SUCCEEDED(hr))
			{
				// To retrieve the filter's friendly name, do the following:
				VARIANT varName;
				VariantInit(&varName);
				hr = pPropBag->Read(L"FriendlyName", &varName, 0);
				if (SUCCEEDED(hr))
				{
					// Display the name in your UI somehow.
					wprintf(L"  Found device: %s\n", varName.bstrVal);
				}
				VariantClear(&varName);

				// To create an instance of the filter, do the following:
				
				hr = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter, (void**)&pFilter);								

				// Get a pointer to the IAMCameraControl interface used to control the camera
				//hr = pFilter->QueryInterface(IID_IAMCameraControl, (void **)&m_pProcAmp);
				hr = pFilter->QueryInterface(IID_IAMVideoProcAmp, (void **)&m_pProcAmp);

				if(hr != S_OK) {
					fprintf(stderr, "ERROR: Unable to access IAMCameraControl interface.\n");
					return;
				}

				long Min=NULL, Max=NULL, Step=NULL, Default=NULL, Flags=NULL, Val=NULL;
				hr = m_pProcAmp->GetRange(VideoProcAmp_WhiteBalance, &Min, &Max, &Step,&Default, &Flags);
				hr = m_pProcAmp->Get(VideoProcAmp_WhiteBalance, &Val, &Flags);
				hr = m_pProcAmp->Set(VideoProcAmp_WhiteBalance, Val, VideoProcAmp_Flags_Manual);

				// Retrieve information about the pan and tilt controls
				//hr = pCameraControl->GetRange(CameraControl_Pan, &panInfo.min, &panInfo.max, &panInfo.step, &panInfo.def, &panInfo.flags);
				if(hr != S_OK) {
					//ui.TextTest->setText("Fallo");
					return;
				}

				if(m_pProcAmp) {
					m_pProcAmp->Release();
				}
				pPropBag->Release();
			}
			pMoniker->Release();
		}
		pEnumCat->Release();
	}
	pSysDevEnum->Release();
}

/**
* Configura el parámetro de exposición si la cámara lo permite
**/
void Fress::camera_calibration2(){
	if(!flag_calibration) return; 
	//IAMCameraControl *pCameraControl = NULL;
	IBaseFilter *pFilter = NULL;
	IAMCameraControl *m_pProcAmp = NULL;
	HRESULT hr;
	int ijm = 0;
	// Create the System Device Enumerator.
	ICreateDevEnum *pSysDevEnum = NULL;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void **)&pSysDevEnum);
	if(FAILED(hr))
	{
		fprintf(stderr, "ERROR: Unable to create system device enumerator.\n");
		//return pCameraControl;
	}

	// Obtain a class enumerator for the video input device category.
	IEnumMoniker *pEnumCat = NULL;
	hr = pSysDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnumCat, 0);

	if(hr == S_OK) 
	{
		// Enumerate the monikers.
		IMoniker *pMoniker = NULL;
		ULONG cFetched;
		while(pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
		{
			IPropertyBag *pPropBag;
			hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pPropBag);
			if(SUCCEEDED(hr))
			{
				// To retrieve the filter's friendly name, do the following:
				VARIANT varName;
				VariantInit(&varName);
				hr = pPropBag->Read(L"FriendlyName", &varName, 0);
				if (SUCCEEDED(hr))
				{
					// Display the name in your UI somehow.
					wprintf(L"  Found device: %s\n", varName.bstrVal);
				}
				VariantClear(&varName);

				// To create an instance of the filter, do the following:
				
				hr = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter, (void**)&pFilter);								

				// Get a pointer to the IAMCameraControl interface used to control the camera
				//hr = pFilter->QueryInterface(IID_IAMCameraControl, (void **)&m_pProcAmp);
				hr = pFilter->QueryInterface(IID_IAMCameraControl, (void **)&m_pProcAmp);

				if(hr != S_OK) {
					fprintf(stderr, "ERROR: Unable to access IAMCameraControl interface.\n");
					return;
				}

				long Min=NULL, Max=NULL, Step=NULL, Default=NULL, Flags=NULL, Val=NULL;
				hr = m_pProcAmp->GetRange(CameraControl_Exposure, &Min, &Max, &Step,&Default, &Flags);
				hr = m_pProcAmp->Get(CameraControl_Exposure, &Val, &Flags);
				if(ijm == 0)
					hr = m_pProcAmp->Set(CameraControl_Exposure, ui.brightness_2->value(), CameraControl_Flags_Manual);
				if(ijm == 1)
					hr = m_pProcAmp->Set(CameraControl_Exposure, ui.brightness_3->value(), CameraControl_Flags_Manual);
				ijm++;
				//hr = pCameraControl->Set(8, 5600, );
				// Retrieve information about the pan and tilt controls
				//hr = pCameraControl->GetRange(CameraControl_Pan, &panInfo.min, &panInfo.max, &panInfo.step, &panInfo.def, &panInfo.flags);
				if(hr != S_OK) {
					//ui.TextTest->setText("Fallo");
					return;
				}

				if(m_pProcAmp) {
					m_pProcAmp->Release();
				}
				pPropBag->Release();
			}
			pMoniker->Release();
		}
		pEnumCat->Release();
	}
	pSysDevEnum->Release();
}

void Fress::filter(IplImage* imagexy, IplImage* imagez, IplImage* imagexy_bef, IplImage* imagez_bef){
		return;
		//if(!ui.filter1->isChecked() && !ui.filter2->isChecked()) return;
		/*
		int width, height;
		CvScalar s1xy, s2xy, s3xy, s4xy, s5xy, s6xy, s7xy, s8xy, s9xy;
		CvScalar s1z, s2z, s3z, s4z, s5z, s6z, s7z, s8z, s9z;

		CvScalar sxy, sz;

		width = imagexy->width;
		height = imagexy->height;
		int suma=0, suma2 = 0;

		for(int i=1; i<height-1; i++){
			for(int j=1; j<width-1; j++){

				sxy = cvGet2D(imagexy_bef,i,j);
				sz = cvGet2D(imagez_bef,i,j);

				s1xy = cvGet2D(imagexy,i,j);
				s2xy = cvGet2D(imagexy,i+1,j);
				s3xy = cvGet2D(imagexy,i,j+1);
				s4xy = cvGet2D(imagexy,i+1,j+1);
				s5xy = cvGet2D(imagexy,i-1,j);
				s6xy = cvGet2D(imagexy,i,j-1);
				s7xy = cvGet2D(imagexy,i-1,j-1);
				s8xy = cvGet2D(imagexy,i+1,j-1);
				s9xy = cvGet2D(imagexy,i-1,j+1);

				suma = s2xy.val[0] + s3xy.val[0] + s4xy.val[0] + s5xy.val[0] + s6xy.val[0] + s7xy.val[0] + s8xy.val[0] + s9xy.val[0];

				s1z = cvGet2D(imagez,i,j);
				s2z = cvGet2D(imagez,i+1,j);
				s3z = cvGet2D(imagez,i,j+1);
				s4z = cvGet2D(imagez,i+1,j+1);
				s5z = cvGet2D(imagez,i-1,j);
				s6z = cvGet2D(imagez,i,j-1);
				s7z = cvGet2D(imagez,i-1,j-1);
				s8z = cvGet2D(imagez,i+1,j-1);
				s9z = cvGet2D(imagez,i-1,j+1);

				suma2 = s2z.val[0] + s3z.val[0] + s4z.val[0] + s5z.val[0] + s6z.val[0] + s7z.val[0] + s8z.val[0] + s9z.val[0]; 

				if((s1xy.val[0]>0 && suma == 0) && ui.filter1->isChecked()){
					s1xy.val[0] = 0;
					cvSet2D(imagexy,i,j,s1xy);
				}
				if( (s1z.val[0]>0 && suma2 == 0) && ui.filter1->isChecked()){
					s1z.val[0] = 0;
					cvSet2D(imagez,i,j,s1z);
				}
				if(sxy.val[0] != s1xy.val[0] && ui.filter2->isChecked()){
					s1xy.val[0] = 0;
					cvSet2D(imagexy,i,j,s1xy);
				}
				if( sz.val[0] != s1z.val[0] && ui.filter2->isChecked()){
					s1z.val[0] = 0;
					cvSet2D(imagez,i,j,s1z);
				}
			}
		}
		*/
}

/**
* Devuelve la media del arreglo
*
* int arrelo[20]: Arreglo a promedia
* int cant_prom: Cantidad de datos a promediar
*/
double mean_all(double arrelo[20], int cant_prom){
	double media=0;
	int largo = 0;
	for(int i = 0; i<cant_prom; i++){
		if(arrelo[i] == 0) break;
		media += arrelo[i];
		largo++;
	}
	if(largo == 0) largo = 1;
	media = media/largo;
	return media;
}

/**
* Lee los parámetros de calibración para grandes numeros
* desde el archivo
*/
void Fress::read_calibparam(){
	string line;
	ifstream myfile("C:\\Mach3\\calibparams.txt");
	double value;

	for(int i = 0; i<10; i++){
		if (myfile.is_open())
		{
			myfile >> line;
			const char *line_char = line.c_str();
			value = atof(line_char);
			calibparam[i] = value;
			
		}else{
			calibparam[i] = 1.;
		}
	}
	QString aux;
	aux.setNum(calibparam[0]);
	ui.x40->setText(aux);
	aux.setNum(calibparam[1]);
	ui.xm40->setText(aux);
	aux.setNum(calibparam[2]);
	ui.y40->setText(aux);
	aux.setNum(calibparam[3]);
	ui.ym40->setText(aux);
	aux.setNum(calibparam[4]);
	ui.z40->setText(aux);
	aux.setNum(calibparam[5]);
	ui.zm40->setText(aux);

	aux.setNum(calibparam[6]);
	ui.x40e->setText(aux);
	aux.setNum(calibparam[7]);
	ui.xm40e->setText(aux);
	aux.setNum(calibparam[8]);
	ui.y40e->setText(aux);
	aux.setNum(calibparam[9]);
	ui.ym40e->setText(aux);

	myfile.close();
}

/**
* Guarda los parámetros de calibración en un archivo para
* que la configuración que registrar al reiniciar el software
**/
void Fress::on_savecalib40_clicked(){

	calibparam[0] = ui.x40->text().toDouble();
	calibparam[1] = ui.xm40->text().toDouble();
	calibparam[2] = ui.y40->text().toDouble();
	calibparam[3] = ui.ym40->text().toDouble();
	calibparam[4] = ui.z40->text().toDouble();
	calibparam[5] = ui.zm40->text().toDouble();

	calibparam[6] = ui.y40e->text().toDouble();
	calibparam[7] = ui.ym40e->text().toDouble();
	calibparam[8] = ui.x40e->text().toDouble();
	calibparam[9] = ui.xm40e->text().toDouble();

	ofstream myfile("C:\\Mach3\\calibparams.txt");

	if (myfile.is_open())
	{
		
		myfile << calibparam[0];
		myfile << "\n";
		myfile << calibparam[1];
		myfile << "\n";
		myfile << calibparam[2];
		myfile << "\n";
		myfile << calibparam[3];
		myfile << "\n";
		myfile << calibparam[4];
		myfile << "\n";
		myfile << calibparam[5];
		myfile << "\n";
		myfile << calibparam[6];
		myfile << "\n";
		myfile << calibparam[7];
		myfile << "\n";
		myfile << calibparam[8];
		myfile << "\n";
		myfile << calibparam[9];
		myfile << "\n";

		myfile.close();
	}
}

/**
* Función que lee parámetros de un csv
**/
void lastposition(){
	float x1=0, x2=0, y1=0, y2=0, z1=0, z2=0, e1=0, e2=0, e3=0;
	const char filename[] = "C:\\Mach3\\posiciones.csv";
	FILE *file = fopen(filename,"r");
	fseek(file, -(sizeof(float)*6+12*sizeof(unsigned char)), SEEK_END);
	
	xmach2=xmach1; 
	ymach2=ymach1; 
	zmach2=zmach1;

	xcam2=xcam1; 
	ycam2=ycam1; 
	zcam2=zcam1;

	/*while(fscanf(file,"%f,%f,%f,%f,%f,%f,%f,%f,%f",&xcam1,&xmach1,&ycam1,&ymach1,&zcam1,&zmach1,&e1,&e2,&e3) != EOF){
	}*/
	fscanf(file,"%f,%f,%f,%f,%f,%f",&xcam1,&xmach1,&ycam1,&ymach1,&zcam1,&zmach1);
	fclose(file);
}