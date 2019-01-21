#-------------------------------------------------
#
# Project created by QtCreator 2017-03-20T14:33:45
#
#-------------------------------------------------

QT       += core gui widgets
include(../../rep-buildplugins.pri)

TARGET = otherblocks
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

SOURCES += otherblocksplugin.cpp \
    affinetransformations.cpp \
    affinewidget.cpp \
    commontransformwidget.cpp \
    perspectivetransformations.cpp \
    perspectivewidget.cpp \
    scaleprocessing.cpp \
    scalewidget.cpp \
    rotateprocessing.cpp \
    rotatewidget.cpp \
    translateprocessing.cpp \
    translatewidget.cpp \
    roiprocessing.cpp \
    roiwidget.cpp \
    delayprocessing.cpp \
    delaywidget.cpp \
    gaussiannoiseprocessing.cpp \
    gaussiannoisewidget.cpp \
    spnoiseprocessing.cpp \
    spnoisewidget.cpp

HEADERS += otherblocksplugin.h \
    affinetransformations.h \
    affinewidget.h \
    commontransformwidget.h \
    perspectivetransformations.h \
    perspectivewidget.h \
    blockenums.h \
    scaleprocessing.h \
    scalewidget.h \
    rotateprocessing.h \
    rotatewidget.h \
    translateprocessing.h \
    translatewidget.h \
    roiprocessing.h \
    roiwidget.h \
    delayprocessing.h \
    delaywidget.h \
    gaussiannoiseprocessing.h \
    gaussiannoisewidget.h \
    spnoiseprocessing.h \
    spnoisewidget.h
DISTFILES += otherblocks.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    scaleui.ui \
    rotateui.ui \
    translateui.ui \
    roiform.ui
