#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "comics/works/ui/fonts.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    comics::works::ui::Fonts* fonts = new comics::works::ui::Fonts();
    fonts->setDefaultFont(app);
    fonts->deleteLater();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
