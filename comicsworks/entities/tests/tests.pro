TEMPLATE = app
TARGET = tst_example
CONFIG += warn_on qmltestcase
SOURCES += tst_entities.cpp

DISTFILES += \
    tst_Grid.qml

include(../entities.pri)
