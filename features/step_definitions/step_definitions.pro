TEMPLATE = app
CONFIG -= app_bundle

QT += testlib

SOURCES += \
    QtTestCukeSteps.cpp

INCLUDEPATH += /usr/local/Cellar/boost/1.65.1/include
LIBS += /usr/local/Cellar/boost/1.65.1/lib/libboost_filesystem.a
LIBS += /usr/local/Cellar/boost/1.65.1/lib/libboost_regex.a
LIBS += /usr/local/Cellar/boost/1.65.1/lib/libboost_program_options.a
LIBS += /usr/local/Cellar/boost/1.65.1/lib/libboost_system.a

INCLUDEPATH += ../../../cucumber-cpp/include
CUKES_SOURCE_DIR = $$PWD
CUKES_TARGET_DIR = $$OUT_PWD
unix {
    LIBFILE = $$CUKES_SOURCE_DIR/libcucumber-cpp.a
    QMAKE_PRE_LINK += $$quote(cp $$LIBFILE $$CUKES_TARGET_DIR)
}
LIBS += $$CUKES_TARGET_DIR/libcucumber-cpp.a

include(../../comics/works/entities/entities.pri)
include(../../comics/works/entities/panel/panel.pri)
include(../../comics/works/entities/workspace/workspace.pri)
include(../../comics/works/usecases/usecases.pri)

INCLUDEPATH += $$PWD/../..
