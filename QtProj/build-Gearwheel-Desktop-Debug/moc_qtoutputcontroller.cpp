/****************************************************************************
** Meta object code from reading C++ file 'qtoutputcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Gearwheel/qtoutputcontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtoutputcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GearwheelOutputController_t {
    QByteArrayData data[10];
    char stringdata[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GearwheelOutputController_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GearwheelOutputController_t qt_meta_stringdata_GearwheelOutputController = {
    {
QT_MOC_LITERAL(0, 0, 25),
QT_MOC_LITERAL(1, 26, 8),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 1),
QT_MOC_LITERAL(4, 38, 1),
QT_MOC_LITERAL(5, 40, 10),
QT_MOC_LITERAL(6, 51, 11),
QT_MOC_LITERAL(7, 63, 12),
QT_MOC_LITERAL(8, 76, 21),
QT_MOC_LITERAL(9, 98, 10)
    },
    "GearwheelOutputController\0moveItem\0\0"
    "x\0y\0zoomItemIn\0zoomItemOut\0rotateSingle\0"
    "toggleSecondGearwheel\0rotate_fwd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GearwheelOutputController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x0a /* Public */,
       5,    0,   49,    2, 0x0a /* Public */,
       6,    0,   50,    2, 0x0a /* Public */,
       7,    0,   51,    2, 0x0a /* Public */,
       8,    0,   52,    2, 0x0a /* Public */,
       9,    0,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GearwheelOutputController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GearwheelOutputController *_t = static_cast<GearwheelOutputController *>(_o);
        switch (_id) {
        case 0: _t->moveItem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->zoomItemIn(); break;
        case 2: _t->zoomItemOut(); break;
        case 3: _t->rotateSingle(); break;
        case 4: _t->toggleSecondGearwheel(); break;
        case 5: _t->rotate_fwd(); break;
        default: ;
        }
    }
}

const QMetaObject GearwheelOutputController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GearwheelOutputController.data,
      qt_meta_data_GearwheelOutputController,  qt_static_metacall, 0, 0}
};


const QMetaObject *GearwheelOutputController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GearwheelOutputController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GearwheelOutputController.stringdata))
        return static_cast<void*>(const_cast< GearwheelOutputController*>(this));
    return QObject::qt_metacast(_clname);
}

int GearwheelOutputController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
