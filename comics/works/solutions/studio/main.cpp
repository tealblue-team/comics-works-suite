#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "comics/works/usecases/usecases.h"
#include "comics/works/entities/workspace/workspace.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    using namespace comics::works;

    // entities
    auto e_workspace = new entities::Workspace("workspace1", &app);
    qRegisterMetaType<entities::WorkspaceBase*>("entities::WorkspaceBase*");
    // usecases
    auto uc = new usecases(&app);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("e_workspace", e_workspace);
    engine.rootContext()->setContextProperty("uc", uc);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
