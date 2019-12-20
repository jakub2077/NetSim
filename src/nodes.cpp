#include "nodes.hpp"

void ReceiverPreferences::add_receiver(IPackageReceiver* receiver, double probability) {
    for (auto& [r,p] : receivers_){
        p = p*(1-probability);
    }
    receivers_[receiver] = probability;
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
