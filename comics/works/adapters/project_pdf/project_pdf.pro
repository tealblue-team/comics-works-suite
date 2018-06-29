#-------------------------------------------------
#
# Project created by QtCreator 2018-05-30T07:41:08
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_project_pdf
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        tst_project_pdf.cpp

include(../project_json/project_json.pri)
include(../../entities/entities.pri)
include(../../entities/character/character.pri)
include(../../entities/panel/panel.pri)
include(../../entities/project/project.pri)
include(../../usecases/usecases.pri)

INCLUDEPATH += $$PWD/../../../..

include(project_pdf.pri)
