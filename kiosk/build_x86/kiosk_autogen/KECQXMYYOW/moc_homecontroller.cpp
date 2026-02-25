/****************************************************************************
** Meta object code from reading C++ file 'homecontroller.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/controller/homecontroller.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'homecontroller.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSHomeControllerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSHomeControllerENDCLASS = QtMocHelpers::stringData(
    "HomeController",
    "onTemperatureChanged",
    "",
    "value",
    "unit",
    "onSpO2Changed",
    "spo2",
    "pulse",
    "onStartSpo2Requested",
    "onSpO2Final",
    "onTemperatureFinal",
    "temp",
    "onWeightFinal",
    "weight",
    "onHeightFinal",
    "height",
    "onNIBPFinal",
    "sys",
    "dia"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSHomeControllerENDCLASS_t {
    uint offsetsAndSizes[38];
    char stringdata0[15];
    char stringdata1[21];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[5];
    char stringdata5[14];
    char stringdata6[5];
    char stringdata7[6];
    char stringdata8[21];
    char stringdata9[12];
    char stringdata10[19];
    char stringdata11[5];
    char stringdata12[14];
    char stringdata13[7];
    char stringdata14[14];
    char stringdata15[7];
    char stringdata16[12];
    char stringdata17[4];
    char stringdata18[4];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSHomeControllerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSHomeControllerENDCLASS_t qt_meta_stringdata_CLASSHomeControllerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "HomeController"
        QT_MOC_LITERAL(15, 20),  // "onTemperatureChanged"
        QT_MOC_LITERAL(36, 0),  // ""
        QT_MOC_LITERAL(37, 5),  // "value"
        QT_MOC_LITERAL(43, 4),  // "unit"
        QT_MOC_LITERAL(48, 13),  // "onSpO2Changed"
        QT_MOC_LITERAL(62, 4),  // "spo2"
        QT_MOC_LITERAL(67, 5),  // "pulse"
        QT_MOC_LITERAL(73, 20),  // "onStartSpo2Requested"
        QT_MOC_LITERAL(94, 11),  // "onSpO2Final"
        QT_MOC_LITERAL(106, 18),  // "onTemperatureFinal"
        QT_MOC_LITERAL(125, 4),  // "temp"
        QT_MOC_LITERAL(130, 13),  // "onWeightFinal"
        QT_MOC_LITERAL(144, 6),  // "weight"
        QT_MOC_LITERAL(151, 13),  // "onHeightFinal"
        QT_MOC_LITERAL(165, 6),  // "height"
        QT_MOC_LITERAL(172, 11),  // "onNIBPFinal"
        QT_MOC_LITERAL(184, 3),  // "sys"
        QT_MOC_LITERAL(188, 3)   // "dia"
    },
    "HomeController",
    "onTemperatureChanged",
    "",
    "value",
    "unit",
    "onSpO2Changed",
    "spo2",
    "pulse",
    "onStartSpo2Requested",
    "onSpO2Final",
    "onTemperatureFinal",
    "temp",
    "onWeightFinal",
    "weight",
    "onHeightFinal",
    "height",
    "onNIBPFinal",
    "sys",
    "dia"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSHomeControllerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   62,    2, 0x0a,    1 /* Public */,
       5,    2,   67,    2, 0x0a,    4 /* Public */,
       8,    0,   72,    2, 0x0a,    7 /* Public */,
       9,    2,   73,    2, 0x08,    8 /* Private */,
      10,    1,   78,    2, 0x08,   11 /* Private */,
      12,    1,   81,    2, 0x08,   13 /* Private */,
      14,    1,   84,    2, 0x08,   15 /* Private */,
      16,    2,   87,    2, 0x08,   17 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Char,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   17,   18,

       0        // eod
};

Q_CONSTINIT const QMetaObject HomeController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSHomeControllerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSHomeControllerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSHomeControllerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<HomeController, std::true_type>,
        // method 'onTemperatureChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<char, std::false_type>,
        // method 'onSpO2Changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onStartSpo2Requested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSpO2Final'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onTemperatureFinal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'onWeightFinal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'onHeightFinal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onNIBPFinal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void HomeController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HomeController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onTemperatureChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<char>>(_a[2]))); break;
        case 1: _t->onSpO2Changed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 2: _t->onStartSpo2Requested(); break;
        case 3: _t->onSpO2Final((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 4: _t->onTemperatureFinal((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 5: _t->onWeightFinal((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 6: _t->onHeightFinal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->onNIBPFinal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject *HomeController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HomeController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSHomeControllerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int HomeController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
