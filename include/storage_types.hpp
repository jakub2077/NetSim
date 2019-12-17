#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include "package.hpp"

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
    virtual void push(Package&& package) = 0;

    virtual bool empty() = 0;

    virtual std::size_t size() = 0;
};

class IPackageQueue : IPackageStockpile {
    virtual Package pop() = 0;

    virtual PackageQueueType get_queuetype() = 0;
};

#endif //NETSIM_STORAGE_TYPES_HPP
