#include "nodes.hpp"

void PackageSender::send_package(){
    IPackageReceiver* receiver = receiver_preferences.choose_receiver();
    receiver->receive_package(std::move(buffer.value()));
    buffer.reset();
}

std::optional<Package> PackageSender::get_sending_buffer(){
    return std::move(buffer);
}

void PackageSender::push_package(Package&& package){
    buffer.emplace(std::move(package));
}

PackageSender::PackageSender(const ReceiverPreferences& receiver_preferences) : receiver_preferences(
        receiver_preferences) {}

void ReceiverPreferences::add_receiver(IPackageReceiver* receiver) {
    if (receivers_.empty()){
        receivers_[receiver] = 1;
    } else {
        double probability = pg_();

        for (auto& [r,p] : receivers_){
            p = p*(1-probability);
        }
        receivers_[receiver] = probability;
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* receiver) {
    for (auto& [r,p] : receivers_) {
        p = p / (1 - receivers_[receiver]);
    }
    receivers_.erase(receiver);
}

IPackageReceiver* ReceiverPreferences::choose_receiver(double fake_rnd) {
    double rnd;

    if (fake_rnd!=-1){
        rnd = fake_rnd;
    } else{
        rnd =((double)rand() / (RAND_MAX));
    }

    double distr=0;
    for (auto [r,p] : receivers_){
        if(rnd<=(distr+p)){
            return r;
        }
        distr += p;
    }
    auto [r,p] = *receivers_.begin();
    return r;
}

void Ramp::deliver_goods(Time t) {
    if (t==0) {
        Package p1;
        push_package(std::move(p1));
        send_package();
        Package p2;
        push_package(std::move(p2));
    } else if (t%di_==0) {
        send_package();
        Package p3;
        push_package(std::move(p3));
    }
}
