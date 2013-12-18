#-------------------------------------------------
#
# Project created by QtCreator 2013-12-18T02:26:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MP4_2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    analyzer.cpp \
    box.cpp \
    boxfactory.cpp \
    dashcreator.cpp \
    dashproxy.cpp \
    exceptions.cpp \
    mpd.cpp \
    period.cpp \
    sampleentry.cpp \
    sampletablebox.cpp \
    segmentlist.cpp \
    trackbox.cpp \
    treeitem.cpp \
    treemodel.cpp

HEADERS  += mainwindow.h \
    analyzer.h \
    box.h \
    boxfactory.h \
    dashcreator.h \
    dashproxy.h \
    exceptions.h \
    mpd.h \
    period.h \
    sampleentry.h \
    sampletablebox.h \
    segmentlist.h \
    trackbox.h \
    treeitem.h \
    treemodel.h

FORMS    += mainwindow.ui
