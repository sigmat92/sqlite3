/****************************************************************************
** Meta object code from reading C++ file 'sqliterecorder.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/storage/sqliterecorder.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sqliterecorder.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSSQLiteRecorderENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSSQLiteRecorderENDCLASS = QtMocHelpers::stringData(
    "SQLiteRecorder",
    "store",
    "",
    "text",
    "format",
    "storeVitals",
    "temperature",
    "tempUnit",
    "spo2",
    "pulse",
    "weight",
    "height",
    "sys",
    "dia",
    "map"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSSQLiteRecorderENDCLASS_t {
    uint offsetsAndSizes[30];
    char stringdata0[15];
    char stringdata1[6];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[7];
    char stringdata5[12];
    char stringdata6[12];
    char stringdata7[9];
    char stringdata8[5];
    char stringdata9[6];
    char stringdata10[7];
    char stringdata11[7];
    char stringdata12[4];
    char stringdata13[4];
    char stringdata14[4];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSSQLiteRecorderENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSSQLiteRecorderENDCLASS_t qt_meta_stringdata_CLASSSQLiteRecorderENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "SQLiteRecorder"
        QT_MOC_LITERAL(15, 5),  // "store"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 4),  // "text"
        QT_MOC_LITERAL(27, 6),  // "format"
        QT_MOC_LITERAL(34, 11),  // "storeVitals"
        QT_MOC_LITERAL(46, 11),  // "temperature"
        QT_MOC_LITERAL(58, 8),  // "tempUnit"
        QT_MOC_LITERAL(67, 4),  // "spo2"
        QT_MOC_LITERAL(72, 5),  // "pulse"
        QT_MOC_LITERAL(78, 6),  // "weight"
        QT_MOC_LITERAL(85, 6),  // "height"
        QT_MOC_LITERAL(92, 3),  // "sys"
        QT_MOC_LITERAL(96, 3),  // "dia"
        QT_MOC_LITERAL(100, 3)   // "map"
    },
    "SQLiteRecorder",
    "store",
    "",
    "text",
    "format",
    "storeVitals",
    "temperature",
    "tempUnit",
    "spo2",
    "pulse",
    "weight",
    "height",
    "sys",
    "dia",
    "map"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSQLiteRecorderENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   26,    2, 0x0a,    1 /* Public */,
       5,    9,   31,    2, 0x0a,    4 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Double, QMetaType::Char, QMetaType::Int, QMetaType::Int, QMetaType::Double, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    6,    7,    8,    9,   10,   11,   12,   13,   14,

       0        // eod
};

Q_CONSTINIT const QMetaObject SQLiteRecorder::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSSQLiteRecorderENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSQLiteRecorderENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSQLiteRecorderENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SQLiteRecorder, std::true_type>,
        // method 'store'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'storeVitals'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<char, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void SQLiteRecorder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SQLiteRecorder *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->store((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->storeVitals((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<char>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[8])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[9]))); break;
        default: ;
        }
    }
}

const QMetaObject *SQLiteRecorder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SQLiteRecorder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSQLiteRecorderENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SQLiteRecorder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
