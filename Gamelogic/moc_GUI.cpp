/****************************************************************************
** Meta object code from reading C++ file 'GUI.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "GUI.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GUI_t {
    QByteArrayData data[15];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GUI_t qt_meta_stringdata_GUI = {
    {
QT_MOC_LITERAL(0, 0, 3), // "GUI"
QT_MOC_LITERAL(1, 4, 9), // "addPlayer"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 9), // "startGame"
QT_MOC_LITERAL(4, 25, 12), // "handleAction"
QT_MOC_LITERAL(5, 38, 10), // "actionName"
QT_MOC_LITERAL(6, 49, 15), // "handleSpyAction"
QT_MOC_LITERAL(7, 65, 17), // "handleBaronAction"
QT_MOC_LITERAL(8, 83, 20), // "handleGovernorAction"
QT_MOC_LITERAL(9, 104, 17), // "handleJudgeAction"
QT_MOC_LITERAL(10, 122, 14), // "updateGameView"
QT_MOC_LITERAL(11, 137, 17), // "checkGeneralBlock"
QT_MOC_LITERAL(12, 155, 11), // "targetIndex"
QT_MOC_LITERAL(13, 167, 6), // "Action"
QT_MOC_LITERAL(14, 174, 6) // "action"

    },
    "GUI\0addPlayer\0\0startGame\0handleAction\0"
    "actionName\0handleSpyAction\0handleBaronAction\0"
    "handleGovernorAction\0handleJudgeAction\0"
    "updateGameView\0checkGeneralBlock\0"
    "targetIndex\0Action\0action"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    1,   61,    2, 0x08 /* Private */,
       6,    0,   64,    2, 0x08 /* Private */,
       7,    0,   65,    2, 0x08 /* Private */,
       8,    0,   66,    2, 0x08 /* Private */,
       9,    0,   67,    2, 0x08 /* Private */,
      10,    0,   68,    2, 0x08 /* Private */,
      11,    2,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Int, 0x80000000 | 13,   12,   14,

       0        // eod
};

void GUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GUI *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addPlayer(); break;
        case 1: _t->startGame(); break;
        case 2: _t->handleAction((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->handleSpyAction(); break;
        case 4: _t->handleBaronAction(); break;
        case 5: _t->handleGovernorAction(); break;
        case 6: _t->handleJudgeAction(); break;
        case 7: _t->updateGameView(); break;
        case 8: { bool _r = _t->checkGeneralBlock((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const Action(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GUI::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_GUI.data,
    qt_meta_data_GUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GUI.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int GUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
