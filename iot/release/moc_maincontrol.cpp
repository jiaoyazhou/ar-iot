/****************************************************************************
** Meta object code from reading C++ file 'maincontrol.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/maincontrol.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maincontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_maincontrol[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      24,   12,   12,   12, 0x08,
      37,   12,   12,   12, 0x08,
      53,   12,   49,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_maincontrol[] = {
    "maincontrol\0\0btnClick()\0UpdateData()\0"
    "OnComRead()\0int\0get_realdata()\0"
};

void maincontrol::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        maincontrol *_t = static_cast<maincontrol *>(_o);
        switch (_id) {
        case 0: _t->btnClick(); break;
        case 1: _t->UpdateData(); break;
        case 2: _t->OnComRead(); break;
        case 3: { int _r = _t->get_realdata();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData maincontrol::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject maincontrol::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_maincontrol,
      qt_meta_data_maincontrol, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &maincontrol::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *maincontrol::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *maincontrol::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_maincontrol))
        return static_cast<void*>(const_cast< maincontrol*>(this));
    return QWidget::qt_metacast(_clname);
}

int maincontrol::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
