/****************************************************************************
** Meta object code from reading C++ file 'gpiokeyhandler.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/platform/input/gpiokeyhandler.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gpiokeyhandler.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSGPIOKeyHandlerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSGPIOKeyHandlerENDCLASS = QtMocHelpers::stringData(
    "GPIOKeyHandler",
    "mutePressed",
    "",
    "nibpPressed",
    "freezePressed",
    "printPressed",
    "menuPressed",
    "processEvents",
    "stop"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSGPIOKeyHandlerENDCLASS_t {
    uint offsetsAndSizes[18];
    char stringdata0[15];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[14];
    char stringdata5[13];
    char stringdata6[12];
    char stringdata7[14];
    char stringdata8[5];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSGPIOKeyHandlerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSGPIOKeyHandlerENDCLASS_t qt_meta_stringdata_CLASSGPIOKeyHandlerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "GPIOKeyHandler"
        QT_MOC_LITERAL(15, 11),  // "mutePressed"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 11),  // "nibpPressed"
        QT_MOC_LITERAL(40, 13),  // "freezePressed"
        QT_MOC_LITERAL(54, 12),  // "printPressed"
        QT_MOC_LITERAL(67, 11),  // "menuPressed"
        QT_MOC_LITERAL(79, 13),  // "processEvents"
        QT_MOC_LITERAL(93, 4)   // "stop"
    },
    "GPIOKeyHandler",
    "mutePressed",
    "",
    "nibpPressed",
    "freezePressed",
    "printPressed",
    "menuPressed",
    "processEvents",
    "stop"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSGPIOKeyHandlerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x06,    1 /* Public */,
       3,    0,   57,    2, 0x06,    2 /* Public */,
       4,    0,   58,    2, 0x06,    3 /* Public */,
       5,    0,   59,    2, 0x06,    4 /* Public */,
       6,    0,   60,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   61,    2, 0x0a,    6 /* Public */,
       8,    0,   62,    2, 0x0a,    7 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject GPIOKeyHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSGPIOKeyHandlerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSGPIOKeyHandlerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSGPIOKeyHandlerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GPIOKeyHandler, std::true_type>,
        // method 'mutePressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'nibpPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'freezePressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'printPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'menuPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'processEvents'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void GPIOKeyHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GPIOKeyHandler *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->mutePressed(); break;
        case 1: _t->nibpPressed(); break;
        case 2: _t->freezePressed(); break;
        case 3: _t->printPressed(); break;
        case 4: _t->menuPressed(); break;
        case 5: _t->processEvents(); break;
        case 6: _t->stop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GPIOKeyHandler::*)();
            if (_t _q_method = &GPIOKeyHandler::mutePressed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GPIOKeyHandler::*)();
            if (_t _q_method = &GPIOKeyHandler::nibpPressed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GPIOKeyHandler::*)();
            if (_t _q_method = &GPIOKeyHandler::freezePressed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GPIOKeyHandler::*)();
            if (_t _q_method = &GPIOKeyHandler::printPressed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GPIOKeyHandler::*)();
            if (_t _q_method = &GPIOKeyHandler::menuPressed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *GPIOKeyHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GPIOKeyHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSGPIOKeyHandlerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GPIOKeyHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void GPIOKeyHandler::mutePressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GPIOKeyHandler::nibpPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void GPIOKeyHandler::freezePressed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GPIOKeyHandler::printPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void GPIOKeyHandler::menuPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
