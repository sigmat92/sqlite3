/****************************************************************************
** Meta object code from reading C++ file 'settingscontroller.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/controller/settingscontroller.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingscontroller.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSSettingsControllerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSSettingsControllerENDCLASS = QtMocHelpers::stringData(
    "SettingsController",
    "exitToHomeRequested",
    "",
    "settingsRequested",
    "onPostVitals",
    "handleSave",
    "handleExit",
    "handleDhcpToggle",
    "enabled"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSSettingsControllerENDCLASS_t {
    uint offsetsAndSizes[18];
    char stringdata0[19];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[18];
    char stringdata4[13];
    char stringdata5[11];
    char stringdata6[11];
    char stringdata7[17];
    char stringdata8[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSSettingsControllerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSSettingsControllerENDCLASS_t qt_meta_stringdata_CLASSSettingsControllerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 18),  // "SettingsController"
        QT_MOC_LITERAL(19, 19),  // "exitToHomeRequested"
        QT_MOC_LITERAL(39, 0),  // ""
        QT_MOC_LITERAL(40, 17),  // "settingsRequested"
        QT_MOC_LITERAL(58, 12),  // "onPostVitals"
        QT_MOC_LITERAL(71, 10),  // "handleSave"
        QT_MOC_LITERAL(82, 10),  // "handleExit"
        QT_MOC_LITERAL(93, 16),  // "handleDhcpToggle"
        QT_MOC_LITERAL(110, 7)   // "enabled"
    },
    "SettingsController",
    "exitToHomeRequested",
    "",
    "settingsRequested",
    "onPostVitals",
    "handleSave",
    "handleExit",
    "handleDhcpToggle",
    "enabled"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSettingsControllerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    1 /* Public */,
       3,    0,   51,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    0,   54,    2, 0x08,    5 /* Private */,
       7,    1,   55,    2, 0x08,    6 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,

       0        // eod
};

Q_CONSTINIT const QMetaObject SettingsController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSSettingsControllerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSettingsControllerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSettingsControllerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SettingsController, std::true_type>,
        // method 'exitToHomeRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'settingsRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onPostVitals'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleSave'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleExit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleDhcpToggle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void SettingsController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SettingsController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->exitToHomeRequested(); break;
        case 1: _t->settingsRequested(); break;
        case 2: _t->onPostVitals(); break;
        case 3: _t->handleSave(); break;
        case 4: _t->handleExit(); break;
        case 5: _t->handleDhcpToggle((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SettingsController::*)();
            if (_t _q_method = &SettingsController::exitToHomeRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SettingsController::*)();
            if (_t _q_method = &SettingsController::settingsRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *SettingsController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingsController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSettingsControllerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SettingsController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void SettingsController::exitToHomeRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SettingsController::settingsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
