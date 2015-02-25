/****************************************************************************
** Meta object code from reading C++ file 'qtoutputscene.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Gearwheel/qtoutputscene.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtoutputscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GearwheelOutputView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   21,   20,   20, 0x05,
      49,   20,   20,   20, 0x05,
      58,   20,   20,   20, 0x05,
      68,   20,   20,   20, 0x05,
      81,   20,   20,   20, 0x05,
      96,   94,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     115,   20,   20,   20, 0x0a,
     136,   20,   20,   20, 0x0a,
     153,   94,   20,   20, 0x0a,
     177,   94,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GearwheelOutputView[] = {
    "GearwheelOutputView\0\0x,y\0"
    "changePosition(int,int)\0zoomIn()\0"
    "zoomOut()\0rotateFine()\0rotateFull()\0"
    "x\0changeSpeed(float)\0rotationTimerEvent()\0"
    "toggleRotation()\0speedSliderChanged(int)\0"
    "changeSteps(int)\0"
};

void GearwheelOutputView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GearwheelOutputView *_t = static_cast<GearwheelOutputView *>(_o);
        switch (_id) {
        case 0: _t->changePosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->zoomIn(); break;
        case 2: _t->zoomOut(); break;
        case 3: _t->rotateFine(); break;
        case 4: _t->rotateFull(); break;
        case 5: _t->changeSpeed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->rotationTimerEvent(); break;
        case 7: _t->toggleRotation(); break;
        case 8: _t->speedSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->changeSteps((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GearwheelOutputView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GearwheelOutputView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_GearwheelOutputView,
      qt_meta_data_GearwheelOutputView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GearwheelOutputView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GearwheelOutputView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GearwheelOutputView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GearwheelOutputView))
        return static_cast<void*>(const_cast< GearwheelOutputView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int GearwheelOutputView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void GearwheelOutputView::changePosition(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GearwheelOutputView::zoomIn()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void GearwheelOutputView::zoomOut()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void GearwheelOutputView::rotateFine()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void GearwheelOutputView::rotateFull()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void GearwheelOutputView::changeSpeed(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
