#ifndef REGISTER_H
#define REGISTER_H

namespace comics {
namespace works {
namespace entities {
class ProjectBase;
struct Register {
    ProjectBase* currentProject = nullptr;
};
}
}
}

#endif // REGISTER_H
