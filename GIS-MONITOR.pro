#-------------------------------------------------
#
# Project created by QtCreator 2016-07-18T07:32:26
#
#-------------------------------------------------
QT       += core gui sql widgets

RC_FILE += main.rc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GIS-MONITOR

TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    include/dbcon.cpp

HEADERS  += mainwindow.h \
    include/dbcon.h

FORMS    += mainwindow.ui

RESOURCES += \
    main.qrc
