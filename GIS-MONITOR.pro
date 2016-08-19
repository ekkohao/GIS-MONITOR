#-------------------------------------------------
#
# Project created by QtCreator 2016-07-18T07:32:26
#
#-------------------------------------------------
QT       += core gui sql widgets

RC_FILE += main.rc

greaterThan(QT_MAJOR_VERSION, 4):

TARGET = GIS-MONITOR

TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    include/dbcon.cpp \
    include/stdafx.cpp \
    include/serialport.cpp \
    portselect.cpp

HEADERS  += mainwindow.h \
    include/dbcon.h \
    include/stdafx.h \
    include/targetver.h \
    include/serialport.h \
    portselect.h \
    include/haohelp.h

FORMS    += mainwindow.ui \
    portselect.ui

RESOURCES += \
    main.qrc
