/****************************************************************************
** Meta object code from reading C++ file 'mctrtabchart1.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/mctrtabchart1.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mctrtabchart1.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mctrtabchart1[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x0a,
      39,   35,   14,   14, 0x0a,
      69,   14,   64,   14, 0x0a,
      94,   90,   14,   14, 0x0a,
     130,  125,   14,   14, 0x0a,
     153,  149,   14,   14, 0x0a,
     177,  171,   14,   14, 0x0a,
     195,  190,   14,   14, 0x0a,
     214,  207,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_mctrtabchart1[] = {
    "mctrtabchart1\0\0data\0addData(qreal)\0"
    "use\0setUseAntialiasing(bool)\0bool\0"
    "getUseAntialiasing()\0clr\0"
    "setHorizontalLineColor(QColor)\0show\0"
    "setShowPoint(bool)\0str\0setTitle(QString)\0"
    "iline\0setLine(int)\0iMax\0setMax(int)\0"
    "iValue\0setDecValue(int)\0"
};

void mctrtabchart1::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        mctrtabchart1 *_t = static_cast<mctrtabchart1 *>(_o);
        switch (_id) {
        case 0: _t->addData((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: _t->setUseAntialiasing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: { bool _r = _t->getUseAntialiasing();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: _t->setHorizontalLineColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 4: _t->setShowPoint((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setTitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->setLine((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setMax((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setDecValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData mctrtabchart1::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject mctrtabchart1::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_mctrtabchart1,
      qt_meta_data_mctrtabchart1, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mctrtabchart1::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mctrtabchart1::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mctrtabchart1::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mctrtabchart1))
        return static_cast<void*>(const_cast< mctrtabchart1*>(this));
    return QWidget::qt_metacast(_clname);
}

int mctrtabchart1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
