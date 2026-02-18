/****************************************************************************
** Meta object code from reading C++ file 'vitalsservice.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/service/vitalsservice.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vitalsservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.0. It"
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
struct qt_meta_stringdata_CLASSVitalsServiceENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSVitalsServiceENDCLASS = QtMocHelpers::stringData(
    "VitalsService",
    "temperatureReady",
    "",
    "value",
    "unit",
    "spo2Ready",
    "spo2",
    "pulse",
    "weightReady",
    "weight",
    "heightReady",
    "height",
    "nibpReady",
    "sys",
    "dia",
    "map",
    "sensorBusy",
    "name",
    "busy",
    "sensorMissing",
    "measurementFinished",
    "onTemperatureRaw",
    "onSpO2Raw",
    "onWeightRaw",
    "onHeightRaw",
    "onNibpRaw"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSVitalsServiceENDCLASS_t {
    uint offsetsAndSizes[52];
    char stringdata0[14];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[5];
    char stringdata5[10];
    char stringdata6[5];
    char stringdata7[6];
    char stringdata8[12];
    char stringdata9[7];
    char stringdata10[12];
    char stringdata11[7];
    char stringdata12[10];
    char stringdata13[4];
    char stringdata14[4];
    char stringdata15[4];
    char stringdata16[11];
    char stringdata17[5];
    char stringdata18[5];
    char stringdata19[14];
    char stringdata20[20];
    char stringdata21[17];
    char stringdata22[10];
    char stringdata23[12];
    char stringdata24[12];
    char stringdata25[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSVitalsServiceENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSVitalsServiceENDCLASS_t qt_meta_stringdata_CLASSVitalsServiceENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13),  // "VitalsService"
        QT_MOC_LITERAL(14, 16),  // "temperatureReady"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 5),  // "value"
        QT_MOC_LITERAL(38, 4),  // "unit"
        QT_MOC_LITERAL(43, 9),  // "spo2Ready"
        QT_MOC_LITERAL(53, 4),  // "spo2"
        QT_MOC_LITERAL(58, 5),  // "pulse"
        QT_MOC_LITERAL(64, 11),  // "weightReady"
        QT_MOC_LITERAL(76, 6),  // "weight"
        QT_MOC_LITERAL(83, 11),  // "heightReady"
        QT_MOC_LITERAL(95, 6),  // "height"
        QT_MOC_LITERAL(102, 9),  // "nibpReady"
        QT_MOC_LITERAL(112, 3),  // "sys"
        QT_MOC_LITERAL(116, 3),  // "dia"
        QT_MOC_LITERAL(120, 3),  // "map"
        QT_MOC_LITERAL(124, 10),  // "sensorBusy"
        QT_MOC_LITERAL(135, 4),  // "name"
        QT_MOC_LITERAL(140, 4),  // "busy"
        QT_MOC_LITERAL(145, 13),  // "sensorMissing"
        QT_MOC_LITERAL(159, 19),  // "measurementFinished"
        QT_MOC_LITERAL(179, 16),  // "onTemperatureRaw"
        QT_MOC_LITERAL(196, 9),  // "onSpO2Raw"
        QT_MOC_LITERAL(206, 11),  // "onWeightRaw"
        QT_MOC_LITERAL(218, 11),  // "onHeightRaw"
        QT_MOC_LITERAL(230, 9)   // "onNibpRaw"
    },
    "VitalsService",
    "temperatureReady",
    "",
    "value",
    "unit",
    "spo2Ready",
    "spo2",
    "pulse",
    "weightReady",
    "weight",
    "heightReady",
    "height",
    "nibpReady",
    "sys",
    "dia",
    "map",
    "sensorBusy",
    "name",
    "busy",
    "sensorMissing",
    "measurementFinished",
    "onTemperatureRaw",
    "onSpO2Raw",
    "onWeightRaw",
    "onHeightRaw",
    "onNibpRaw"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSVitalsServiceENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   92,    2, 0x06,    1 /* Public */,
       5,    2,   97,    2, 0x06,    4 /* Public */,
       8,    1,  102,    2, 0x06,    7 /* Public */,
      10,    1,  105,    2, 0x06,    9 /* Public */,
      12,    3,  108,    2, 0x06,   11 /* Public */,
      16,    2,  115,    2, 0x06,   15 /* Public */,
      19,    1,  120,    2, 0x06,   18 /* Public */,
      20,    0,  123,    2, 0x06,   20 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      21,    2,  124,    2, 0x0a,   21 /* Public */,
      22,    2,  129,    2, 0x0a,   24 /* Public */,
      23,    1,  134,    2, 0x0a,   27 /* Public */,
      24,    1,  137,    2, 0x0a,   29 /* Public */,
      25,    3,  140,    2, 0x0a,   31 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Char,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   14,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   17,   18,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Char,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   14,   15,

       0        // eod
};

Q_CONSTINIT const QMetaObject VitalsService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSVitalsServiceENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSVitalsServiceENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSVitalsServiceENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<VitalsService, std::true_type>,
        // method 'temperatureReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<char, std::false_type>,
        // method 'spo2Ready'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'weightReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'heightReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'nibpReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'sensorBusy'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'sensorMissing'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'measurementFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTemperatureRaw'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<char, std::false_type>,
        // method 'onSpO2Raw'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onWeightRaw'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'onHeightRaw'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onNibpRaw'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void VitalsService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VitalsService *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->temperatureReady((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<char>>(_a[2]))); break;
        case 1: _t->spo2Ready((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 2: _t->weightReady((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 3: _t->heightReady((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->nibpReady((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 5: _t->sensorBusy((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 6: _t->sensorMissing((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->measurementFinished(); break;
        case 8: _t->onTemperatureRaw((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<char>>(_a[2]))); break;
        case 9: _t->onSpO2Raw((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 10: _t->onWeightRaw((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 11: _t->onHeightRaw((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->onNibpRaw((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VitalsService::*)(double , char );
            if (_t _q_method = &VitalsService::temperatureReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VitalsService::*)(int , int );
            if (_t _q_method = &VitalsService::spo2Ready; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VitalsService::*)(double );
            if (_t _q_method = &VitalsService::weightReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (VitalsService::*)(int );
            if (_t _q_method = &VitalsService::heightReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (VitalsService::*)(int , int , int );
            if (_t _q_method = &VitalsService::nibpReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (VitalsService::*)(const QString & , bool );
            if (_t _q_method = &VitalsService::sensorBusy; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (VitalsService::*)(const QString & );
            if (_t _q_method = &VitalsService::sensorMissing; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (VitalsService::*)();
            if (_t _q_method = &VitalsService::measurementFinished; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject *VitalsService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VitalsService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSVitalsServiceENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VitalsService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void VitalsService::temperatureReady(double _t1, char _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VitalsService::spo2Ready(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VitalsService::weightReady(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VitalsService::heightReady(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void VitalsService::nibpReady(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void VitalsService::sensorBusy(const QString & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void VitalsService::sensorMissing(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void VitalsService::measurementFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
