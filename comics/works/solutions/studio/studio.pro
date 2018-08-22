QT += quick
CONFIG += c++11
TARGET = comics-works-studio

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp

RESOURCES += qml.qrc

INCLUDEPATH += $$PWD/../../../..
QML_IMPORT_PATH += $$PWD/../../../..

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(vendor/vendor.pri)

macx {
    include(platforms/macos/platform_macos.pri)
}

include(../../ui/ui.pri)
include(../../usecases/usecases.pri)
include(../../entities/character/character.pri)
include(../../entities/panel/panel.pri)
include(../../entities/project/project.pri)
include(../../adapters/project_json/project_json.pri)
include(../../adapters/project_pdf/project_pdf.pri)
include(../../utils/utils.pri)

samples.files = $$PWD/samples/heavyLoad1.cw.json
samples.path = Contents
QMAKE_BUNDLE_DATA += samples

OTHER_FILES += $$PWD/samples/heavyLoad1.cw.json
