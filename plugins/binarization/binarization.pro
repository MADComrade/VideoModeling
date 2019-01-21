#-------------------------------------------------
#
# Project created by QtCreator 2017-03-20T12:17:45
#
#-------------------------------------------------

QT       += core gui widgets
include(../../rep-buildplugins.pri)
TARGET = binarization
TEMPLATE = lib
CONFIG += plugin
INCLUDEPATH    += ../../VideoProcessingModeling/processingmoduleitem/common
INCLUDEPATH+= ../../common/

win32{
    LIBS+= $${DESTDIR}/common.lib
}

unix{
    LIBS += -lcommon$${TARGET_SUFFIX}
}
include(../../rep-opencv.pri)
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += binarizationplugin.cpp \
    adaptivethresholdprocessing.cpp \
    adaptivethresholdwidget.cpp \
    cannyprocessing.cpp \
    cannywidget.cpp \
    flaplaciandetector.cpp \
    flaplacianwidget.cpp \
    thresholdprocessing.cpp \
    thresholdwidget.cpp

HEADERS += binarizationplugin.h \
    adaptivethresholdprocessing.h \
    adaptivethresholdwidget.h \
    cannyprocessing.h \
    cannywidget.h \
    flaplaciandetector.h \
    flaplacianwidget.h \
    thresholdprocessing.h \
    thresholdwidget.h \
    blockenums.h
DISTFILES += binarization.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    cannywidget.ui \
    laplaciansettings.ui


