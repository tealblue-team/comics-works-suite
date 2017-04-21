TEMPLATE = app

CONFIG += qmltestcase warn_on
CONFIG -= app_bundle

SOURCES += \
    tst_usecases.cpp

DISTFILES += \
    tst_usecases.qml

include(../../../entities/entities.pri)
include(../../usecases.pri)
