/****************************************************************************
** Meta object code from reading C++ file 'inputservice.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/service/inputservice.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inputservice.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSInputServiceENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSInputServiceENDCLASS = QtMocHelpers::stringData(
    "InputService",
    "focusNext",
    "",
    "focusPrevious",
    "activate",
    "mute",
    "nibp",
    "freeze",
    "print",
    "menu",
    "navigateNext",
    "navigatePrevious",
    "select",
    "onMutePressed",
    "onNibpPressed",
    "onFreezePressed",
    "onPrintPressed",
    "onMenuPressed"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSInputServiceENDCLASS_t {
    uint offsetsAndSizes[36];
    char stringdata0[13];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[9];
    char stringdata5[5];
    char stringdata6[5];
    char stringdata7[7];
    char stringdata8[6];
    char stringdata9[5];
    char stringdata10[13];
    char stringdata11[17];
    char stringdata12[7];
    char stringdata13[14];
    char stringdata14[14];
    char stringdata15[16];
    char stringdata16[15];
    char stringdata17[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSInputServiceENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSInputServiceENDCLASS_t qt_meta_stringdata_CLASSInputServiceENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "InputService"
        QT_MOC_LITERAL(13, 9),  // "focusNext"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 13),  // "focusPrevious"
        QT_MOC_LITERAL(38, 8),  // "activate"
        QT_MOC_LITERAL(47, 4),  // "mute"
        QT_MOC_LITERAL(52, 4),  // "nibp"
        QT_MOC_LITERAL(57, 6),  // "freeze"
        QT_MOC_LITERAL(64, 5),  // "print"
        QT_MOC_LITERAL(70, 4),  // "menu"
        QT_MOC_LITERAL(75, 12),  // "navigateNext"
        QT_MOC_LITERAL(88, 16),  // "navigatePrevious"
        QT_MOC_LITERAL(105, 6),  // "select"
        QT_MOC_LITERAL(112, 13),  // "onMutePressed"
        QT_MOC_LITERAL(126, 13),  // "onNibpPressed"
        QT_MOC_LITERAL(140, 15),  // "onFreezePressed"
        QT_MOC_LITERAL(156, 14),  // "onPrintPressed"
        QT_MOC_LITERAL(171, 13)   // "onMenuPressed"
    },
    "InputService",
    "focusNext",
    "",
    "focusPrevious",
    "activate",
    "mute",
    "nibp",
    "freeze",
    "print",
    "menu",
    "navigateNext",
    "navigatePrevious",
    "select",
    "onMutePressed",
    "onNibpPressed",
    "onFreezePressed",
    "onPrintPressed",
    "onMenuPressed"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSInputServiceENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  110,    2, 0x06,    1 /* Public */,
       3,    0,  111,    2, 0x06,    2 /* Public */,
       4,    0,  112,    2, 0x06,    3 /* Public */,
       5,    0,  113,    2, 0x06,    4 /* Public */,
       6,    0,  114,    2, 0x06,    5 /* Public */,
       7,    0,  115,    2, 0x06,    6 /* Public */,
       8,    0,  116,    2, 0x06,    7 /* Public */,
       9,    0,  117,    2, 0x06,    8 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    0,  118,    2, 0x0a,    9 /* Public */,
      11,    0,  119,    2, 0x0a,   10 /* Public */,
      12,    0,  120,    2, 0x0a,   11 /* Public */,
      13,    0,  121,    2, 0x0a,   12 /* Public */,
      14,    0,  122,    2, 0x0a,   13 /* Public */,
      15,    0,  123,    2, 0x0a,   14 /* Public */,
      16,    0,  124,    2, 0x0a,   15 /* Public */,
      17,    0,  125,    2, 0x0a,   16 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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
        // method 'mute'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'nibp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'freeze'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'print'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'menu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'navigateNext'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'navigatePrevious'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'select'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMutePressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onNibpPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFreezePressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onPrintPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMenuPressed'
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
        case 3: _t->mute(); break;
        case 4: _t->nibp(); break;
        case 5: _t->freeze(); break;
        case 6: _t->print(); break;
        case 7: _t->menu(); break;
        case 8: _t->navigateNext(); break;
        case 9: _t->navigatePrevious(); break;
        case 10: _t->select(); break;
        case 11: _t->onMutePressed(); break;
        case 12: _t->onNibpPressed(); break;
        case 13: _t->onFreezePressed(); break;
        case 14: _t->onPrintPressed(); break;
        case 15: _t->onMenuPressed(); break;
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
        {
            using _t = void (InputService::*)();
            if (_t _q_method = &InputService::mute; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (InputService::*)();
            if (_t _q_method = &InputService::nibp; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (InputService::*)();
            if (_t _q_method = &InputService::freeze; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (InputService::*)();
            if (_t _q_method = &InputService::print; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (InputService::*)();
            if (_t _q_method = &InputService::menu; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
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

// SIGNAL 3
void InputService::mute()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void InputService::nibp()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void InputService::freeze()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void InputService::print()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void InputService::menu()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
