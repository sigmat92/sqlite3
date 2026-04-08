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
    "startRequested",
    "",
    "answerSelected",
    "answer",
    "exitRequested",
    "displaySymbol",
    "symbol",
    "showResult",
    "result"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSVisionTestViewENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[15];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[7];
    char stringdata5[14];
    char stringdata6[14];
    char stringdata7[7];
    char stringdata8[11];
    char stringdata9[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSVisionTestViewENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSVisionTestViewENDCLASS_t qt_meta_stringdata_CLASSVisionTestViewENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "VisionTestView"
        QT_MOC_LITERAL(15, 14),  // "startRequested"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 14),  // "answerSelected"
        QT_MOC_LITERAL(46, 6),  // "answer"
        QT_MOC_LITERAL(53, 13),  // "exitRequested"
        QT_MOC_LITERAL(67, 13),  // "displaySymbol"
        QT_MOC_LITERAL(81, 6),  // "symbol"
        QT_MOC_LITERAL(88, 10),  // "showResult"
        QT_MOC_LITERAL(99, 6)   // "result"
    },
    "VisionTestView",
    "startRequested",
    "",
    "answerSelected",
    "answer",
    "exitRequested",
    "displaySymbol",
    "symbol",
    "showResult",
    "result"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSVisionTestViewENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,    1 /* Public */,
       3,    1,   45,    2, 0x06,    2 /* Public */,
       5,    0,   48,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   49,    2, 0x0a,    5 /* Public */,
       8,    1,   52,    2, 0x0a,    7 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    9,

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
        // method 'startRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'answerSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'exitRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'displaySymbol'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'showResult'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>
    >,
    nullptr
} };

void VisionTestView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VisionTestView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->startRequested(); break;
        case 1: _t->answerSelected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->exitRequested(); break;
        case 3: _t->displaySymbol((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->showResult((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VisionTestView::*)();
            if (_t _q_method = &VisionTestView::startRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VisionTestView::*)(QString );
            if (_t _q_method = &VisionTestView::answerSelected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VisionTestView::*)();
            if (_t _q_method = &VisionTestView::exitRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
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
void VisionTestView::startRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VisionTestView::answerSelected(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VisionTestView::exitRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
