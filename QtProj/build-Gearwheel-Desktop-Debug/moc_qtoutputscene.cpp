/****************************************************************************
** Meta object code from reading C++ file 'qtoutputscene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Gearwheel/qtoutputscene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtoutputscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GearwheelOutputView_t {
    QByteArrayData data[11];
    char stringdata[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GearwheelOutputView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GearwheelOutputView_t qt_meta_stringdata_GearwheelOutputView = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 14),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 1),
QT_MOC_LITERAL(4, 38, 1),
QT_MOC_LITERAL(5, 40, 6),
QT_MOC_LITERAL(6, 47, 7),
QT_MOC_LITERAL(7, 55, 10),
QT_MOC_LITERAL(8, 66, 10),
QT_MOC_LITERAL(9, 77, 18),
QT_MOC_LITERAL(10, 96, 14)
    },
    "GearwheelOutputView\0changePosition\0\0"
    "x\0y\0zoomIn\0zoomOut\0rotateFine\0rotateFull\0"
    "rotationTimerEvent\0toggleRotation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GearwheelOutputView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       5,    0,   54,    2, 0x06 /* Public */,
       6,    0,   55,    2, 0x06 /* Public */,
       7,    0,   56,    2, 0x06 /* Public */,
       8,    0,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   58,    2, 0x0a /* Public */,
      10,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GearwheelOutputView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GearwheelOutputView *_t = static_cast<GearwheelOutputView *>(_o);
        switch (_id) {
        case 0: _t->changePosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->zoomIn(); break;
        case 2: _t->zoomOut(); break;
        case 3: _t->rotateFine(); break;
        case 4: _t->rotateFull(); break;
        case 5: _t->rotationTimerEvent(); break;
        case 6: _t->toggleRotation(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GearwheelOutputView::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GearwheelOutputView::changePosition)) {
                *result = 0;
            }
        }
        {
            typedef void (GearwheelOutputView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GearwheelOutputView::zoomIn)) {
                *result = 1;
            }
        }
        {
            typedef void (GearwheelOutputView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GearwheelOutputView::zoomOut)) {
                *result = 2;
            }
        }
        {
            typedef void (GearwheelOutputView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GearwheelOutputView::rotateFine)) {
                *result = 3;
            }
        }
        {
            typedef void (GearwheelOutputView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GearwheelOutputView::rotateFull)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject GearwheelOutputView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_GearwheelOutputView.data,
      qt_meta_data_GearwheelOutputView,  qt_static_metacall, 0, 0}
};


const QMetaObject *GearwheelOutputView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GearwheelOutputView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GearwheelOutputView.stringdata))
        return static_cast<void*>(const_cast< GearwheelOutputView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int GearwheelOutputView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
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
QT_END_MOC_NAMESPACE
