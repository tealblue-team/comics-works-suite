TARGET = "comics.works Studio"

ICON = $$PWD/comics-works-studio.icns
QMAKE_INFO_PLIST = $$PWD/Info.plist

# auto updater
QMAKE_LFLAGS += -Wl,-rpath,@loader_path/../Frameworks
LIBS += -framework AppKit
LIBS += -framework Carbon
LIBS += -framework Foundation
LIBS += -framework ApplicationServices
LIBS += -framework Sparkle

SPARKLE_PATH = $$PWD
QMAKE_LFLAGS += -F $$SPARKLE_PATH
QMAKE_OBJECTIVE_CFLAGS += -F $$SPARKLE_PATH

sparkle.path = Contents/Frameworks
sparkle.files = $$SPARKLE_PATH/Sparkle.framework
QMAKE_BUNDLE_DATA += sparkle

HEADERS += \
    $$PWD/AutoUpdater.h \
    $$PWD/SparkleAutoUpdater.h \
    $$PWD/CocoaInitializer.h

SOURCES += \
    $$PWD/AutoUpdater.cpp

OBJECTIVE_SOURCES += \
    $$PWD/SparkleAutoUpdater.mm \
    $$PWD/CocoaInitializer.mm
