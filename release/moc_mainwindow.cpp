/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../GitRepositories/Stove-simulation-Qt/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[42];
    char stringdata0[383];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 12), // "errorMessage"
QT_MOC_LITERAL(24, 0), // ""
QT_MOC_LITERAL(25, 8), // "errIndex"
QT_MOC_LITERAL(34, 22), // "on_actionNew_triggered"
QT_MOC_LITERAL(57, 23), // "on_PenSize_valueChanged"
QT_MOC_LITERAL(81, 5), // "value"
QT_MOC_LITERAL(87, 27), // "on_startSimulation_released"
QT_MOC_LITERAL(115, 26), // "on_stopSimulation_released"
QT_MOC_LITERAL(142, 23), // "on_actionExit_triggered"
QT_MOC_LITERAL(166, 29), // "on_threadsNumber_valueChanged"
QT_MOC_LITERAL(196, 4), // "arg1"
QT_MOC_LITERAL(201, 21), // "on_topSilver_released"
QT_MOC_LITERAL(223, 21), // "on_topCopper_released"
QT_MOC_LITERAL(245, 19), // "on_topIron_released"
QT_MOC_LITERAL(265, 21), // "on_topQuartz_released"
QT_MOC_LITERAL(287, 20), // "on_topBrick_released"
QT_MOC_LITERAL(308, 20), // "on_topGlass_released"
QT_MOC_LITERAL(329, 19), // "on_HeaterOn_toggled"
QT_MOC_LITERAL(349, 7), // "checked"
QT_MOC_LITERAL(357, 25) // "on_powerDial_valueChanged"

    },
    "MainWindow\0errorMessage\0\0errIndex\0"
    "on_actionNew_triggered\0on_PenSize_valueChanged\0"
    "value\0on_startSimulation_released\0"
    "on_stopSimulation_released\0"
    "on_actionExit_triggered\0"
    "on_threadsNumber_valueChanged\0arg1\0"
    "on_topSilver_released\0on_topCopper_released\0"
    "on_topIron_released\0on_topQuartz_released\0"
    "on_topBrick_released\0on_topGlass_released\0"
    "on_HeaterOn_toggled\0checked\0"
    "on_powerDial_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  104,    2, 0x0a,    1 /* Public */,
       4,    0,  107,    2, 0x08,    3 /* Private */,
       5,    1,  108,    2, 0x08,    4 /* Private */,
       7,    0,  111,    2, 0x08,    6 /* Private */,
       8,    0,  112,    2, 0x08,    7 /* Private */,
       9,    0,  113,    2, 0x08,    8 /* Private */,
      10,    1,  114,    2, 0x08,    9 /* Private */,
      12,    0,  117,    2, 0x08,   11 /* Private */,
      13,    0,  118,    2, 0x08,   12 /* Private */,
      14,    0,  119,    2, 0x08,   13 /* Private */,
      15,    0,  120,    2, 0x08,   14 /* Private */,
      16,    0,  121,    2, 0x08,   15 /* Private */,
      17,    0,  122,    2, 0x08,   16 /* Private */,
      18,    1,  123,    2, 0x08,   17 /* Private */,
      20,    1,  126,    2, 0x08,   19 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->errorMessage((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->on_actionNew_triggered(); break;
        case 2: _t->on_PenSize_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->on_startSimulation_released(); break;
        case 4: _t->on_stopSimulation_released(); break;
        case 5: _t->on_actionExit_triggered(); break;
        case 6: _t->on_threadsNumber_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->on_topSilver_released(); break;
        case 8: _t->on_topCopper_released(); break;
        case 9: _t->on_topIron_released(); break;
        case 10: _t->on_topQuartz_released(); break;
        case 11: _t->on_topBrick_released(); break;
        case 12: _t->on_topGlass_released(); break;
        case 13: _t->on_HeaterOn_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 14: _t->on_powerDial_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}
struct qt_meta_stringdata_DrawArea_t {
    const uint offsetsAndSize[34];
    char stringdata0[269];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_DrawArea_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_DrawArea_t qt_meta_stringdata_DrawArea = {
    {
QT_MOC_LITERAL(0, 8), // "DrawArea"
QT_MOC_LITERAL(9, 21), // "signalCreateBurnerMap"
QT_MOC_LITERAL(31, 0), // ""
QT_MOC_LITERAL(32, 29), // "signalCreateTemperatureLayers"
QT_MOC_LITERAL(62, 18), // "signalDoSimulation"
QT_MOC_LITERAL(81, 18), // "signalAlphaUpdated"
QT_MOC_LITERAL(100, 11), // "signalError"
QT_MOC_LITERAL(112, 8), // "errIndex"
QT_MOC_LITERAL(121, 14), // "signalNoErrors"
QT_MOC_LITERAL(136, 14), // "updateTimeStep"
QT_MOC_LITERAL(151, 10), // "clearImage"
QT_MOC_LITERAL(162, 15), // "createBurnerMap"
QT_MOC_LITERAL(178, 14), // "paintBurnerMap"
QT_MOC_LITERAL(193, 26), // "createTemperatureMapLayers"
QT_MOC_LITERAL(220, 19), // "paintTemperatureMap"
QT_MOC_LITERAL(240, 15), // "startSimulation"
QT_MOC_LITERAL(256, 12) // "doSimulation"

    },
    "DrawArea\0signalCreateBurnerMap\0\0"
    "signalCreateTemperatureLayers\0"
    "signalDoSimulation\0signalAlphaUpdated\0"
    "signalError\0errIndex\0signalNoErrors\0"
    "updateTimeStep\0clearImage\0createBurnerMap\0"
    "paintBurnerMap\0createTemperatureMapLayers\0"
    "paintTemperatureMap\0startSimulation\0"
    "doSimulation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DrawArea[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   98,    2, 0x06,    1 /* Public */,
       3,    0,   99,    2, 0x06,    2 /* Public */,
       4,    0,  100,    2, 0x06,    3 /* Public */,
       5,    0,  101,    2, 0x06,    4 /* Public */,
       6,    1,  102,    2, 0x06,    5 /* Public */,
       8,    1,  105,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,  108,    2, 0x0a,    9 /* Public */,
      10,    0,  109,    2, 0x0a,   10 /* Public */,
      11,    0,  110,    2, 0x0a,   11 /* Public */,
      12,    0,  111,    2, 0x0a,   12 /* Public */,
      13,    0,  112,    2, 0x0a,   13 /* Public */,
      14,    0,  113,    2, 0x0a,   14 /* Public */,
      15,    0,  114,    2, 0x0a,   15 /* Public */,
      16,    0,  115,    2, 0x0a,   16 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DrawArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DrawArea *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signalCreateBurnerMap(); break;
        case 1: _t->signalCreateTemperatureLayers(); break;
        case 2: _t->signalDoSimulation(); break;
        case 3: _t->signalAlphaUpdated(); break;
        case 4: _t->signalError((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->signalNoErrors((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->updateTimeStep(); break;
        case 7: _t->clearImage(); break;
        case 8: _t->createBurnerMap(); break;
        case 9: _t->paintBurnerMap(); break;
        case 10: _t->createTemperatureMapLayers(); break;
        case 11: _t->paintTemperatureMap(); break;
        case 12: _t->startSimulation(); break;
        case 13: _t->doSimulation(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DrawArea::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DrawArea::signalCreateBurnerMap)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DrawArea::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DrawArea::signalCreateTemperatureLayers)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DrawArea::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DrawArea::signalDoSimulation)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DrawArea::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DrawArea::signalAlphaUpdated)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DrawArea::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DrawArea::signalError)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (DrawArea::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DrawArea::signalNoErrors)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject DrawArea::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_DrawArea.offsetsAndSize,
    qt_meta_data_DrawArea,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_DrawArea_t
, QtPrivate::TypeAndForceComplete<DrawArea, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *DrawArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DrawArea::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DrawArea.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DrawArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void DrawArea::signalCreateBurnerMap()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DrawArea::signalCreateTemperatureLayers()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DrawArea::signalDoSimulation()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DrawArea::signalAlphaUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void DrawArea::signalError(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DrawArea::signalNoErrors(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
