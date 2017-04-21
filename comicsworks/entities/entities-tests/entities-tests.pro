TEMPLATE = app
CONFIG += warn_on qmltestcase
CONFIG -= app_bundle

SOURCES += tst_entities.cpp

DISTFILES += \
    tst_Grid.qml

include(../entities.pri)
