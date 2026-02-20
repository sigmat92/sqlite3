/****************************************************************************
** Meta object code from reading C++ file 'settingsview.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/view/settingsview.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingsview.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSSettingsViewENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSSettingsViewENDCLASS = QtMocHelpers::stringData(
    "SettingsView",
    "saveRequested",
    "",
    "scanWifiRequested",
    "testConnectionRequested",
    "exitRequested"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSSettingsViewENDCLASS_t {
    uint offsetsAndSizes[12];
    char stringdata0[13];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[18];
    char stringdata4[24];
    char stringdata5[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSSettingsViewENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSSettingsViewENDCLASS_t qt_meta_stringdata_CLASSSettingsViewENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "SettingsView"
        QT_MOC_LITERAL(13, 13),  // "saveRequested"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 17),  // "scanWifiRequested"
        QT_MOC_LITERAL(46, 23),  // "testConnectionRequested"
        QT_MOC_LITERAL(70, 13)   // "exitRequested"
    },
    "SettingsView",
    "saveRequested",
    "",
    "scanWifiRequested",
    "testConnectionRequested",
    "exitRequested"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSettingsViewENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x06,    1 /* Public */,
       3,    0,   39,    2, 0x06,    2 /* Public */,
       4,    0,   40,    2, 0x06,    3 /* Public */,
       5,    0,   41,    2, 0x06,    4 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject SettingsView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSSettingsViewENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSettingsViewENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSettingsViewENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SettingsView, std::true_type>,
        // method 'saveRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'scanWifiRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'testConnectionRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exitRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SettingsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SettingsView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->saveRequested(); break;
        case 1: _t->scanWifiRequested(); break;
        case 2: _t->testConnectionRequested(); break;
        case 3: _t->exitRequested(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SettingsView::*)();
            if (_t _q_method = &SettingsView::saveRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SettingsView::*)();
            if (_t _q_method = &SettingsView::scanWifiRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SettingsView::*)();
            if (_t _q_method = &SettingsView::testConnectionRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SettingsView::*)();
            if (_t _q_method = &SettingsView::exitRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *SettingsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingsView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSettingsViewENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SettingsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SettingsView::saveRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SettingsView::scanWifiRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SettingsView::testConnectionRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SettingsView::exitRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
