#ifndef PANEL_BASE_H
#define PANEL_BASE_H

#include <QObject>

namespace comics {
namespace works {
namespace entities {
class PanelBase : public QObject
{
    Q_OBJECT
protected:
    explicit PanelBase(QObject *parent = nullptr) {}
public:
    virtual const QString& eid() const = 0;
    virtual int width() const = 0;
    virtual int height() const = 0;

    virtual void setEid(const QString&) = 0;
    virtual void setWidth(int) = 0;
    virtual void setHeight(int) = 0;
};
}
}
}

#endif // PANEL_BASE_H
