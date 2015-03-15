/****************************************************************************
** Meta object code from reading C++ file 'qtoutputcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Gearwheel/qtoutputcontroller.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtoutputcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GearwheelOutputController[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      33,   27,   26,   26, 0x05,
      60,   27,   26,   26, 0x05,

 // slots: signature, parameters, type, tag, flags
      92,   26,   26,   26, 0x0a,
     117,  113,   26,   26, 0x0a,
     135,   26,   26,   26, 0x0a,
     148,   26,   26,   26, 0x0a,
     162,   26,   26,   26, 0x0a,
     177,   26,   26,   26, 0x0a,
     201,   26,   26,   26, 0x0a,
     226,  219,   26,   26, 0x0a,
     243,   26,   26,   26, 0x0a,
     258,  256,   26,   26, 0x0a,
     275,   26,   26,   26, 0x0a,
     294,  292,   26,   26, 0x0a,
     316,  292,   26,   26, 0x0a,
     339,  256,   26,   26, 0x0a,
     355,   27,   26,   26, 0x0a,
     382,   27,   26,   26, 0x0a,
     413,   27,   26,   26, 0x0a,
     445,   27,   26,   26, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GearwheelOutputController[] = {
    "GearwheelOutputController\0\0state\0"
    "rotationStateChanged(bool)\0"
    "secondGearwheelVisChanged(bool)\0"
    "rotationTimerEvent()\0x,y\0moveItem(int,int)\0"
    "zoomItemIn()\0zoomItemOut()\0rotateSingle()\0"
    "toggleSecondGearwheel()\0centerGearwheel()\0"
    "newDeg\0changeSpeed(int)\0rotate_fwd()\0"
    "x\0changeSteps(int)\0toggleRotation()\0"
    "z\0changeToothcount(int)\0changeToothcount2(int)\0"
    "changeX(double)\0setDiameterVisibility(int)\0"
    "setFootdiameterVisibility(int)\0"
    "setOuterdiameterVisibility(int)\0"
    "setBasediameterVisibility(int)\0"
};

void GearwheelOutputController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GearwheelOutputController *_t = static_cast<GearwheelOutputController *>(_o);
        switch (_id) {
        case 0: _t->rotationStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->secondGearwheelVisChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->rotationTimerEvent(); break;
        case 3: _t->moveItem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->zoomItemIn(); break;
        case 5: _t->zoomItemOut(); break;
        case 6: _t->rotateSingle(); break;
        case 7: _t->toggleSecondGearwheel(); break;
        case 8: _t->centerGearwheel(); break;
        case 9: _t->changeSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->rotate_fwd(); break;
        case 11: _t->changeSteps((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->toggleRotation(); break;
        case 13: _t->changeToothcount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->changeToothcount2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->changeX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 16: _t->setDiameterVisibility((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->setFootdiameterVisibility((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->setOuterdiameterVisibility((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->setBasediameterVisibility((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GearwheelOutputController::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GearwheelOutputController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GearwheelOutputController,
      qt_meta_data_GearwheelOutputController, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GearwheelOutputController::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GearwheelOutputController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GearwheelOutputController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GearwheelOutputController))
        return static_cast<void*>(const_cast< GearwheelOutputController*>(this));
    return QObject::qt_metacast(_clname);
}

int GearwheelOutputController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void GearwheelOutputController::rotationStateChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GearwheelOutputController::secondGearwheelVisChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
