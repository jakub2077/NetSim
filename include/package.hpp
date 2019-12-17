#ifndef NETSIM_PACKAGE_HPP
#define NETSIM_PACKAGE_HPP

#include <string>

class Package {
public:
    Package(std::string id): id_(std::move(id)) {};

    Package(Package&& package) = default;

private:
    std::string id_;
};
#endif //NETSIM_PACKAGE_HPP

