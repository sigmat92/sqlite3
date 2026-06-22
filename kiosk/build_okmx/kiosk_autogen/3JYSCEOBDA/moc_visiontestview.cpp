/****************************************************************************
** Meta object code from reading C++ file 'visiontestview.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
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
struct qt_meta_stringdata_CLASSVisionTestViewENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSVisionTestViewENDCLASS = QtMocHelpers::stringData(
    "VisionTestView",
    "startRequested",
    "",
    "answerSelected",
    "answer",
    "nearModeSelected",
    "farModeSelected",
    "exitRequested",
    "displayLevel",
    "letters",
    "fontSize",
    "showResult",
    "result",
    "onNearClicked",
    "onFarClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSVisionTestViewENDCLASS_t {
    uint offsetsAndSizes[30];
    char stringdata0[15];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[7];
    char stringdata5[17];
    char stringdata6[16];
    char stringdata7[14];
    char stringdata8[13];
    char stringdata9[8];
    char stringdata10[9];
    char stringdata11[11];
    char stringdata12[7];
    char stringdata13[14];
    char stringdata14[13];
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
        QT_MOC_LITERAL(53, 16),  // "nearModeSelected"
        QT_MOC_LITERAL(70, 15),  // "farModeSelected"
        QT_MOC_LITERAL(86, 13),  // "exitRequested"
        QT_MOC_LITERAL(100, 12),  // "displayLevel"
        QT_MOC_LITERAL(113, 7),  // "letters"
        QT_MOC_LITERAL(121, 8),  // "fontSize"
        QT_MOC_LITERAL(130, 10),  // "showResult"
        QT_MOC_LITERAL(141, 6),  // "result"
        QT_MOC_LITERAL(148, 13),  // "onNearClicked"
        QT_MOC_LITERAL(162, 12)   // "onFarClicked"
    },
    "VisionTestView",
    "startRequested",
    "",
    "answerSelected",
    "answer",
    "nearModeSelected",
    "farModeSelected",
    "exitRequested",
    "displayLevel",
    "letters",
    "fontSize",
    "showResult",
    "result",
    "onNearClicked",
    "onFarClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSVisionTestViewENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x06,    1 /* Public */,
       3,    1,   69,    2, 0x06,    2 /* Public */,
       5,    0,   72,    2, 0x06,    4 /* Public */,
       6,    0,   73,    2, 0x06,    5 /* Public */,
       7,    0,   74,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    2,   75,    2, 0x0a,    7 /* Public */,
      11,    1,   80,    2, 0x0a,   10 /* Public */,
      13,    0,   83,    2, 0x08,   12 /* Private */,
      14,    0,   84,    2, 0x08,   13 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    9,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
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
        // method 'startRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'answerSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'nearModeSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'farModeSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exitRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'displayLevel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'showResult'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'onNearClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFarClicked'
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
        case 0: _t->startRequested(); break;
        case 1: _t->answerSelected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->nearModeSelected(); break;
        case 3: _t->farModeSelected(); break;
        case 4: _t->exitRequested(); break;
        case 5: _t->displayLevel((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 6: _t->showResult((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->onNearClicked(); break;
        case 8: _t->onFarClicked(); break;
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
            if (_t _q_method = &VisionTestView::nearModeSelected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (VisionTestView::*)();
            if (_t _q_method = &VisionTestView::farModeSelected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (VisionTestView::*)();
            if (_t _q_method = &VisionTestView::exitRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
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
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
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
void VisionTestView::nearModeSelected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void VisionTestView::farModeSelected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void VisionTestView::exitRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
