#-------------------------------------------------
#
# Project created by QtCreator 2017-03-20T14:24:36
#
#-------------------------------------------------

QT       += core gui widgets
include(../../rep-buildplugins.pri)

TARGET = filters
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

SOURCES += filtersplugin.cpp \
    bilateralfilter.cpp \
    correlationprocessing.cpp \
    correlationwidget.cpp \
    fbutterworthfilter.cpp \
    fbutterworthwidget.cpp \
    fgaussianprocessing.cpp \
    fgaussianwidget.cpp \
    fidealfilter.cpp \
    fidealfilterwidget.cpp \
    filterwithkernel.cpp \
    filterwithkernelwidget.cpp \
    gammaprocessing.cpp \
    gammawidget.cpp \
    gaussianfiter.cpp \
    histogrammaprocessing.cpp \
    histogrammawidget.cpp \
    logarithmprocessing.cpp \
    logarithmwidget.cpp \
    medianfilter.cpp \
    negativeprocessing.cpp \
    negativewidget.cpp

HEADERS += filtersplugin.h \
    bilateralfilter.h \
    correlationprocessing.h \
    correlationwidget.h \
    fbutterworthfilter.h \
    fbutterworthwidget.h \
    fgaussianprocessing.h \
    fgaussianwidget.h \
    fidealfilter.h \
    fidealfilterwidget.h \
    filterwithkernel.h \
    filterwithkernelwidget.h \
    gammaprocessing.h \
    gammawidget.h \
    gaussianfiter.h \
    histogrammaprocessing.h \
    histogrammawidget.h \
    logarithmprocessing.h \
    logarithmwidget.h \
    medianfilter.h \
    negativeprocessing.h \
    negativewidget.h \
    blockenums.h
DISTFILES += filters.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    correlationprocessingwidget.ui \
    fbutterworthsetting.ui \
    fgaussiansettingswidget.ui \
    gammaprocessingwidget.ui \
    logarithmprocessingwidget.ui
