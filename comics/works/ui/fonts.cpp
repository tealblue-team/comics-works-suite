#include <QFontDatabase>
#include <QFont>
#include <QFontInfo>
#include <QDebug>
#include "fonts.h"

using namespace comics::works::ui;

Fonts::Fonts(QObject *parent) : QObject(parent)
{

}

void Fonts::setDefaultFont(const QGuiApplication& app)
{
    QFontDatabase::addApplicationFont(
                ":/qt-project.org/imports/comics/works/ui/assets/fonts/Source_Sans_Pro/SourceSansPro-SemiBold.ttf");
    int fontId = QFontDatabase::addApplicationFont(
                ":/qt-project.org/imports/comics/works/ui/assets/fonts/Source_Sans_Pro/SourceSansPro-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont appFont(fontFamily);
    appFont.setPixelSize(16);
    app.setFont(appFont);
}
