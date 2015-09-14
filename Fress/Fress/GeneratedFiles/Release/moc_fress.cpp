/****************************************************************************
** Meta object code from reading C++ file 'fress.h'
**
** Created: Tue 10. Jul 02:21:58 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../fress.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fress.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Fress[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x08,
      33,    6,    6,    6, 0x08,
      51,    6,    6,    6, 0x08,
      59,    6,    6,    6, 0x08,
      78,    6,    6,    6, 0x08,
      96,    6,    6,    6, 0x08,
     114,    6,    6,    6, 0x08,
     133,    6,    6,    6, 0x08,
     158,    6,    6,    6, 0x08,
     173,    6,    6,    6, 0x08,
     188,    6,    6,    6, 0x08,
     203,    6,    6,    6, 0x08,
     221,    6,    6,    6, 0x08,
     233,    6,    6,    6, 0x08,
     306,  247,    6,    6, 0x08,
     377,  366,    6,    6, 0x08,
     401,    6,    6,    6, 0x08,
     419,    6,    6,    6, 0x08,
     438,    6,    6,    6, 0x08,
     468,  463,    6,    6, 0x08,
     485,  463,    6,    6, 0x08,
     503,  463,    6,    6, 0x08,
     527,  463,    6,    6, 0x08,
     565,  560,  552,    6, 0x08,
     581,    6,    6,    6, 0x08,
     597,    6,    6,    6, 0x08,
     618,    6,    6,    6, 0x08,
     678,  640,    6,    6, 0x08,
     726,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Fress[] = {
    "Fress\0\0on_posiciones_2_clicked()\0"
    "on_exit_clicked()\0about()\0on_Start_clicked()\0"
    "on_Stop_clicked()\0on_Show_clicked()\0"
    "on_Close_clicked()\0on_calibration_clicked()\0"
    "on_R_clicked()\0on_G_clicked()\0"
    "on_B_clicked()\0on_save_clicked()\0"
    "rvertical()\0rhorizontal()\0"
    "frame_horizontal,frame_vertical,imgHSVh1,imgHSVv1,i,method\0"
    "posxyz(IplImage*,IplImage*,IplImage*,IplImage*,double*,int)\0"
    "image,file\0write(IplImage*,string)\0"
    "on_Open_clicked()\0on_set_0_clicked()\0"
    "on_savecalib40_clicked()\0file\0"
    "readfile(string)\0writefile(string)\0"
    "readmodificable(string)\0"
    "writemodificable(string)\0double*\0path\0"
    "readint(string)\0read_pixel2mm()\0"
    "camera_calibration()\0camera_calibration2()\0"
    "imagexy,imagez,imagexy_bef,imagez_bef\0"
    "filter(IplImage*,IplImage*,IplImage*,IplImage*)\0"
    "read_calibparam()\0"
};

void Fress::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Fress *_t = static_cast<Fress *>(_o);
        switch (_id) {
        case 0: _t->on_posiciones_2_clicked(); break;
        case 1: _t->on_exit_clicked(); break;
        case 2: _t->about(); break;
        case 3: _t->on_Start_clicked(); break;
        case 4: _t->on_Stop_clicked(); break;
        case 5: _t->on_Show_clicked(); break;
        case 6: _t->on_Close_clicked(); break;
        case 7: _t->on_calibration_clicked(); break;
        case 8: _t->on_R_clicked(); break;
        case 9: _t->on_G_clicked(); break;
        case 10: _t->on_B_clicked(); break;
        case 11: _t->on_save_clicked(); break;
        case 12: _t->rvertical(); break;
        case 13: _t->rhorizontal(); break;
        case 14: _t->posxyz((*reinterpret_cast< IplImage*(*)>(_a[1])),(*reinterpret_cast< IplImage*(*)>(_a[2])),(*reinterpret_cast< IplImage*(*)>(_a[3])),(*reinterpret_cast< IplImage*(*)>(_a[4])),(*reinterpret_cast< double*(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 15: _t->write((*reinterpret_cast< IplImage*(*)>(_a[1])),(*reinterpret_cast< string(*)>(_a[2]))); break;
        case 16: _t->on_Open_clicked(); break;
        case 17: _t->on_set_0_clicked(); break;
        case 18: _t->on_savecalib40_clicked(); break;
        case 19: _t->readfile((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 20: _t->writefile((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 21: _t->readmodificable((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 22: _t->writemodificable((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 23: { double* _r = _t->readint((*reinterpret_cast< string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double**>(_a[0]) = _r; }  break;
        case 24: _t->read_pixel2mm(); break;
        case 25: _t->camera_calibration(); break;
        case 26: _t->camera_calibration2(); break;
        case 27: _t->filter((*reinterpret_cast< IplImage*(*)>(_a[1])),(*reinterpret_cast< IplImage*(*)>(_a[2])),(*reinterpret_cast< IplImage*(*)>(_a[3])),(*reinterpret_cast< IplImage*(*)>(_a[4]))); break;
        case 28: _t->read_calibparam(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Fress::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Fress::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Fress,
      qt_meta_data_Fress, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Fress::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Fress::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Fress::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Fress))
        return static_cast<void*>(const_cast< Fress*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Fress::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
