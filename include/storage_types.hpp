#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <deque>
#include <set>

using ElementID=unsigned int;

static std::set<ElementID> assigned_IDs;
static std::set<ElementID> freed_IDs;

class Package {};

enum PackageQueueType {
    FIFO,
    LIFO
};

//in progress
class PackageQueue{
public:
    PackageQueue(PackageQueueType queue_type);
private:
    std::deque<Package> queue_;
    PackageQueueType queue_type_;
};

class IPackageStockpile {
public:
    virtual void push(Package&& package) {};

    virtual bool empty() {};

    virtual std::size_t size() {};
};

class IPackageQueue : IPackageStockpile {
    virtual Package pop() {};

    virtual PackageQueueType get_queuetype() {};
};

#endif //NETSIM_STORAGE_TYPES_HPP
