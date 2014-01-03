#-------------------------------------------------
#
# Project created by QtCreator 2013-12-18T02:26:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MP4_2
TEMPLATE = app

INCLUDEPATH += ./DASH \
               ./GUI \
               ./MPD \
               ./TREE

SOURCES += main.cpp\
        GUI\mainwindow.cpp \
    TREE\analyzer.cpp \
    TREE\box.cpp \
    TREE\boxfactory.cpp \
    DASH\dashcreator.cpp \
    DASH\dashproxy.cpp \
    TREE\exceptions.cpp \
    MPD\mpd.cpp \
    MPD\period.cpp \
    TREE\sampleentry.cpp \
    TREE\sampletablebox.cpp \
    MPD\segmentlist.cpp \
    TREE\trackbox.cpp \
    TREE\treeitem.cpp \
    TREE\treemodel.cpp

HEADERS  += GUI\mainwindow.h \
    TREE\analyzer.h \
    TREE\box.h \
    TREE\boxfactory.h \
    DASH\dashcreator.h \
    DASH\dashproxy.h \
    TREE\exceptions.h \
    MPD\mpd.h \
    MPD\period.h \
    TREE\sampleentry.h \
    TREE\sampletablebox.h \
    MPD\segmentlist.h \
    TREE\trackbox.h \
    TREE\treeitem.h \
    TREE\treemodel.h

FORMS
