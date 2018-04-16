#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "comics/works/usecases/usecases.h"
#include "comics/works/entities/register.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    using namespace comics::works;

    // entities register
    entities::Register entities_register;
    // usecases
    auto uc = new usecases(&app);
    uc->entities_reg = &entities_register;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("uc", uc);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
