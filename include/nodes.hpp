#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP

#include <utility>

#include "types.hpp"
#include "package.hpp"
#include "helpers.hpp"
#include "storage_types.hpp"

enum ReceiverType{
    WORKER,
    STOREHOUSE,
};

class IPackageReceiver{
public:
    using const_iterator = IPackageStockpile::const_iterator;

    virtual void receive_package(Package&& p) = 0;

    virtual ReceiverType get_receiver_type() const = 0;

    virtual ElementID get_id() const = 0;

    virtual const_iterator begin() const = 0;

    virtual const_iterator end() const = 0;

    virtual const_iterator cbegin() const = 0;

    virtual const_iterator cend() const = 0;
};

class ReceiverPreferences{
public:
    explicit ReceiverPreferences(ProbabilityGenerator pg = probability_generator);

    using preferences_t = std::map<IPackageReceiver*, double>;

    using const_iterator = preferences_t::const_iterator;

    using iterator = preferences_t::iterator;

    void add_receiver(IPackageReceiver* receiver);

    void remove_receiver(IPackageReceiver* receiver);

    void set_preferences(preferences_t r) {receivers_ = std::move(r);}

    IPackageReceiver* choose_receiver() const;

    const preferences_t& get_preferences() const { return receivers_;}

    const_iterator begin() const { return receivers_.cbegin();}

    const_iterator end() const { return receivers_.cend();}

    const_iterator cbegin() const { return receivers_.cbegin();}

    const_iterator cend() const { return receivers_.cend();}

private:
    preferences_t receivers_;

    ProbabilityGenerator pg_;
};

class PackageSender{
public:
    PackageSender() = default;

    explicit PackageSender(ReceiverPreferences& receiver_preferences) : receiver_preferences_(receiver_preferences) {}

    void send_package();

    std::optional<Package>& get_sending_buffer() {return buffer;};

    ReceiverPreferences receiver_preferences_;

protected:
    void push_package(Package&& package);

private:
    std::optional<Package> buffer;
};

class Storehouse: public IPackageReceiver{
public:
    explicit Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = std::make_unique<PackageQueue>(PackageQueue(FIFO))) : id_(id),  d_(d.release()){}

    void receive_package(Package&& p) override {d_->push(std::move(p));}

    ReceiverType get_receiver_type() const override {return ReceiverType::STOREHOUSE;}

    ElementID get_id() const override {return id_;}

    std::size_t get_queue_size() const{ return d_->size();}

    std::list<Package>& get_queue() { return d_->get_q();}

    const_iterator begin() const override { return d_->cbegin();}

    const_iterator end() const override { return d_->cend();}

    const_iterator cbegin() const override { return d_->cbegin();}

    const_iterator cend() const override { return d_->cend();}
private:
    ElementID id_;

    std::unique_ptr<IPackageStockpile> d_;
};

class Ramp: public PackageSender{
public:
    Ramp(ElementID id, TimeOffset di): id_(id), di_(di) {}

    Ramp(ElementID id, TimeOffset di, ReceiverPreferences& receiverPreferences) : PackageSender(receiverPreferences), id_(id), di_(di) {}

    void deliver_goods(Time t);

    TimeOffset get_delivery_interval() const {return  di_;}

    ElementID get_id() const {return id_;}
private:
    ElementID id_;

    TimeOffset di_;
};

class Worker: public PackageSender, public IPackageReceiver{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : id_(id), pd_(pd), q_(q.release()){}

    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q, ReceiverPreferences receiverPreferences) : PackageSender(receiverPreferences), id_(id), pd_(pd), q_(q.release()){}

    void do_work(Time t);

    TimeOffset get_processing_duration() {return pd_;}

    Time get_processing_start_time() {return processing_start_time;}

    void receive_package(Package&& p) override {q_->push(std::move(p));}

    ReceiverType get_receiver_type() const override {return ReceiverType::WORKER;}

    ElementID get_id() const override {return id_;}

    std::size_t get_queue_size() { return q_->size();}

    std::optional<Package>& get_now_processed() {return now_processed;}

    std::list<Package>& get_queue() { return q_->get_q();}

    const_iterator begin() const override { return q_->cbegin();}

    const_iterator end() const override { return q_->cend();}

    const_iterator cbegin() const override { return q_->cbegin();}

    const_iterator cend() const override { return q_->cend();}
private:
    ElementID id_;

    TimeOffset pd_;

    Time processing_start_time = 1;

    Time actual_processing_time = 1;

    std::unique_ptr<IPackageQueue> q_;

    std::optional<Package> now_processed;//Aktualnie przetwarzany produkt
};

#endif //NETSIM_NODES_HPP
