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
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x0a,
      52,   48,   26,   26, 0x0a,
      70,   26,   26,   26, 0x0a,
      83,   26,   26,   26, 0x0a,
      97,   26,   26,   26, 0x0a,
     112,   26,   26,   26, 0x0a,
     143,  136,   26,   26, 0x0a,
     160,   26,   26,   26, 0x0a,
     175,  173,   26,   26, 0x0a,
     192,   26,   26,   26, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GearwheelOutputController[] = {
    "GearwheelOutputController\0\0"
    "rotationTimerEvent()\0x,y\0moveItem(int,int)\0"
    "zoomItemIn()\0zoomItemOut()\0rotateSingle()\0"
    "toggleSecondGearwheel()\0newDeg\0"
    "changeSpeed(int)\0rotate_fwd()\0x\0"
    "changeSteps(int)\0toggleRotation()\0"
};

void GearwheelOutputController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GearwheelOutputController *_t = static_cast<GearwheelOutputController *>(_o);
        switch (_id) {
        case 0: _t->rotationTimerEvent(); break;
        case 1: _t->moveItem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->zoomItemIn(); break;
        case 3: _t->zoomItemOut(); break;
        case 4: _t->rotateSingle(); break;
        case 5: _t->toggleSecondGearwheel(); break;
        case 6: _t->changeSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->rotate_fwd(); break;
        case 8: _t->changeSteps((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->toggleRotation(); break;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
