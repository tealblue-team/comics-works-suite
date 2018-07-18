#include "utils.h"
#include <array>
#include <cmath>
#include <QString>

comics::works::Utils::Utils(QObject* parent) : QObject(parent) {}

QString comics::works::Utils::generateRandomId(int size) {
    std::srand(std::time(0));
    std::array<char,26> abc({{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}});
    QString randomId = "";
    for (int i=0;i<size;++i) {
        randomId += QString(abc[std::rand()/((RAND_MAX + 1u)/26)]);
    }
    return randomId.toUpper();
}
