/****************************************************************************
** Meta object code from reading C++ file 'homeview.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/view/homeview.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'homeview.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSHomeViewENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSHomeViewENDCLASS = QtMocHelpers::stringData(
    "HomeView",
    "startSpo2Requested",
    "",
    "startTemperatureRequested",
    "startNIBPRequested",
    "startHeightRequested",
    "startWeightRequested",
    "visionTestRequested",
    "settingsRequested",
    "resetSessionRequested",
    "startPrintingRequested",
    "sessionId",
    "startSessionRequested",
    "name",
    "age",
    "mobile",
    "gender",
    "newSessionRequested",
    "setTemperatureBusy",
    "busy",
    "setSpO2Busy",
    "setNIBPBusy",
    "setHeightBusy",
    "setWeightBusy",
    "setTemperatureText",
    "text",
    "setNIBPText",
    "setNIBPPressure",
    "pressure",
    "setHeightText",
    "setWeightText",
    "setSpo2Text",
    "onVitalsUpdated",
    "spo2",
    "pulse"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSHomeViewENDCLASS_t {
    uint offsetsAndSizes[70];
    char stringdata0[9];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[26];
    char stringdata4[19];
    char stringdata5[21];
    char stringdata6[21];
    char stringdata7[20];
    char stringdata8[18];
    char stringdata9[22];
    char stringdata10[23];
    char stringdata11[10];
    char stringdata12[22];
    char stringdata13[5];
    char stringdata14[4];
    char stringdata15[7];
    char stringdata16[7];
    char stringdata17[20];
    char stringdata18[19];
    char stringdata19[5];
    char stringdata20[12];
    char stringdata21[12];
    char stringdata22[14];
    char stringdata23[14];
    char stringdata24[19];
    char stringdata25[5];
    char stringdata26[12];
    char stringdata27[16];
    char stringdata28[9];
    char stringdata29[14];
    char stringdata30[14];
    char stringdata31[12];
    char stringdata32[16];
    char stringdata33[5];
    char stringdata34[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSHomeViewENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSHomeViewENDCLASS_t qt_meta_stringdata_CLASSHomeViewENDCLASS = {
    {
        QT_MOC_LITERAL(0, 8),  // "HomeView"
        QT_MOC_LITERAL(9, 18),  // "startSpo2Requested"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 25),  // "startTemperatureRequested"
        QT_MOC_LITERAL(55, 18),  // "startNIBPRequested"
        QT_MOC_LITERAL(74, 20),  // "startHeightRequested"
        QT_MOC_LITERAL(95, 20),  // "startWeightRequested"
        QT_MOC_LITERAL(116, 19),  // "visionTestRequested"
        QT_MOC_LITERAL(136, 17),  // "settingsRequested"
        QT_MOC_LITERAL(154, 21),  // "resetSessionRequested"
        QT_MOC_LITERAL(176, 22),  // "startPrintingRequested"
        QT_MOC_LITERAL(199, 9),  // "sessionId"
        QT_MOC_LITERAL(209, 21),  // "startSessionRequested"
        QT_MOC_LITERAL(231, 4),  // "name"
        QT_MOC_LITERAL(236, 3),  // "age"
        QT_MOC_LITERAL(240, 6),  // "mobile"
        QT_MOC_LITERAL(247, 6),  // "gender"
        QT_MOC_LITERAL(254, 19),  // "newSessionRequested"
        QT_MOC_LITERAL(274, 18),  // "setTemperatureBusy"
        QT_MOC_LITERAL(293, 4),  // "busy"
        QT_MOC_LITERAL(298, 11),  // "setSpO2Busy"
        QT_MOC_LITERAL(310, 11),  // "setNIBPBusy"
        QT_MOC_LITERAL(322, 13),  // "setHeightBusy"
        QT_MOC_LITERAL(336, 13),  // "setWeightBusy"
        QT_MOC_LITERAL(350, 18),  // "setTemperatureText"
        QT_MOC_LITERAL(369, 4),  // "text"
        QT_MOC_LITERAL(374, 11),  // "setNIBPText"
        QT_MOC_LITERAL(386, 15),  // "setNIBPPressure"
        QT_MOC_LITERAL(402, 8),  // "pressure"
        QT_MOC_LITERAL(411, 13),  // "setHeightText"
        QT_MOC_LITERAL(425, 13),  // "setWeightText"
        QT_MOC_LITERAL(439, 11),  // "setSpo2Text"
        QT_MOC_LITERAL(451, 15),  // "onVitalsUpdated"
        QT_MOC_LITERAL(467, 4),  // "spo2"
        QT_MOC_LITERAL(472, 5)   // "pulse"
    },
    "HomeView",
    "startSpo2Requested",
    "",
    "startTemperatureRequested",
    "startNIBPRequested",
    "startHeightRequested",
    "startWeightRequested",
    "visionTestRequested",
    "settingsRequested",
    "resetSessionRequested",
    "startPrintingRequested",
    "sessionId",
    "startSessionRequested",
    "name",
    "age",
    "mobile",
    "gender",
    "newSessionRequested",
    "setTemperatureBusy",
    "busy",
    "setSpO2Busy",
    "setNIBPBusy",
    "setHeightBusy",
    "setWeightBusy",
    "setTemperatureText",
    "text",
    "setNIBPText",
    "setNIBPPressure",
    "pressure",
    "setHeightText",
    "setWeightText",
    "setSpo2Text",
    "onVitalsUpdated",
    "spo2",
    "pulse"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSHomeViewENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  152,    2, 0x06,    1 /* Public */,
       3,    0,  153,    2, 0x06,    2 /* Public */,
       4,    0,  154,    2, 0x06,    3 /* Public */,
       5,    0,  155,    2, 0x06,    4 /* Public */,
       6,    0,  156,    2, 0x06,    5 /* Public */,
       7,    0,  157,    2, 0x06,    6 /* Public */,
       8,    0,  158,    2, 0x06,    7 /* Public */,
       9,    0,  159,    2, 0x06,    8 /* Public */,
      10,    1,  160,    2, 0x06,    9 /* Public */,
      12,    4,  163,    2, 0x06,   11 /* Public */,
      17,    0,  172,    2, 0x06,   16 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      18,    1,  173,    2, 0x0a,   17 /* Public */,
      20,    1,  176,    2, 0x0a,   19 /* Public */,
      21,    1,  179,    2, 0x0a,   21 /* Public */,
      22,    1,  182,    2, 0x0a,   23 /* Public */,
      23,    1,  185,    2, 0x0a,   25 /* Public */,
      24,    1,  188,    2, 0x0a,   27 /* Public */,
      26,    1,  191,    2, 0x0a,   29 /* Public */,
      27,    1,  194,    2, 0x0a,   31 /* Public */,
      29,    1,  197,    2, 0x0a,   33 /* Public */,
      30,    1,  200,    2, 0x0a,   35 /* Public */,
      31,    1,  203,    2, 0x0a,   37 /* Public */,
      32,    2,  206,    2, 0x0a,   39 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::QString,   13,   14,   15,   16,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::Void, QMetaType::Int,   28,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   33,   34,

       0        // eod
};

