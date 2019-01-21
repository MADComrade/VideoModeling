CONFIG += c++11

unix{
    CONFIG(debug, debug|release) {
        TARGET_SUFFIX = d
        DEFINES += DEBUG
        LIBS += -L"$${_PRO_FILE_PWD_}/../../debug"
        DESTDIR = $${_PRO_FILE_PWD_}/../../debug
        QMAKE_CXXFLAGS += -O0
    } else{
        CONFIG += staticlib
        LIBS += -L"$${_PRO_FILE_PWD_}/../../release"
        DESTDIR = $${_PRO_FILE_PWD_}/../../release
    }

    RCC_DIR     = $${_PRO_FILE_PWD_}/build
    MOC_DIR     = $${_PRO_FILE_PWD_}/build
    OBJECTS_DIR = $${_PRO_FILE_PWD_}/build
    UI_DIR      = $${_PRO_FILE_PWD_}/build
    TARGET      = $$join(TARGET,,,$${TARGET_SUFFIX})

    message(DESTDIR $$DESTDIR TARGET $$TARGET)
}

win32{
    CONFIG(debug, debug|release) {
        message(Debug On)
        CONFIG += DebugBuild
    } else:CONFIG(release, debug|release) {
        message(Release On)
        CONFIG += ReleaseBuild
    } else {
        error(Unsupported build)
    }

    BASEDIR = $${IN_PWD}
    DebugBuild {
        DESTDIR = $${_PRO_FILE_PWD_}/../../debug
        BUILDDIR = $${_PRO_FILE_PWD_}/../../trash/build-debug$${TARGET}
    }
    ReleaseBuild {
        DESTDIR = $${_PRO_FILE_PWD_}/../../release
        BUILDDIR = $${_PRO_FILE_PWD_}/../../trash/build-release$${TARGET}
    }
    OBJECTS_DIR = $${BUILDDIR}/obj
    MOC_DIR = $${BUILDDIR}/moc
    UI_DIR = $${BUILDDIR}/ui
    RCC_DIR = $${BUILDDIR}/rcc

    message(BUILDDIR $$BUILDDIR)
    message(BASEDIR $$BASEDIR DESTDIR $$DESTDIR TARGET $$TARGET)
}
