/****************************************************************************
** Meta object code from reading C++ file 'protocolparser.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/platform/uart/protocolparser.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'protocolparser.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSProtocolParserENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSProtocolParserENDCLASS = QtMocHelpers::stringData(
    "ProtocolParser",
    "temperatureReceived",
    "",
    "value",
    "unit",
    "spo2Received",
    "spo2",
    "pulse",
    "nibpReceived",
    "sys",
    "dia",
    "weightReceived",
    "heightReceived"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSProtocolParserENDCLASS_t {
    uint offsetsAndSizes[26];
    char stringdata0[15];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[5];
    char stringdata5[13];
    char stringdata6[5];
    char stringdata7[6];
    char stringdata8[13];
    char stringdata9[4];
    char stringdata10[4];
    char stringdata11[15];
    char stringdata12[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSProtocolParserENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSProtocolParserENDCLASS_t qt_meta_stringdata_CLASSProtocolParserENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "ProtocolParser"
        QT_MOC_LITERAL(15, 19),  // "temperatureReceived"
        QT_MOC_LITERAL(35, 0),  // ""
        QT_MOC_LITERAL(36, 5),  // "value"
        QT_MOC_LITERAL(42, 4),  // "unit"
        QT_MOC_LITERAL(47, 12),  // "spo2Received"
        QT_MOC_LITERAL(60, 4),  // "spo2"
        QT_MOC_LITERAL(65, 5),  // "pulse"
        QT_MOC_LITERAL(71, 12),  // "nibpReceived"
        QT_MOC_LITERAL(84, 3),  // "sys"
        QT_MOC_LITERAL(88, 3),  // "dia"
        QT_MOC_LITERAL(92, 14),  // "weightReceived"
        QT_MOC_LITERAL(107, 14)   // "heightReceived"
    },
    "ProtocolParser",
    "temperatureReceived",
    "",
    "value",
    "unit",
    "spo2Received",
    "spo2",
    "pulse",
    "nibpReceived",
    "sys",
    "dia",
    "weightReceived",
    "heightReceived"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSProtocolParserENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   44,    2, 0x06,    1 /* Public */,
       5,    2,   49,    2, 0x06,    4 /* Public */,
       8,    3,   54,    2, 0x06,    7 /* Public */,
      11,    1,   61,    2, 0x06,   11 /* Public */,
      12,    1,   64,    2, 0x06,   13 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Char,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    9,   10,    7,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,

       0        // eod
};

Q_CONSTINIT const QMetaObject ProtocolParser::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSProtocolParserENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSProtocolParserENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSProtocolParserENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ProtocolParser, std::true_type>,
        // method 'temperatureReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<char, std::false_type>,
        // method 'spo2Received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'nibpReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'weightReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'heightReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>
    >,
    nullptr
} };

void ProtocolParser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProtocolParser *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->temperatureReceived((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<char>>(_a[2]))); break;
        case 1: _t->spo2Received((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 2: _t->nibpReceived((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 3: _t->weightReceived((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 4: _t->heightReceived((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ProtocolParser::*)(double , char );
            if (_t _q_method = &ProtocolParser::temperatureReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ProtocolParser::*)(int , int );
            if (_t _q_method = &ProtocolParser::spo2Received; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ProtocolParser::*)(int , int , int );
            if (_t _q_method = &ProtocolParser::nibpReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ProtocolParser::*)(double );
            if (_t _q_method = &ProtocolParser::weightReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ProtocolParser::*)(double );
            if (_t _q_method = &ProtocolParser::heightReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *ProtocolParser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProtocolParser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSProtocolParserENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ProtocolParser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ProtocolParser::temperatureReceived(double _t1, char _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ProtocolParser::spo2Received(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ProtocolParser::nibpReceived(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ProtocolParser::weightReceived(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ProtocolParser::heightReceived(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