Q_CONSTINIT const QMetaObject HomeView::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseView::staticMetaObject>(),
    qt_meta_stringdata_CLASSHomeViewENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSHomeViewENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSHomeViewENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<HomeView, std::true_type>,
        // method 'startSpo2Requested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startTemperatureRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startNIBPRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startHeightRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startWeightRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'visionTestRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'settingsRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resetSessionRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startPrintingRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'startSessionRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'newSessionRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setTemperatureBusy'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setSpO2Busy'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setNIBPBusy'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setHeightBusy'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setWeightBusy'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setTemperatureText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setNIBPText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setNIBPPressure'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setHeightText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setWeightText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setSpo2Text'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onVitalsUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void HomeView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HomeView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->startSpo2Requested(); break;
        case 1: _t->startTemperatureRequested(); break;
        case 2: _t->startNIBPRequested(); break;
        case 3: _t->startHeightRequested(); break;
        case 4: _t->startWeightRequested(); break;
        case 5: _t->visionTestRequested(); break;
        case 6: _t->settingsRequested(); break;
        case 7: _t->resetSessionRequested(); break;
        case 8: _t->startPrintingRequested((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->startSessionRequested((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 10: _t->newSessionRequested(); break;
        case 11: _t->setTemperatureBusy((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 12: _t->setSpO2Busy((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 13: _t->setNIBPBusy((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 14: _t->setHeightBusy((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 15: _t->setWeightBusy((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 16: _t->setTemperatureText((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 17: _t->setNIBPText((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 18: _t->setNIBPPressure((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 19: _t->setHeightText((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->setWeightText((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 21: _t->setSpo2Text((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 22: _t->onVitalsUpdated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HomeView::*)();
            if (_t _q_method = &HomeView::startSpo2Requested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (HomeView::*)();
            if (_t _q_method = &HomeView::startTemperatureRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (HomeView::*)();
            if (_t _q_method = &HomeView::startNIBPRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (HomeView::*)();
            if (_t _q_method = &HomeView::startHeightRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (HomeView::*)();
            if (_t _q_method = &HomeView::startWeightRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (HomeView::*)();
            if (_t _q_method = &HomeView::visionTestRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (HomeView::*)();
            if (_t _q_method = &HomeView::settingsRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (HomeView::*)();
            if (_t _q_method = &HomeView::resetSessionRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (HomeView::*)(int );
            if (_t _q_method = &HomeView::startPrintingRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (HomeView::*)(QString , int , QString , QString );
            if (_t _q_method = &HomeView::startSessionRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (HomeView::*)();
            if (_t _q_method = &HomeView::newSessionRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
    }
}

const QMetaObject *HomeView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HomeView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSHomeViewENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return BaseView::qt_metacast(_clname);
}

int HomeView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void HomeView::startSpo2Requested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void HomeView::startTemperatureRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void HomeView::startNIBPRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void HomeView::startHeightRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void HomeView::startWeightRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void HomeView::visionTestRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void HomeView::settingsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void HomeView::resetSessionRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void HomeView::startPrintingRequested(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void HomeView::startSessionRequested(QString _t1, int _t2, QString _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void HomeView::newSessionRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}
QT_WARNING_POP
