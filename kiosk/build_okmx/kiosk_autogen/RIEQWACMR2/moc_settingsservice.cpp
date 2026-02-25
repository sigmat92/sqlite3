/****************************************************************************
** Meta object code from reading C++ file 'settingsservice.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/service/settingsservice.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingsservice.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSSettingsServiceENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSSettingsServiceENDCLASS = QtMocHelpers::stringData(
    "SettingsService",
    "wifiListReady",
    "",
    "connectivityResult",
    "save",
    "load",
    "scanWifi",
    "testConnection",
    "applyNetwork"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSSettingsServiceENDCLASS_t {
    uint offsetsAndSizes[18];
    char stringdata0[16];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[19];
    char stringdata4[5];
    char stringdata5[5];
    char stringdata6[9];
    char stringdata7[15];
    char stringdata8[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSSettingsServiceENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSSettingsServiceENDCLASS_t qt_meta_stringdata_CLASSSettingsServiceENDCLASS = {
    {
        QT_MOC_LITERAL(0, 15),  // "SettingsService"
        QT_MOC_LITERAL(16, 13),  // "wifiListReady"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 18),  // "connectivityResult"
        QT_MOC_LITERAL(50, 4),  // "save"
        QT_MOC_LITERAL(55, 4),  // "load"
        QT_MOC_LITERAL(60, 8),  // "scanWifi"
        QT_MOC_LITERAL(69, 14),  // "testConnection"
        QT_MOC_LITERAL(84, 12)   // "applyNetwork"
    },
    "SettingsService",
    "wifiListReady",
    "",
    "connectivityResult",
    "save",
    "load",
    "scanWifi",
    "testConnection",
    "applyNetwork"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSettingsServiceENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    1 /* Public */,
       3,    1,   59,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   62,    2, 0x0a,    5 /* Public */,
       5,    0,   63,    2, 0x0a,    6 /* Public */,
       6,    0,   64,    2, 0x0a,    7 /* Public */,
       7,    0,   65,    2, 0x0a,    8 /* Public */,
       8,    0,   66,    2, 0x0a,    9 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject SettingsService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSSettingsServiceENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSettingsServiceENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSettingsServiceENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SettingsService, std::true_type>,
        // method 'wifiListReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QStringList, std::false_type>,
        // method 'connectivityResult'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'save'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'load'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'scanWifi'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'testConnection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyNetwork'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SettingsService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SettingsService *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->wifiListReady((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 1: _t->connectivityResult((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->save(); break;
        case 3: _t->load(); break;
        case 4: _t->scanWifi(); break;
        case 5: _t->testConnection(); break;
        case 6: _t->applyNetwork(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SettingsService::*)(QStringList );
            if (_t _q_method = &SettingsService::wifiListReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SettingsService::*)(bool );
            if (_t _q_method = &SettingsService::connectivityResult; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *SettingsService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingsService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSettingsServiceENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SettingsService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SettingsService::wifiListReady(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SettingsService::connectivityResult(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
