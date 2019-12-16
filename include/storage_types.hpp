#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

class Package {};

enum PackageQueueType {
    FIFO,
    LIFO
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
