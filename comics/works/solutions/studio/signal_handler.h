#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include <QObject>

class SignalHandler : public QObject
{
    Q_OBJECT
public:
    explicit SignalHandler(QObject *parent = nullptr);
signals:
    Q_INVOKABLE void checkForUpdates();
};

#endif // SIGNAL_HANDLER_H
