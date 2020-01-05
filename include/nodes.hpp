#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP

#include "types.hpp"
#include "package.hpp"
#include "helpers.hpp"

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
    ReceiverPreferences(ProbabilityGenerator pg): pg_(pg) {};

    using preferences_t = std::map<IPackageReceiver*, double>;

    using const_iterator = preferences_t::const_iterator;

    using iterator = preferences_t::iterator;

    void add_receiver(IPackageReceiver* receiver);

    void remove_receiver(IPackageReceiver* receiver);

    IPackageReceiver* choose_receiver(double fake_rnd = -1);

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
    PackageSender(const ReceiverPreferences& receiver_preferences);

    void send_package();

    std::optional<Package> get_sending_buffer();// {return std::optional<Package>();};

    ReceiverPreferences receiver_preferences;

//protected:
    void push_package(Package&& package);

private:
    std::optional<Package> buffer;
};

//not implemented (podstawowa implementacja do tetów)
class Storehouse: public IPackageReceiver{
public:
    Storehouse(ElementID id_) : id_(id_) {}

    void receive_package(Package&& p) override {(void)p;}

    ReceiverType get_receiver_type() const override { return ReceiverType::Storage;}

    ElementID get_id() const override {return id_;}
private:
    ElementID id_;
};

class Ramp: public PackageSender{
public:
    Ramp(ElementID id, TimeOffset di, ReceiverPreferences& receiverPreferences) : PackageSender(receiverPreferences), id_(id), di_(di) {}

    void deliver_goods(Time t);

    TimeOffset get_delivry_interval() { return  di_;}

    ElementID get_id() { return id_;}
private:
    ElementID id_;
    TimeOffset di_;
};


#endif //NETSIM_NODES_HPP
