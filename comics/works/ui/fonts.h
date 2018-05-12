#ifndef FONTS_H
#define FONTS_H

#include <QObject>
#include <QGuiApplication>

namespace comics {
namespace works {
namespace ui {

class Fonts : public QObject
{
    Q_OBJECT
public:
    explicit Fonts(QObject *parent = nullptr);
    void setDefaultFont(const QGuiApplication& app);
};

}
}
}

#endif // FONTS_H
