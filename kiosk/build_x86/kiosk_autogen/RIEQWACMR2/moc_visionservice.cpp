/****************************************************************************
** Meta object code from reading C++ file 'visionservice.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/service/visionservice.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'visionservice.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSVisionServiceENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSVisionServiceENDCLASS = QtMocHelpers::stringData(
    "VisionService",
    "nextLevel",
    "",
    "letters",
    "fontSize",
    "testCompleted",
    "result",
    "setNearMode",
    "setFarMode",
    "startTest",
    "submitAnswer",
    "correct"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSVisionServiceENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[14];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[9];
    char stringdata5[14];
    char stringdata6[7];
    char stringdata7[12];
    char stringdata8[11];
    char stringdata9[10];
    char stringdata10[13];
    char stringdata11[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSVisionServiceENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSVisionServiceENDCLASS_t qt_meta_stringdata_CLASSVisionServiceENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13),  // "VisionService"
        QT_MOC_LITERAL(14, 9),  // "nextLevel"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 7),  // "letters"
        QT_MOC_LITERAL(33, 8),  // "fontSize"
        QT_MOC_LITERAL(42, 13),  // "testCompleted"
        QT_MOC_LITERAL(56, 6),  // "result"
        QT_MOC_LITERAL(63, 11),  // "setNearMode"
        QT_MOC_LITERAL(75, 10),  // "setFarMode"
        QT_MOC_LITERAL(86, 9),  // "startTest"
        QT_MOC_LITERAL(96, 12),  // "submitAnswer"
        QT_MOC_LITERAL(109, 7)   // "correct"
    },
    "VisionService",
    "nextLevel",
    "",
    "letters",
    "fontSize",
    "testCompleted",
    "result",
    "setNearMode",
    "setFarMode",
    "startTest",
    "submitAnswer",
    "correct"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSVisionServiceENDCLASS[] = {

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
       1,    2,   50,    2, 0x06,    1 /* Public */,
       5,    1,   55,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   58,    2, 0x0a,    6 /* Public */,
       8,    0,   59,    2, 0x0a,    7 /* Public */,
       9,    0,   60,    2, 0x0a,    8 /* Public */,
      10,    1,   61,    2, 0x0a,    9 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,

       0        // eod
};

Q_CONSTINIT const QMetaObject VisionService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSVisionServiceENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSVisionServiceENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSVisionServiceENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<VisionService, std::true_type>,
        // method 'nextLevel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'testCompleted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'setNearMode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setFarMode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startTest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'submitAnswer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void VisionService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VisionService *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->nextLevel((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->testCompleted((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->setNearMode(); break;
        case 3: _t->setFarMode(); break;
        case 4: _t->startTest(); break;
        case 5: _t->submitAnswer((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VisionService::*)(QString , int );
            if (_t _q_method = &VisionService::nextLevel; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VisionService::*)(QString );
            if (_t _q_method = &VisionService::testCompleted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *VisionService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VisionService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSVisionServiceENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VisionService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void VisionService::nextLevel(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VisionService::testCompleted(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
