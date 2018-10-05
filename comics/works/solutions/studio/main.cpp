#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "comics/works/utils/utils.h"
#include "comics/works/usecases/usecases.h"
#include "comics/works/entities/register.h"
#include "comics/works/adapters/project_json/project_json.h"
#include "comics/works/adapters/project_pdf/project_pdf.h"
#include "comics/works/ui/fonts.h"
#include "signal_handler.h"
#ifdef Q_OS_MAC
#include "comics/works/solutions/studio/platforms/macos/SparkleAutoUpdater.h"
#include "comics/works/solutions/studio/platforms/macos/CocoaInitializer.h"
#endif

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("comics.works");
    app.setOrganizationDomain("comics.works");
    app.setApplicationName("comics.works Studio");
    app.setApplicationVersion("0.1.0");

    auto signalHandler = new SignalHandler(&app);

#ifdef Q_OS_MAC
    AutoUpdater* updater = 0;
    CocoaInitializer initializer;
    bool updateEnabled = true;//settings.value(Constants::PREF_UPDATE_ENABLED, true).toBool();
    int updateInterval = 3600;//settings.value(Constants::PREF_UPDATE_INTERVAL, 3600).toInt();
    if (updateEnabled) {
        updater = new SparkleAutoUpdater("https://comics.works/studio/releases/macos/comics_works_studio_releases_macos.xml");
        QObject::connect(signalHandler, &SignalHandler::checkForUpdates, [updater]{
            updater->checkForUpdates();
            qDebug() << "Checking for updates...";
        });
        //updater->checkForUpdates();
        //        updater->setUpdateCheckInterval(updateInterval);
    } else {
        qDebug() << "Auto-update is disabled on Mac OS X.";
    }
#endif

    using namespace comics::works;

    // entities register
    entities::Register entities_register;
    // usecases
    auto uc = new usecases(&app);
    uc->entities_reg = &entities_register;
    // utils
    auto utils = new Utils(&app);
    // adapters
    auto projectJson = new adapters::ProjectJson(&app);
    projectJson->setUsecases(uc);
    projectJson->setUtils(utils);

    auto projectPdf = new adapters::ProjectPdf(&app);
    projectPdf->setUsecases(uc);
    projectJson->setUtils(utils);

    ui::Fonts* fonts = new comics::works::ui::Fonts();
    fonts->setDefaultFont(app);
    fonts->deleteLater();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("signalHandler", signalHandler);
    engine.rootContext()->setContextProperty("uc", uc);
    engine.rootContext()->setContextProperty("utils", utils);
    engine.rootContext()->setContextProperty("projectJson", projectJson);
    engine.rootContext()->setContextProperty("projectPdf", projectPdf);
    engine.rootContext()->setContextProperty("applicationVersion", app.applicationVersion());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    bool normalExit = app.exec();

    // Delete update on app quit, or maybe use a unique_ptr
    delete updater;

    return normalExit;
}
