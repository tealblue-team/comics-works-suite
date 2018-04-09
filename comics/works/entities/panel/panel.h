#ifndef PANEL_H
#define PANEL_H
#include "panel_base.h"

#include <QObject>

namespace comics {
namespace works {
namespace entities {
class Panel : public PanelBase
{
public:
    explicit Panel(const QString& eid, QObject *parent = nullptr);

    const QString& eid() const;
    int width() const;
    int height() const;

    void setEid(const QString&);
    void setWidth(int);
    void setHeight(int);
private:
    QString m_eid;
    int m_width = 0;
    int m_height = 0;
};
}
}
}

#endif // PANEL_H
