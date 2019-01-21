INCLUDEPATH += D:/opencv/build/install/include
LIBS += -LD:/opencv/build/install/x64/vc15/lib

CONFIG(debug,debug|release) {
LIBS += -lopencv_core341d
LIBS += -lopencv_imgproc341d
LIBS += -lopencv_highgui341d
LIBS += -lopencv_features2d341d
LIBS += -lopencv_videoio341d
LIBS += -lopencv_video341d
LIBS += -lopencv_objdetect341d
LIBS += -lopencv_imgcodecs341d
LIBS += -lopencv_calib3d341d
LIBS += -lopencv_xfeatures2d341d
LIBS += -lopencv_videostab341d
}
CONFIG(release,debug|release) {
LIBS += -lopencv_core341
LIBS += -lopencv_imgproc341
LIBS += -lopencv_highgui341
LIBS += -lopencv_features2d341
LIBS += -lopencv_videoio341
LIBS += -lopencv_video341
LIBS += -lopencv_objdetect341
LIBS += -lopencv_imgcodecs341
LIBS += -lopencv_calib3d341
LIBS += -lopencv_xfeatures2d341
LIBS += -lopencv_videostab341
}



#INCLUDEPATH += D:/opencv/build/install/include
#LIBS +=-L"D:/opencv/build/install/x86/mingw/lib"
#LIBS +=  \
#        -lopencv_core331 \
#        -lopencv_features2d331 \
#        -lopencv_highgui331 \
#        -lopencv_imgcodecs331 \
#        -lopencv_imgproc331 \
#        -lopencv_video331 \
#        -lopencv_videoio331 \
#        -lopencv_videostab331 \
#        -lopencv_xfeatures2d331 \
