#include "nodes.hpp"

void PackageSender::send_package(){
    IPackageReceiver* receiver = receiver_preferences.choose_receiver(-1);
    std::optional<Package> sending_buffer = get_sending_buffer();
    receiver->receive_package(std::move(sending_buffer.value()));
    buffer.reset();
}

std::optional<Package> PackageSender::get_sending_buffer(){
    return std::move(buffer);
}

void PackageSender::push_package(Package&& package){
    buffer.emplace(std::move(package));
}

void ReceiverPreferences::add_receiver(IPackageReceiver* receiver) {
    if (receivers_.empty()){
        receivers_[receiver] = 1;
    } else {
        double probability = rnd_fcn();

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
