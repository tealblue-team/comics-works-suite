#ifndef UTILS_H
#define UTILS_H
#include <QObject>

namespace comics {
namespace works {
class Utils: public QObject {
    Q_OBJECT
public:
    explicit Utils(QObject* parent = nullptr);
    Q_INVOKABLE QString generateRandomId(int size);
};
}
}

#endif // UTILS_H
