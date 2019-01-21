QT       += widgets
include(../rep-opencv.pri)
include(../rep-buildproject.pri)
TARGET = common
TEMPLATE = lib

CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arrowblock.cpp \
    baseprocessingwidget.cpp \
    commonmanager.cpp \
    commonprocessing.cpp \
    commonwidget.cpp \
    inputdataitem.cpp \
    inputvideoitem.cpp \
    interfaceofmoduleitem.cpp \
    outputdataitem.cpp \
    outputvideoitem.cpp \
    singletonthread.cpp \
    additionmethods.cpp \
    simulationsingleton.cpp

HEADERS += \
    arrowblock.h \
    baseprocessingwidget.h \
    commonmanager.h \
    commonprocessing.h \
    commontemplateblock.h \
    commontemplatemanager.h \
    commonwidget.h \
    inputdataitem.h \
    inputvideoitem.h \
    interfaceofmoduleitem.h \
    moduleconfig.h \
    outputdataitem.h \
    outputvideoitem.h \
    singletonthread.h \
    additionmethods.h \
    settings_block_io.h \
    simulationsingleton.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    baseprocessingwidget.ui
