#include "calibration_x.h"

using std::ofstream;

double pos2 = 0;
int tipo_calibracion = 1;

Calibration::Calibration(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	ui.lineEdit->hide();
	i = 0;
	xyz = NULL;
	for(int i = 0; i<4; i++)
		xyz_ini[i] = -2;
}

/**
* Constructor vacío
**/
Calibration::~Calibration()
{

}

/**
* Función que despliega la pantalla y función de calibración
**/
void Calibration::on_next_clicked(){
	calibration1();
}

/**
* Setea la misma memoria para la posición xyz que la de la clase Fress
*
* double* xyz_s: Puntero a la memoria donde se encuentran las posiciones de x, y, z
**/
void Calibration::setXYZ(double* xyz_s){
	xyz = xyz_s;
	pos = xyz[0];
}

/**
* Setea la misma memoria para la posición pixel2mm que la de la clase Fress
*
* double* pixel2mm_ui: Puntero a la memoria donde se encuentran las transformaciones de pixeles a mm de x, y, z
**/
void Calibration::setPixel2mm(double* pixel2mm_ui){
	pixel2mm = pixel2mm_ui;
}

/**
* Escribe los parámetros de transformacion pixel2mm
*
* stringa path: String con el archivo donde se guardarán los datos
*/
void Calibration::writepixel2mm(string path){
	string line;
	ofstream myfile(path);
	if (myfile.is_open())
	{
		for(int i = 0; i<5; i++){
			myfile << pixel2mm[i];
			myfile << "\n";
		}
		for(int i = 0; i<4; i++){
			myfile << xyz_ini[i];
			myfile << "\n";
		}
	}
	myfile.close();
}

/**
* Función que estima el parámetro de transformación de pixeles a milímetros
* y lo guarda dentro de la memoria interna
**/
void Calibration::calibration1(){
	if(i == 0){
		ui.lineEdit->hide();
		ui.label->setText("Presiones Ok para continuar con la calibracion");
		ui.next->setText("OK");

		xyz_ini[0] = xyz[0];
		xyz_ini[1] = xyz[1];
		xyz_ini[2] = xyz[2];
		xyz_ini[3] = xyz[3];

	}else if(i == 1){
		pos = xyz[0];
		pos2 = xyz[1];
		//ui.lineEdit->show();
		ui.label->setText("Mueva 10mm positivo el eje x luego presione OK");
	}else if(i == 2){
		distance = 10.;//ui.lineEdit->text().toDouble();
		ui.label->setText("Mueva 10mm positivo el eje y luego presione OK");
		double value1, value2;
		value1 = abs(distance/(abs(pos)-abs(xyz[0])));
		value2 = (xyz[1]-pos2)/(xyz[0]-pos);

		pixel2mm[0] = value1;
		pixel2mm[4] = value2;

		pos = xyz[1];
		pos2 = xyz[0];
	}else if(i == 3){
		distance = 10.;//ui.lineEdit->text().toDouble();
		double value1, value2;
		value1 = abs(distance/(abs(pos)-abs(xyz[1])));
		value2 = (xyz[0]-pos2)/(xyz[1]-pos);

		pixel2mm[1] = value1;
		pixel2mm[3] = value2;

		ui.label->setText("Mueva 7mm positivo el eje z luego presione OK");
		pos = xyz[2];
	}else if(i==4){
		
		distance = 7;//ui.lineEdit->text().toDouble();
		double value = abs(distance/(abs(pos)-abs(xyz[2])));
		pixel2mm[2] = value;

		ui.label->setText("Calibración completada");
		ui.next->setText("Ok...");
		ui.lineEdit->hide();
	}else{
		ui.label->setText("Esta será la etapa de calibración de distancia\n, presiones OK para continuar");
		ui.next->setText("Ok");
		i = -1;
		writepixel2mm("C:\\Mach3\\pixel2unit.txt");
		close();
	}
	i++;
}