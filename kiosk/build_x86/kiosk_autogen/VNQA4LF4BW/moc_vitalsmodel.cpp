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
    "temperatureChanged",
    "",
    "t",
    "updated",
    "setSpo2",
    "v",
    "setPulseRate",
    "bpm",
    "setTemperature"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSVitalsModelENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[12];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[2];
    char stringdata4[8];
    char stringdata5[8];
    char stringdata6[2];
    char stringdata7[13];
    char stringdata8[4];
    char stringdata9[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSVitalsModelENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSVitalsModelENDCLASS_t qt_meta_stringdata_CLASSVitalsModelENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "VitalsModel"
        QT_MOC_LITERAL(12, 18),  // "temperatureChanged"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 1),  // "t"
        QT_MOC_LITERAL(34, 7),  // "updated"
        QT_MOC_LITERAL(42, 7),  // "setSpo2"
        QT_MOC_LITERAL(50, 1),  // "v"
        QT_MOC_LITERAL(52, 12),  // "setPulseRate"
        QT_MOC_LITERAL(65, 3),  // "bpm"
        QT_MOC_LITERAL(69, 14)   // "setTemperature"
    },
    "VitalsModel",
    "temperatureChanged",
    "",
    "t",
    "updated",
    "setSpo2",
    "v",
    "setPulseRate",
    "bpm",
    "setTemperature"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSVitalsModelENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x06,    1 /* Public */,
       4,    0,   47,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   48,    2, 0x0a,    4 /* Public */,
       7,    1,   51,    2, 0x0a,    6 /* Public */,
       9,    1,   54,    2, 0x0a,    8 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Float,    3,

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
        // method 'temperatureChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
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
        case 0: _t->temperatureChanged((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 1: _t->updated(); break;
        case 2: _t->setSpo2((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->setPulseRate((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->setTemperature((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VitalsModel::*)(float );
            if (_t _q_method = &VitalsModel::temperatureChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VitalsModel::*)();
            if (_t _q_method = &VitalsModel::updated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
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
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void VitalsModel::temperatureChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VitalsModel::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
