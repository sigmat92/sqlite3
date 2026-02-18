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
    "setTemperature",
    "setSpO2",
    "setWeight",
    "setHeight",
    "setNIBP"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSVitalsModelENDCLASS_t {
    uint offsetsAndSizes[42];
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
    char stringdata16[15];
    char stringdata17[8];
    char stringdata18[10];
    char stringdata19[10];
    char stringdata20[8];
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
        QT_MOC_LITERAL(132, 14),  // "setTemperature"
        QT_MOC_LITERAL(147, 7),  // "setSpO2"
        QT_MOC_LITERAL(155, 9),  // "setWeight"
        QT_MOC_LITERAL(165, 9),  // "setHeight"
        QT_MOC_LITERAL(175, 7)   // "setNIBP"
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
    "setTemperature",
    "setSpO2",
    "setWeight",
    "setHeight",
    "setNIBP"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSVitalsModelENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   74,    2, 0x06,    1 /* Public */,
       5,    2,   79,    2, 0x06,    4 /* Public */,
       8,    1,   84,    2, 0x06,    7 /* Public */,
      10,    1,   87,    2, 0x06,    9 /* Public */,
      12,    3,   90,    2, 0x06,   11 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      16,    2,   97,    2, 0x0a,   15 /* Public */,
      17,    2,  102,    2, 0x0a,   18 /* Public */,
      18,    1,  107,    2, 0x0a,   21 /* Public */,
      19,    1,  110,    2, 0x0a,   23 /* Public */,
      20,    3,  113,    2, 0x0a,   25 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Char,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   14,   15,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Char,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   14,   15,

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
        QtPrivate::TypeAndForceComplete<int, std::false_type>
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
        case 5: _t->setTemperature((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<char>>(_a[2]))); break;
        case 6: _t->setSpO2((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 7: _t->setWeight((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 8: _t->setHeight((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->setNIBP((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
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
QT_WARNING_POP
