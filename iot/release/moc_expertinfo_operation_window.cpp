/****************************************************************************
** Meta object code from reading C++ file 'expertinfo_operation_window.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/expertinfo_operation_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'expertinfo_operation_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_expertinfo_operation_window[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      45,   29,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
      69,   28,   28,   28, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_expertinfo_operation_window[] = {
    "expertinfo_operation_window\0\0"
    "InputExpertInfo\0sendData(ST_ExpertInfo)\0"
    "ReturnInputInfo()\0"
};

void expertinfo_operation_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        expertinfo_operation_window *_t = static_cast<expertinfo_operation_window *>(_o);
        switch (_id) {
        case 0: _t->sendData((*reinterpret_cast< ST_ExpertInfo(*)>(_a[1]))); break;
        case 1: _t->ReturnInputInfo(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData expertinfo_operation_window::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject expertinfo_operation_window::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_expertinfo_operation_window,
      qt_meta_data_expertinfo_operation_window, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &expertinfo_operation_window::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *expertinfo_operation_window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *expertinfo_operation_window::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_expertinfo_operation_window))
        return static_cast<void*>(const_cast< expertinfo_operation_window*>(this));
    return QDialog::qt_metacast(_clname);
}

int expertinfo_operation_window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void expertinfo_operation_window::sendData(ST_ExpertInfo _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
