/****************************************************************************
** Meta object code from reading C++ file 'protocolparser.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/controller/protocolparser.h"
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
    "spo2",
    "",
    "pulseRate",
    "temperature",
    "nibp",
    "sys",
    "dia",
    "mean",
    "weight",
    "height"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSProtocolParserENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[15];
    char stringdata1[5];
    char stringdata2[1];
    char stringdata3[10];
    char stringdata4[12];
    char stringdata5[5];
    char stringdata6[4];
    char stringdata7[4];
    char stringdata8[5];
    char stringdata9[7];
    char stringdata10[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSProtocolParserENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSProtocolParserENDCLASS_t qt_meta_stringdata_CLASSProtocolParserENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "ProtocolParser"
        QT_MOC_LITERAL(15, 4),  // "spo2"
        QT_MOC_LITERAL(20, 0),  // ""
        QT_MOC_LITERAL(21, 9),  // "pulseRate"
        QT_MOC_LITERAL(31, 11),  // "temperature"
        QT_MOC_LITERAL(43, 4),  // "nibp"
        QT_MOC_LITERAL(48, 3),  // "sys"
        QT_MOC_LITERAL(52, 3),  // "dia"
        QT_MOC_LITERAL(56, 4),  // "mean"
        QT_MOC_LITERAL(61, 6),  // "weight"
        QT_MOC_LITERAL(68, 6)   // "height"
    },
    "ProtocolParser",
    "spo2",
    "",
    "pulseRate",
    "temperature",
    "nibp",
    "sys",
    "dia",
    "mean",
    "weight",
    "height"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSProtocolParserENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    1 /* Public */,
       3,    1,   53,    2, 0x06,    3 /* Public */,
       4,    1,   56,    2, 0x06,    5 /* Public */,
       5,    3,   59,    2, 0x06,    7 /* Public */,
       9,    1,   66,    2, 0x06,   11 /* Public */,
      10,    1,   69,    2, 0x06,   13 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    6,    7,    8,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Int,    2,

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
        // method 'spo2'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'pulseRate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'temperature'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        // method 'nibp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'weight'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        // method 'height'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void ProtocolParser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProtocolParser *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->spo2((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->pulseRate((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->temperature((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 3: _t->nibp((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 4: _t->weight((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 5: _t->height((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ProtocolParser::*)(int );
            if (_t _q_method = &ProtocolParser::spo2; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ProtocolParser::*)(int );
            if (_t _q_method = &ProtocolParser::pulseRate; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ProtocolParser::*)(float );
            if (_t _q_method = &ProtocolParser::temperature; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ProtocolParser::*)(int , int , int );
            if (_t _q_method = &ProtocolParser::nibp; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ProtocolParser::*)(float );
            if (_t _q_method = &ProtocolParser::weight; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ProtocolParser::*)(int );
            if (_t _q_method = &ProtocolParser::height; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
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
void ProtocolParser::spo2(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ProtocolParser::pulseRate(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ProtocolParser::temperature(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ProtocolParser::nibp(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ProtocolParser::weight(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ProtocolParser::height(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
