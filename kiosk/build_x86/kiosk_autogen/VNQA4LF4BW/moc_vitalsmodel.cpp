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
    "value",
    "unit",
    "spo2Changed",
    "spo2",
    "pulse",
    "weightChanged",
    "weight",
    "heightChanged",
    "height",
    "nibpChanged",
    "sys",
    "dia",
    "map",
    "nibpPressureChanged",
    "pressure",
    "visionChanged",
    "near",
    "far",
    "visionFinal",
    "temperatureFinal",
    "spo2Final",
    "weightFinal",
    "heightFinal",
    "nibpFinal",
    "setTemperature",
    "setSpO2",
    "setWeight",
    "setHeight",
    "setNIBP",
    "setNibpPressure",
    "setNearVision",
    "result",
    "setFarVision"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSVitalsModelENDCLASS_t {
    uint offsetsAndSizes[72];
    char stringdata0[12];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[5];
    char stringdata5[12];
    char stringdata6[5];
    char stringdata7[6];
    char stringdata8[14];
    char stringdata9[7];
    char stringdata10[14];
    char stringdata11[7];
    char stringdata12[12];
    char stringdata13[4];
    char stringdata14[4];
    char stringdata15[4];
    char stringdata16[20];
    char stringdata17[9];
    char stringdata18[14];
    char stringdata19[5];
    char stringdata20[4];
    char stringdata21[12];
    char stringdata22[17];
    char stringdata23[10];
    char stringdata24[12];
    char stringdata25[12];
    char stringdata26[10];
    char stringdata27[15];
    char stringdata28[8];
    char stringdata29[10];
    char stringdata30[10];
    char stringdata31[8];
    char stringdata32[16];
    char stringdata33[14];
    char stringdata34[7];
    char stringdata35[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSVitalsModelENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSVitalsModelENDCLASS_t qt_meta_stringdata_CLASSVitalsModelENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "VitalsModel"
        QT_MOC_LITERAL(12, 18),  // "temperatureChanged"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 5),  // "value"
        QT_MOC_LITERAL(38, 4),  // "unit"
        QT_MOC_LITERAL(43, 11),  // "spo2Changed"
        QT_MOC_LITERAL(55, 4),  // "spo2"
        QT_MOC_LITERAL(60, 5),  // "pulse"
        QT_MOC_LITERAL(66, 13),  // "weightChanged"
        QT_MOC_LITERAL(80, 6),  // "weight"
        QT_MOC_LITERAL(87, 13),  // "heightChanged"
        QT_MOC_LITERAL(101, 6),  // "height"
        QT_MOC_LITERAL(108, 11),  // "nibpChanged"
        QT_MOC_LITERAL(120, 3),  // "sys"
        QT_MOC_LITERAL(124, 3),  // "dia"
        QT_MOC_LITERAL(128, 3),  // "map"
        QT_MOC_LITERAL(132, 19),  // "nibpPressureChanged"
        QT_MOC_LITERAL(152, 8),  // "pressure"
        QT_MOC_LITERAL(161, 13),  // "visionChanged"
        QT_MOC_LITERAL(175, 4),  // "near"
        QT_MOC_LITERAL(180, 3),  // "far"
        QT_MOC_LITERAL(184, 11),  // "visionFinal"
        QT_MOC_LITERAL(196, 16),  // "temperatureFinal"
        QT_MOC_LITERAL(213, 9),  // "spo2Final"
        QT_MOC_LITERAL(223, 11),  // "weightFinal"
        QT_MOC_LITERAL(235, 11),  // "heightFinal"
        QT_MOC_LITERAL(247, 9),  // "nibpFinal"
        QT_MOC_LITERAL(257, 14),  // "setTemperature"
        QT_MOC_LITERAL(272, 7),  // "setSpO2"
        QT_MOC_LITERAL(280, 9),  // "setWeight"
        QT_MOC_LITERAL(290, 9),  // "setHeight"
        QT_MOC_LITERAL(300, 7),  // "setNIBP"
        QT_MOC_LITERAL(308, 15),  // "setNibpPressure"
        QT_MOC_LITERAL(324, 13),  // "setNearVision"
        QT_MOC_LITERAL(338, 6),  // "result"
        QT_MOC_LITERAL(345, 12)   // "setFarVision"
    },
    "VitalsModel",
    "temperatureChanged",
    "",
    "value",
    "unit",
    "spo2Changed",
    "spo2",
    "pulse",
    "weightChanged",
    "weight",
    "heightChanged",
    "height",
    "nibpChanged",
    "sys",
    "dia",
    "map",
    "nibpPressureChanged",
    "pressure",
    "visionChanged",
    "near",
    "far",
    "visionFinal",
    "temperatureFinal",
    "spo2Final",
    "weightFinal",
    "heightFinal",
    "nibpFinal",
    "setTemperature",
    "setSpO2",
    "setWeight",
    "setHeight",
    "setNIBP",
    "setNibpPressure",
    "setNearVision",
    "result",
    "setFarVision"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSVitalsModelENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  140,    2, 0x06,    1 /* Public */,
       5,    2,  145,    2, 0x06,    4 /* Public */,
       8,    1,  150,    2, 0x06,    7 /* Public */,
      10,    1,  153,    2, 0x06,    9 /* Public */,
      12,    3,  156,    2, 0x06,   11 /* Public */,
      16,    1,  163,    2, 0x06,   15 /* Public */,
      18,    2,  166,    2, 0x06,   17 /* Public */,
      21,    2,  171,    2, 0x06,   20 /* Public */,
      22,    1,  176,    2, 0x06,   23 /* Public */,
      23,    2,  179,    2, 0x06,   25 /* Public */,
      24,    1,  184,    2, 0x06,   28 /* Public */,
      25,    1,  187,    2, 0x06,   30 /* Public */,
      26,    2,  190,    2, 0x06,   32 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      27,    2,  195,    2, 0x0a,   35 /* Public */,
      28,    2,  200,    2, 0x0a,   38 /* Public */,
      29,    1,  205,    2, 0x0a,   41 /* Public */,
      30,    1,  208,    2, 0x0a,   43 /* Public */,
      31,    3,  211,    2, 0x0a,   45 /* Public */,
      32,    1,  218,    2, 0x0a,   49 /* Public */,
      33,    1,  221,    2, 0x0a,   51 /* Public */,
      35,    1,  224,    2, 0x0a,   53 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Char,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   14,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   19,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   19,   20,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   13,   14,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Char,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   14,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::QString,   34,
    QMetaType::Void, QMetaType::QString,   34,

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
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<char, std::false_type>,
        // method 'spo2Changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'weightChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'heightChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'nibpChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'nibpPressureChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'visionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'visionFinal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'temperatureFinal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'spo2Final'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'weightFinal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'heightFinal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'nibpFinal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setTemperature'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<char, std::false_type>,
        // method 'setSpO2'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setWeight'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'setHeight'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setNIBP'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setNibpPressure'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setNearVision'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'setFarVision'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>
    >,
    nullptr
} };

void VitalsModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VitalsModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->temperatureChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<char>>(_a[2]))); break;
        case 1: _t->spo2Changed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 2: _t->weightChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 3: _t->heightChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->nibpChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 5: _t->nibpPressureChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->visionChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 7: _t->visionFinal((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 8: _t->temperatureFinal((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 9: _t->spo2Final((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 10: _t->weightFinal((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 11: _t->heightFinal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->nibpFinal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 13: _t->setTemperature((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<char>>(_a[2]))); break;
        case 14: _t->setSpO2((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 15: _t->setWeight((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 16: _t->setHeight((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 17: _t->setNIBP((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 18: _t->setNibpPressure((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 19: _t->setNearVision((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->setFarVision((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VitalsModel::*)(double , char );
            if (_t _q_method = &VitalsModel::temperatureChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VitalsModel::*)(int , int );
            if (_t _q_method = &VitalsModel::spo2Changed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VitalsModel::*)(double );
            if (_t _q_method = &VitalsModel::weightChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (VitalsModel::*)(int );
            if (_t _q_method = &VitalsModel::heightChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (VitalsModel::*)(int , int , int );
            if (_t _q_method = &VitalsModel::nibpChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (VitalsModel::*)(int );
            if (_t _q_method = &VitalsModel::nibpPressureChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (VitalsModel::*)(const QString & , const QString & );
            if (_t _q_method = &VitalsModel::visionChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (VitalsModel::*)(const QString & , const QString & );
            if (_t _q_method = &VitalsModel::visionFinal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (VitalsModel::*)(double );
            if (_t _q_method = &VitalsModel::temperatureFinal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (VitalsModel::*)(int , int );
            if (_t _q_method = &VitalsModel::spo2Final; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (VitalsModel::*)(double );
            if (_t _q_method = &VitalsModel::weightFinal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (VitalsModel::*)(int );
            if (_t _q_method = &VitalsModel::heightFinal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (VitalsModel::*)(int , int );
            if (_t _q_method = &VitalsModel::nibpFinal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 12;
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
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void VitalsModel::temperatureChanged(double _t1, char _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VitalsModel::spo2Changed(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VitalsModel::weightChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VitalsModel::heightChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void VitalsModel::nibpChanged(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void VitalsModel::nibpPressureChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void VitalsModel::visionChanged(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void VitalsModel::visionFinal(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void VitalsModel::temperatureFinal(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void VitalsModel::spo2Final(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void VitalsModel::weightFinal(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void VitalsModel::heightFinal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void VitalsModel::nibpFinal(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_WARNING_POP
