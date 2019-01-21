QT += widgets multimedia
include(../rep-buildproject.pri)

INCLUDEPATH+= ../common/

win32{
    LIBS+= $${DESTDIR}/common.lib
}

unix{
    LIBS += -lcommon$${TARGET_SUFFIX}
}

VERSION = 1.3
DEFINES += APP_VERSION=\\\"$$VERSION\\\"


HEADERS	    =   mainwindow.h \
                diagramscene.h \
                diagramtextitem.h \
    processingmoduleitem/input_output/videoinputblock.h \
    processingmoduleitem/input_output/videooutputblock.h \
    processingmoduleitem/input_output/inoutblocklist.h \    
    processingmoduleitem/input_output/videoIn/videoinmanager.h \
    processingmoduleitem/input_output/videoIn/videoimageplayer.h \
    processingmoduleitem/input_output/videoIn/videoinwidget.h \
    processingmoduleitem/input_output/videoOut/videooutmanager.h \
    processingmoduleitem/input_output/videoOut/videooutwidget.h \   
    processingmoduleitem/generatorofmodules.h \   
    processingmoduleitem/input_output/videoIn/imageplayer.h \
    processingmoduleitem/input_output/videoIn/imageplayerwidget.h \
    processingmoduleitem/input_output/videoIn/paramvideoinput.h \
    processingmoduleitem/input_output/videoIn/paramvideoinwidget.h \    
    processingmoduleitem/common/plugininterface.h \
    pluginmanager.h \
    itemsonworkspace.h \
    moduleparameter.h \
    processingmoduleitem/input_output/videoIn/webcamplayer.h \
    processingmoduleitem/input_output/videoIn/webcamwidget.h

SOURCES	    =   mainwindow.cpp \
                main.cpp \
		diagramtextitem.cpp \
                diagramscene.cpp \
    processingmoduleitem/input_output/videoinputblock.cpp \
    processingmoduleitem/input_output/videooutputblock.cpp \
    processingmoduleitem/input_output/inoutblocklist.cpp \
    processingmoduleitem/input_output/videoIn/videoinmanager.cpp \
    processingmoduleitem/input_output/videoIn/videoimageplayer.cpp \
    processingmoduleitem/input_output/videoIn/videoinwidget.cpp \
    processingmoduleitem/input_output/videoOut/videooutmanager.cpp \
    processingmoduleitem/input_output/videoOut/videooutwidget.cpp \  
    processingmoduleitem/generatorofmodules.cpp \   
    processingmoduleitem/input_output/videoIn/imageplayer.cpp \
    processingmoduleitem/input_output/videoIn/imageplayerwidget.cpp \
    processingmoduleitem/input_output/videoIn/paramvideoinput.cpp \
    processingmoduleitem/input_output/videoIn/paramvideoinwidget.cpp \    
    pluginmanager.cpp \
    itemsonworkspace.cpp \
    moduleparameter.cpp \
    processingmoduleitem/input_output/videoIn/webcamplayer.cpp \
    processingmoduleitem/input_output/videoIn/webcamwidget.cpp

FORMS += \
    processingmoduleitem/input_output/videoIn/videoinwidget.ui \
    processingmoduleitem/input_output/videoOut/videooutwidget.ui \

RESOURCES   =	diagramscene.qrc

include(../rep-opencv.pri)


