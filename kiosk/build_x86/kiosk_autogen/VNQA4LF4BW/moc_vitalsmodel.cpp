/****************************************************************************
** Meta object code from reading C++ file 'vitalsmodel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/model/vitalsmodel.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vitalsmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSVitalsModelENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSVitalsModelENDCLASS = QtMocHelpers::stringData(
    "VitalsModel",
    "updated",
    "",
    "setSpo2",
    "v",
    "setPulseRate",
    "bpm",
    "setTemperature",
    "t"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSVitalsModelENDCLASS_t {
    uint offsetsAndSizes[18];
    char stringdata0[12];
    char stringdata1[8];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[2];
    char stringdata5[13];
    char stringdata6[4];
    char stringdata7[15];
    char stringdata8[2];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSVitalsModelENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSVitalsModelENDCLASS_t qt_meta_stringdata_CLASSVitalsModelENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "VitalsModel"
        QT_MOC_LITERAL(12, 7),  // "updated"
        QT_MOC_LITERAL(20, 0),  // ""
        QT_MOC_LITERAL(21, 7),  // "setSpo2"
        QT_MOC_LITERAL(29, 1),  // "v"
        QT_MOC_LITERAL(31, 12),  // "setPulseRate"
        QT_MOC_LITERAL(44, 3),  // "bpm"
        QT_MOC_LITERAL(48, 14),  // "setTemperature"
        QT_MOC_LITERAL(63, 1)   // "t"
    },
    "VitalsModel",
    "updated",
    "",
    "setSpo2",
    "v",
    "setPulseRate",
    "bpm",
    "setTemperature",
    "t"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSVitalsModelENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,   39,    2, 0x0a,    2 /* Public */,
       5,    1,   42,    2, 0x0a,    4 /* Public */,
       7,    1,   45,    2, 0x0a,    6 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Float,    8,

       0        // eod
};

Q_CONSTINIT const QMetaObject VitalsModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSVitalsModelENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSVitalsModelENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSVitalsModelENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<VitalsModel, std::true_type>,
        // method 'updated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setSpo2'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setPulseRate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setTemperature'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>
    >,
    nullptr
} };

void VitalsModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VitalsModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updated(); break;
        case 1: _t->setSpo2((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->setPulseRate((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->setTemperature((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VitalsModel::*)();
            if (_t _q_method = &VitalsModel::updated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *VitalsModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VitalsModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSVitalsModelENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VitalsModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void VitalsModel::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
