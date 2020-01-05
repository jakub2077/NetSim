#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include "package.hpp"

enum PackageQueueType {
    FIFO,
    LIFO
};

class IPackageStockpile {
public:
    virtual void push(Package&& package) = 0;

    virtual bool empty() const = 0;

    virtual std::size_t size() const = 0;
};

class IPackageQueue : IPackageStockpile {
public:
    virtual Package pop() = 0;

    virtual PackageQueueType get_queue_type() const = 0;
};

//in progress
class PackageQueue: IPackageQueue {
public:
    explicit PackageQueue(PackageQueueType queue_type): queue_type_(queue_type) {};

    void push(Package&& product) override;

    bool empty() const override { return queue_.empty();};

    std::size_t size() const override { return queue_.size();};

    Package pop() override;

    PackageQueueType  get_queue_type() const override { return queue_type_;};
private:
    std::list<Package> queue_;

    PackageQueueType queue_type_;
};

class PackageStockpile: public IPackageStockpile {
public:
    PackageStockpile() = default;

    PackageStockpile(std::list<Package> list): list_(std::move(list)) {}

    void push(Package&& package) override {list_.push_back(std::move(package));}

    bool empty() const override { return list_.empty();};

    std::size_t size() const override { return list_.size();};

private:
    std::list<Package> list_;
};

#endif //NETSIM_STORAGE_TYPES_HPP
