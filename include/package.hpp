#ifndef NETSIM_PACKAGE_HPP
#define NETSIM_PACKAGE_HPP

#include <string>
#include <set>

using ElementID=unsigned int;

class Package {
public:
    explicit Package();

    Package(Package&& package) noexcept : id_(package.id_) {};

    //Package & operator= (const Package&& package) {return package.id_==id_;};
    
    ElementID get_id() const { return id_;};
private:
    ElementID id_;

    static std::set<ElementID> assigned_IDs;

    static std::set<ElementID> freed_IDs;
};
#endif //NETSIM_PACKAGE_HPP

