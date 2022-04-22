/****************************************************************************
** Meta object code from reading C++ file 'QtWidgetsClass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../QtWidgetsClass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtWidgetsClass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtWidgetsClass_t {
    QByteArrayData data[21];
    char stringdata0[306];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtWidgetsClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtWidgetsClass_t qt_meta_stringdata_QtWidgetsClass = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QtWidgetsClass"
QT_MOC_LITERAL(1, 15, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(4, 62, 11), // "on_finished"
QT_MOC_LITERAL(5, 74, 14), // "QNetworkReply*"
QT_MOC_LITERAL(6, 89, 5), // "reply"
QT_MOC_LITERAL(7, 95, 9), // "readyRead"
QT_MOC_LITERAL(8, 105, 12), // "readyReadTwo"
QT_MOC_LITERAL(9, 118, 14), // "readyReadThree"
QT_MOC_LITERAL(10, 133, 9), // "slotError"
QT_MOC_LITERAL(11, 143, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(12, 171, 13), // "slotSslErrors"
QT_MOC_LITERAL(13, 185, 16), // "QList<QSslError>"
QT_MOC_LITERAL(14, 202, 11), // "onConnected"
QT_MOC_LITERAL(15, 214, 14), // "onDisconnected"
QT_MOC_LITERAL(16, 229, 14), // "onTextReceived"
QT_MOC_LITERAL(17, 244, 4), // "data"
QT_MOC_LITERAL(18, 249, 21), // "onTextMessageReceived"
QT_MOC_LITERAL(19, 271, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(20, 300, 5) // "error"

    },
    "QtWidgetsClass\0on_pushButton_3_clicked\0"
    "\0on_pushButton_clicked\0on_finished\0"
    "QNetworkReply*\0reply\0readyRead\0"
    "readyReadTwo\0readyReadThree\0slotError\0"
    "QNetworkReply::NetworkError\0slotSslErrors\0"
    "QList<QSslError>\0onConnected\0"
    "onDisconnected\0onTextReceived\0data\0"
    "onTextMessageReceived\0"
    "QAbstractSocket::SocketError\0error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtWidgetsClass[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    1,   81,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    0,   85,    2, 0x0a /* Public */,
       9,    0,   86,    2, 0x0a /* Public */,
      10,    1,   87,    2, 0x0a /* Public */,
      12,    1,   90,    2, 0x0a /* Public */,
      14,    0,   93,    2, 0x0a /* Public */,
      15,    0,   94,    2, 0x0a /* Public */,
      16,    1,   95,    2, 0x0a /* Public */,
      18,    1,   98,    2, 0x0a /* Public */,
      10,    1,  101,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   17,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, 0x80000000 | 19,   20,

       0        // eod
};

void QtWidgetsClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtWidgetsClass *_t = static_cast<QtWidgetsClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_3_clicked(); break;
        case 1: _t->on_pushButton_clicked(); break;
        case 2: _t->on_finished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 3: _t->readyRead(); break;
        case 4: _t->readyReadTwo(); break;
        case 5: _t->readyReadThree(); break;
        case 6: _t->slotError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 7: _t->slotSslErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        case 8: _t->onConnected(); break;
        case 9: _t->onDisconnected(); break;
        case 10: _t->onTextReceived((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 11: _t->onTextMessageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->slotError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject QtWidgetsClass::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QtWidgetsClass.data,
      qt_meta_data_QtWidgetsClass,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QtWidgetsClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtWidgetsClass::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtWidgetsClass.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QtWidgetsClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
