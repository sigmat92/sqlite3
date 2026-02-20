/****************************************************************************
** Meta object code from reading C++ file 'homeview.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/view/homeview.h"
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
    "startTemperatureRequested",
    "",
    "startSpo2Requested",
    "startNIBPRequested",
    "startHeightRequested",
    "startWeightRequested",
    "startVisionTestRequested",
    "startNewTestRequested",
    "startSettingsRequested",
    "startPrintingRequested",
    "visionTestRequested",
    "settingsRequested",
    "onVitalsUpdated",
    "spo2",
    "pulse"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSHomeViewENDCLASS_t {
    uint offsetsAndSizes[32];
    char stringdata0[9];
    char stringdata1[26];
    char stringdata2[1];
    char stringdata3[19];
    char stringdata4[19];
    char stringdata5[21];
    char stringdata6[21];
    char stringdata7[25];
    char stringdata8[22];
    char stringdata9[23];
    char stringdata10[23];
    char stringdata11[20];
    char stringdata12[18];
    char stringdata13[16];
    char stringdata14[5];
    char stringdata15[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSHomeViewENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSHomeViewENDCLASS_t qt_meta_stringdata_CLASSHomeViewENDCLASS = {
    {
        QT_MOC_LITERAL(0, 8),  // "HomeView"
        QT_MOC_LITERAL(9, 25),  // "startTemperatureRequested"
        QT_MOC_LITERAL(35, 0),  // ""
        QT_MOC_LITERAL(36, 18),  // "startSpo2Requested"
        QT_MOC_LITERAL(55, 18),  // "startNIBPRequested"
        QT_MOC_LITERAL(74, 20),  // "startHeightRequested"
        QT_MOC_LITERAL(95, 20),  // "startWeightRequested"
        QT_MOC_LITERAL(116, 24),  // "startVisionTestRequested"
        QT_MOC_LITERAL(141, 21),  // "startNewTestRequested"
        QT_MOC_LITERAL(163, 22),  // "startSettingsRequested"
        QT_MOC_LITERAL(186, 22),  // "startPrintingRequested"
        QT_MOC_LITERAL(209, 19),  // "visionTestRequested"
        QT_MOC_LITERAL(229, 17),  // "settingsRequested"
        QT_MOC_LITERAL(247, 15),  // "onVitalsUpdated"
        QT_MOC_LITERAL(263, 4),  // "spo2"
        QT_MOC_LITERAL(268, 5)   // "pulse"
    },
    "HomeView",
    "startTemperatureRequested",
    "",
    "startSpo2Requested",
    "startNIBPRequested",
    "startHeightRequested",
    "startWeightRequested",
    "startVisionTestRequested",
    "startNewTestRequested",
    "startSettingsRequested",
    "startPrintingRequested",
    "visionTestRequested",
    "settingsRequested",
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
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x06,    1 /* Public */,
       3,    0,   87,    2, 0x06,    2 /* Public */,
       4,    0,   88,    2, 0x06,    3 /* Public */,
       5,    0,   89,    2, 0x06,    4 /* Public */,
       6,    0,   90,    2, 0x06,    5 /* Public */,
       7,    0,   91,    2, 0x06,    6 /* Public */,
       8,    0,   92,    2, 0x06,    7 /* Public */,
       9,    0,   93,    2, 0x06,    8 /* Public */,
      10,    0,   94,    2, 0x06,    9 /* Public */,
      11,    0,   95,    2, 0x06,   10 /* Public */,
      12,    0,   96,    2, 0x06,   11 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      13,    2,   97,    2, 0x0a,   12 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,

       0        // eod
};

Q_CONSTINIT const QMetaObject HomeView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSHomeViewENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSHomeViewENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSHomeViewENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<HomeView, std::true_type>,
        // method 'startTemperatureRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startSpo2Requested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startNIBPRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startHeightRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startWeightRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startVisionTestRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startNewTestRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startSettingsRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startPrintingRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'visionTestRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'settingsRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
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
        case 0: _t->startTemperatureRequested(); break;
        case 1: _t->startSpo2Requested(); break;
        case 2: _t->startNIBPRequested(); break;
        case 3: _t->startHeightRequested(); break;
        case 4: _t->startWeightRequested(); break;
        case 5: _t->startVisionTestRequested(); break;
        case 6: _t->startNewTestRequested(); break;
        case 7: _t->startSettingsRequested(); break;
        case 8: _t->startPrintingRequested(); break;
        case 9: _t->visionTestRequested(); break;
        case 10: _t->settingsRequested(); break;
        case 11: _t->onVitalsUpdated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HomeView::*)();
            if (_t _q_method = &HomeView::startTemperatureRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (HomeView::*)();
            if (_t _q_method = &HomeView::startSpo2Requested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
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
            if (_t _q_method = &HomeView::startVisionTestRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (HomeView::*)();
            if (_t _q_method = &HomeView::startNewTestRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (HomeView::*)();
            if (_t _q_method = &HomeView::startSettingsRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (HomeView::*)();
            if (_t _q_method = &HomeView::startPrintingRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (HomeView::*)();
            if (_t _q_method = &HomeView::visionTestRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (HomeView::*)();
            if (_t _q_method = &HomeView::settingsRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
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
    return QWidget::qt_metacast(_clname);
}

int HomeView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void HomeView::startTemperatureRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void HomeView::startSpo2Requested()
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
void HomeView::startVisionTestRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void HomeView::startNewTestRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void HomeView::startSettingsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void HomeView::startPrintingRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void HomeView::visionTestRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void HomeView::settingsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}
QT_WARNING_POP
