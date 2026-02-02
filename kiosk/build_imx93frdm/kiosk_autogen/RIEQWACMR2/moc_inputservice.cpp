/****************************************************************************
** Meta object code from reading C++ file 'inputservice.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/service/inputservice.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inputservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.0. It"
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
struct qt_meta_stringdata_CLASSInputServiceENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSInputServiceENDCLASS = QtMocHelpers::stringData(
    "InputService",
    "focusNext",
    "",
    "focusPrevious",
    "activate",
    "onRotatedLeft",
    "onRotatedRight",
    "onPressed"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSInputServiceENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    1 /* Public */,
       3,    0,   51,    2, 0x06,    2 /* Public */,
       4,    0,   52,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   53,    2, 0x0a,    4 /* Public */,
       6,    0,   54,    2, 0x0a,    5 /* Public */,
       7,    0,   55,    2, 0x0a,    6 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject InputService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSInputServiceENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSInputServiceENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSInputServiceENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<InputService, std::true_type>,
        // method 'focusNext'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'focusPrevious'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'activate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRotatedLeft'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRotatedRight'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void InputService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<InputService *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->focusNext(); break;
        case 1: _t->focusPrevious(); break;
        case 2: _t->activate(); break;
        case 3: _t->onRotatedLeft(); break;
        case 4: _t->onRotatedRight(); break;
        case 5: _t->onPressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (InputService::*)();
            if (_t _q_method = &InputService::focusNext; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (InputService::*)();
            if (_t _q_method = &InputService::focusPrevious; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (InputService::*)();
            if (_t _q_method = &InputService::activate; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *InputService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InputService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSInputServiceENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int InputService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void InputService::focusNext()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void InputService::focusPrevious()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void InputService::activate()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
