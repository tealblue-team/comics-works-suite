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

dsa.files = $$PWD/comics_works_piccolino_dsa.pub
dsa.path = Contents/Resources
QMAKE_BUNDLE_DATA += dsa

HEADERS += \
    $$PWD/AutoUpdater.h \
    $$PWD/SparkleAutoUpdater.h \
    $$PWD/CocoaInitializer.h

SOURCES += \
    $$PWD/AutoUpdater.cpp

OBJECTIVE_SOURCES += \
    $$PWD/SparkleAutoUpdater.mm \
    $$PWD/CocoaInitializer.mm

CFBundleVersion=$$system(defaults read $$PWD/Info.plist CFBundleVersion)
CFBundleShortVersionString=$$system(defaults read $$PWD/Info.plist CFBundleShortVersionString)
DEFINES += CFBundleVersion=\\\"$$CFBundleVersion\\\"
DEFINES += CFBundleShortVersionString=\\\"$$CFBundleShortVersionString\\\"

# Quick and dirty way to create DMG
APP=$$shell_quote($${OUT_PWD}/$${TARGET}.app)
#    DMG_FOLDER=$${OUT_PWD}/dmg

DISTRIBUTION_CN="3rd Party Mac Developer Application: Marco Piccolino Boniforti (8F9RJ9AFRH)"
#    INSTALLER_CN="3rd Party Mac Developer Installer: Marco Piccolino Boniforti (8F9RJ9AFRH)"

#    dmg.target = dmg
#    dmg.commands = cp $${PWD}/dmg.json $${OUT_PWD}; appdmg $${OUT_PWD}/dmg.json CWStudio.dmg
#    dmg.depends = $${APP} sign

sign.target = sign
sign.path = $${APP}/Contents/_CodeSignature/CodeResources
sign.commands = \
    dsymutil $${APP}/Contents/MacOS/$${TARGET} -o  $${TARGET}.dSYM; \
    macdeployqt $${APP} -verbose=1 -appstore-compliant; \
   #cp $${ROOTDIR}/assets/plugins/libqcocoa.dylib $${APP}/Contents/PlugIns/platforms/ ; \
   #find $${APP} -name "\"*.dSYM\"" -exec rm -rf {} \; ; \
    codesign --deep -s "\"$${DISTRIBUTION_CN}\"" -f $${APP}/Contents/Frameworks/Sparkle.framework/Versions/A/Resources/Autoupdate.app/; \
    codesign --deep -s "\"$${DISTRIBUTION_CN}\"" -f $${APP};
sign.depends = $${APP}

#    pkg.target = pkg
#    pkg.path = $${TARGET}.pkg
#    pkg.commands = productbuild --component $${APP} /Applications --sign "\"$${INSTALLER_CN}\"" $${TARGET}.pkg
#    pkg.depends = $${APP}

QMAKE_EXTRA_TARGETS += sign #dmg sign pkg
