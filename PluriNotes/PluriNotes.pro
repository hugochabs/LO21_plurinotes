QT += widgets

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

SOURCES += \
    main.cpp \
    note.cpp \
    relation.cpp \
    notefille.cpp

HEADERS += \
    note.h \
    relation.h \
    notefille.h \
    exception.h

