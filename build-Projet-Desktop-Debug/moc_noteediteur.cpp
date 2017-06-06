/****************************************************************************
** Meta object code from reading C++ file 'noteediteur.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PluriNotes/noteediteur.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'noteediteur.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NoteEditeur_t {
    QByteArrayData data[7];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NoteEditeur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NoteEditeur_t qt_meta_stringdata_NoteEditeur = {
    {
QT_MOC_LITERAL(0, 0, 11), // "NoteEditeur"
QT_MOC_LITERAL(1, 12, 11), // "activerSave"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 10), // "changeTask"
QT_MOC_LITERAL(4, 36, 13), // "changeArticle"
QT_MOC_LITERAL(5, 50, 11), // "changeOther"
QT_MOC_LITERAL(6, 62, 4) // "addN"

    },
    "NoteEditeur\0activerSave\0\0changeTask\0"
    "changeArticle\0changeOther\0addN"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NoteEditeur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void NoteEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NoteEditeur *_t = static_cast<NoteEditeur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->activerSave(); break;
        case 1: _t->changeTask(); break;
        case 2: _t->changeArticle(); break;
        case 3: _t->changeOther(); break;
        case 4: _t->addN(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject NoteEditeur::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NoteEditeur.data,
      qt_meta_data_NoteEditeur,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NoteEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NoteEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NoteEditeur.stringdata0))
        return static_cast<void*>(const_cast< NoteEditeur*>(this));
    return QDialog::qt_metacast(_clname);
}

int NoteEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
