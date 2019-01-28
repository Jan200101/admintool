#-------------------------------------------------
#
# Project created by QtCreator 2019-01-27T15:05:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = admintool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
 
CONFIG += c++11

SOURCES += \
        src/main.cpp \
        src/interface.cpp \
        src/CSVParser.cpp \
        src/CSVWriter.cpp \
        src/user.cpp \
        src/userparser.cpp

HEADERS += \
        include/main.h \
        include/interface.h \
        include/CSVParser.hpp \
        include/CSVWriter.hpp \
        include/user.hpp \
        include/userparser.hpp \
        include/defines.h

INCLUDEPATH += \
            include

FORMS += \
      ui/main.ui

TRANSLATIONS = \
             lang/admintool_en.ts \
             lang/admintool_de.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
