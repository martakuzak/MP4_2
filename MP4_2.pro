#-------------------------------------------------
#
# Project created by QtCreator 2013-12-18T02:26:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MP4_2
TEMPLATE = app

INCLUDEPATH += ./Model\Dash \
               ./View \
               ./Model\Mpd \
               ./Model\Boxes \
               ./Controller

SOURCES += main.cpp\
        View\mainwindow.cpp \
    Model\Boxes\analyzer.cpp \
    Model\Boxes\box.cpp \
    Model\Boxes\boxfactory.cpp \
    Model\Dash\dashcreator.cpp \
    Model\Dash\dashwrapper.cpp \
    Model\Boxes\exceptions.cpp \
    Model\Mpd\mpd.cpp \
    Model\Mpd\period.cpp \
    Model\Boxes\sampleentry.cpp \
    Model\Boxes\sampletablebox.cpp \
    Model\Mpd\segmentlist.cpp \
    Model\Boxes\trackbox.cpp \
    Model\Boxes\treeitem.cpp \
    Model\Boxes\treemodel.cpp \
    Controller\controller.cpp

HEADERS  += View\mainwindow.h \
    Model\Boxes\analyzer.h \
    Model\Boxes\box.h \
    Model\Boxes\boxfactory.h \
    Model\Dash\dashcreator.h \
    Model\Dash\dashwrapper.h \
    Model\Boxes\exceptions.h \
    Model\Mpd\mpd.h \
    Model\Mpd\period.h \
    Model\Boxes\sampleentry.h \
    Model\Boxes\sampletablebox.h \
    Model\Mpd\segmentlist.h \
    Model\Boxes\trackbox.h \
    Model\Boxes\treeitem.h \
    Model\Boxes\treemodel.h \
    Controller\controller.h

FORMS
