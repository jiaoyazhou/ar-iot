/****************************************************************************
** Meta object code from reading C++ file 'expertinfo_window.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/expertinfo_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'expertinfo_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_expertinfo_window[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x09,
      43,   18,   18,   18, 0x09,
      69,   18,   18,   18, 0x09,
      93,   18,   18,   18, 0x09,
     127,  117,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_expertinfo_window[] = {
    "expertinfo_window\0\0button_search_clicked()\0"
    "button_increate_clicked()\0"
    "button_update_clicked()\0button_delete_clicked()\0"
    "InputInfo\0receiveData(ST_ExpertInfo)\0"
};

void expertinfo_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        expertinfo_window *_t = static_cast<expertinfo_window *>(_o);
        switch (_id) {
        case 0: _t->button_search_clicked(); break;
        case 1: _t->button_increate_clicked(); break;
        case 2: _t->button_update_clicked(); break;
        case 3: _t->button_delete_clicked(); break;
        case 4: _t->receiveData((*reinterpret_cast< ST_ExpertInfo(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData expertinfo_window::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject expertinfo_window::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_expertinfo_window,
      qt_meta_data_expertinfo_window, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &expertinfo_window::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *expertinfo_window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *expertinfo_window::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_expertinfo_window))
        return static_cast<void*>(const_cast< expertinfo_window*>(this));
    return QWidget::qt_metacast(_clname);
}

int expertinfo_window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
