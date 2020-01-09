#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include "package.hpp"

enum PackageQueueType {
    FIFO,
    LIFO
};

class IPackageStockpile {
public:
    using const_iterator = std::list<Package>::const_iterator;

    virtual void push(Package&& package) = 0;

    virtual bool empty() const = 0;

    virtual std::size_t size() const = 0;

    virtual const_iterator begin() const = 0;

    virtual const_iterator end() const = 0;

    virtual const_iterator cbegin() const = 0;

    virtual const_iterator cend() const = 0;

    virtual std::list<Package>& get_q() = 0;
};

class IPackageQueue : public IPackageStockpile {
public:
    virtual Package pop() = 0;

    virtual PackageQueueType get_queue_type() const = 0;
};

//in progress
class PackageQueue: public IPackageQueue {
public:
    explicit PackageQueue(PackageQueueType queue_type): queue_type_(queue_type) {}

    void push(Package&& product) override;

    bool empty() const override { return queue_.empty();}

    std::size_t size() const override { return queue_.size();}

    Package pop() override;

    PackageQueueType  get_queue_type() const override { return queue_type_;}

    const_iterator begin() const override { return queue_.cbegin();}

    const_iterator end() const override { return queue_.cend();}

    const_iterator cbegin() const override { return queue_.cbegin();}

    const_iterator cend() const override { return queue_.cend();}

    std::list<Package>& get_q() override { return queue_;}
private:
    std::list<Package> queue_;

    PackageQueueType queue_type_;
};

class PackageStockpile: public IPackageStockpile {
public:
    PackageStockpile() = default;

    explicit PackageStockpile(std::list<Package> list): list_(std::move(list)) {}

    void push(Package&& package) override {list_.push_back(std::move(package));}

    bool empty() const override { return list_.empty();};

    std::size_t size() const override { return list_.size();};

    const_iterator begin() const override { return list_.cbegin();}

    const_iterator end() const override { return list_.cend();}

    const_iterator cbegin() const override { return list_.cbegin();}

    const_iterator cend() const override { return list_.cend();}

    std::list<Package>& get_q() override { return list_;}
private:
    std::list<Package> list_;
};

#endif //NETSIM_STORAGE_TYPES_HPP
