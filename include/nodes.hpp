#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP

#include "types.hpp"
#include "package.hpp"
#include "helpers.hpp"
#include "storage_types.hpp"

enum ReceiverType{
    Worker,
    Storage
};

class IPackageReceiver{
public:
    virtual void receive_package(Package&& p) = 0;

    virtual ReceiverType get_receiver_type() const = 0;

    virtual ElementID get_id() const = 0;
};

class ReceiverPreferences{
public:
    ReceiverPreferences(ProbabilityGenerator pg = random_prob): pg_(pg) {};

    using preferences_t = std::map<IPackageReceiver*, double>;

    using const_iterator = preferences_t::const_iterator;

    using iterator = preferences_t::iterator;

    void add_receiver(IPackageReceiver* receiver);

    void remove_receiver(IPackageReceiver* receiver);

    IPackageReceiver* choose_receiver();

    const_iterator cbegin() const { return receivers_.cbegin();}

    const_iterator cend() const { return receivers_.cend();}

    iterator begin() { return receivers_.begin();}

    iterator end() { return receivers_.end();}

private:
    preferences_t receivers_;

    ProbabilityGenerator pg_;
};

//not implemented
class PackageSender{
public:
    PackageSender() {};

    PackageSender(ReceiverPreferences& receiver_preferences);

    void send_package();

    std::optional<Package> get_sending_buffer();// {return std::optional<Package>();};

    ReceiverPreferences receiver_preferences;

protected:
    void push_package(Package&& package);

private:
    std::optional<Package> buffer;
};


class Storehouse: public IPackageReceiver{
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = nullptr) : id_(id),  d_(d.release()){}

    void receive_package(Package&& p) override {d_->push(std::move(p));}

    ReceiverType get_receiver_type() const override { return ReceiverType::Storage;}

    ElementID get_id() const override {return id_;}
private:
    ElementID id_;

    std::unique_ptr<IPackageStockpile> d_;
};

class Ramp: public PackageSender{
public:
    Ramp(ElementID id, TimeOffset di): PackageSender(), id_(id), di_(di) {}

    Ramp(ElementID id, TimeOffset di, ReceiverPreferences& receiverPreferences) : PackageSender(receiverPreferences), id_(id), di_(di) {}

    void deliver_goods(Time t);

    TimeOffset get_delivry_interval() { return  di_;}

    ElementID get_id() { return id_;}
private:
    ElementID id_;

    TimeOffset di_;
};


class Worker: public PackageSender, IPackageReceiver{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q): , id_(id), pd_(pd){}

    void do_work(Time t) {}

    TimeOffset get_processing_duration() {}

    Time get_processing_start_time() {}

    void receive_package(Package&& p) override {(void)p;}

    ReceiverType get_receiver_type() const override {return ReceiverType::Storage;}

    ElementID get_id() const override {return id_;}

private:
    ElementID id_;

    TimeOffset pd_;

    Time processing_start_time;

    TimeOffset processing_duration;

    Time left_processing_time;

};



#endif //NETSIM_NODES_HPP
