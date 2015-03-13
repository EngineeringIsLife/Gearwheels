/****************************************************************************
** Meta object code from reading C++ file 'mainlayout.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Gearwheel/mainlayout.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainlayout.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainLayout[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   12,   11,   11, 0x0a,
      47,   12,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainLayout[] = {
    "MainLayout\0\0state\0gearwheelRotationState(bool)\0"
    "secondGWVisibility(bool)\0"
};

void MainLayout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainLayout *_t = static_cast<MainLayout *>(_o);
        switch (_id) {
        case 0: _t->gearwheelRotationState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->secondGWVisibility((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainLayout::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainLayout::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MainLayout,
      qt_meta_data_MainLayout, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainLayout::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainLayout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainLayout::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainLayout))
        return static_cast<void*>(const_cast< MainLayout*>(this));
    return QObject::qt_metacast(_clname);
}

int MainLayout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
