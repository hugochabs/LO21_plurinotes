QT += widgets
QT += core gui


QMAKE_LFLAGS +=  -std=c++11

greaterThan(QT_MAJOR_VERSION, 4){
CONFIG += c++11
} else {
QMAKE_CXXFLAGS += -std=c++11
}

SOURCES += \
    main.cpp \
    note.cpp \
    relation.cpp \
    notefille.cpp \
    json.cpp

HEADERS += \
    note.h \
    relation.h \
    notefille.h \
    exception.h \
    json.h

