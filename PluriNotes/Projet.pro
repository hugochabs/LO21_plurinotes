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
QMAKE_CXXFLAGS_WARN_ON += -Wno-reorder
}

SOURCES += main.cpp \
    json.cpp \
    note.cpp \
    notefille.cpp \
    relation.cpp \
    noteediteur.cpp \
    notefille.cpp \
    mainwindow.cpp \
    initialisationnote.cpp \
    slotnote.cpp \
    trashviewer.cpp \
    relationviewer.cpp \
    colleague.cpp \
    alertviewer.cpp

HEADERS  += \
    exception.h \
    json.h \
    note.h \
    notefille.h \
    relation.h \
    noteediteur.h \
    mainwindow.h \
    trashviewer.h \
    relationviewer.h \
    colleague.h \
    alertviewer.h

FORMS    += \
    mainwindow.ui \
    trashviewer.ui \
    relationviewer.ui
