/****************************************************************************
** Meta object code from reading C++ file 'visiontestview.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/view/visiontestview.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'visiontestview.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSVisionTestViewENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSVisionTestViewENDCLASS = QtMocHelpers::stringData(
    "VisionTestView",
    "leftStartRequested",
    "",
    "rightStartRequested",
    "backRequested",
    "startRequested",
    "passRequested",
    "failRequested",
    "modeChanged",
    "mode",
    "exitRequested"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSVisionTestViewENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[15];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[20];
    char stringdata4[14];
    char stringdata5[15];
    char stringdata6[14];
    char stringdata7[14];
    char stringdata8[12];
    char stringdata9[5];
    char stringdata10[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSVisionTestViewENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSVisionTestViewENDCLASS_t qt_meta_stringdata_CLASSVisionTestViewENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "VisionTestView"
        QT_MOC_LITERAL(15, 18),  // "leftStartRequested"
        QT_MOC_LITERAL(34, 0),  // ""
        QT_MOC_LITERAL(35, 19),  // "rightStartRequested"
        QT_MOC_LITERAL(55, 13),  // "backRequested"
        QT_MOC_LITERAL(69, 14),  // "startRequested"
        QT_MOC_LITERAL(84, 13),  // "passRequested"
        QT_MOC_LITERAL(98, 13),  // "failRequested"
        QT_MOC_LITERAL(112, 11),  // "modeChanged"
        QT_MOC_LITERAL(124, 4),  // "mode"
        QT_MOC_LITERAL(129, 13)   // "exitRequested"
    },
    "VisionTestView",
    "leftStartRequested",
    "",
    "rightStartRequested",
    "backRequested",
    "startRequested",
    "passRequested",
    "failRequested",
    "modeChanged",
    "mode",
    "exitRequested"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSVisionTestViewENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    1 /* Public */,
       3,    0,   63,    2, 0x06,    2 /* Public */,
       4,    0,   64,    2, 0x06,    3 /* Public */,
       5,    0,   65,    2, 0x06,    4 /* Public */,
       6,    0,   66,    2, 0x06,    5 /* Public */,
       7,    0,   67,    2, 0x06,    6 /* Public */,
       8,    1,   68,    2, 0x06,    7 /* Public */,
      10,    0,   71,    2, 0x06,    9 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject VisionTestView::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseView::staticMetaObject>(),
    qt_meta_stringdata_CLASSVisionTestViewENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSVisionTestViewENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSVisionTestViewENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<VisionTestView, std::true_type>,
        // method 'leftStartRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rightStartRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'backRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'passRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'failRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'modeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'exitRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void VisionTestView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VisionTestView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->leftStartRequested(); break;
        case 1: _t->rightStartRequested(); break;
        case 2: _t->backRequested(); break;
        case 3: _t->startRequested(); break;
        case 4: _t->passRequested(); break;
        case 5: _t->failRequested(); break;
        case 6: _t->modeChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->exitRequested(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VisionTestView::*)();
            if (_t _q_method = &VisionTestView::leftStartRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VisionTestView::*)();
            if (_t _q_method = &VisionTestView::rightStartRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VisionTestView::*)();
            if (_t _q_method = &VisionTestView::backRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (VisionTestView::*)();
            if (_t _q_method = &VisionTestView::startRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (VisionTestView::*)();
            if (_t _q_method = &VisionTestView::passRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (VisionTestView::*)();
            if (_t _q_method = &VisionTestView::failRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (VisionTestView::*)(QString );
            if (_t _q_method = &VisionTestView::modeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (VisionTestView::*)();
            if (_t _q_method = &VisionTestView::exitRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject *VisionTestView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VisionTestView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSVisionTestViewENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return BaseView::qt_metacast(_clname);
}

int VisionTestView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void VisionTestView::leftStartRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VisionTestView::rightStartRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void VisionTestView::backRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void VisionTestView::startRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void VisionTestView::passRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void VisionTestView::failRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void VisionTestView::modeChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void VisionTestView::exitRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
