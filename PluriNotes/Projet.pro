#-------------------------------------------------
#
# Project created by QtCreator 2017-05-27T00:00:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projet
TEMPLATE = app



QMAKE_LFLAGS +=  -std=c++11

greaterThan(QT_MAJOR_VERSION, 4){
CONFIG += c++11
} else {
QMAKE_CXXFLAGS += -std=c++11
}

SOURCES += main.cpp \
    json.cpp \
    note.cpp \
    notefille.cpp \
    relation.cpp \
    noteediteur.cpp \
    notefille.cpp \
    mainwindow.cpp

HEADERS  += \
    exception.h \
    json.h \
    note.h \
    notefille.h \
    relation.h \
    noteediteur.h \
    mainwindow.h

FORMS    += \
    mainwindow.ui
