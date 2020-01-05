#include "nodes.hpp"

void PackageSender::send_package(){
    if (buffer.has_value()){
        IPackageReceiver* receiver = receiver_preferences.choose_receiver();
        receiver->receive_package(std::move(buffer.value()));
        buffer.reset();
    }

}

std::optional<Package> PackageSender::get_sending_buffer(){
    return std::move(buffer);
}

void PackageSender::push_package(Package&& package){
    buffer.emplace(std::move(package));
}

PackageSender::PackageSender(ReceiverPreferences& receiver_preferences) : receiver_preferences(
        receiver_preferences) {}

void ReceiverPreferences::add_receiver(IPackageReceiver* receiver) {
    if (receivers_.empty()){
        receivers_[receiver] = 1;
    } else {
        double probability = 1.0/(receivers_.size()+1);

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

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    auto rnd = pg_();

    double distr=0;
    for(auto it=receivers_.rbegin();it!=receivers_.rend();++it){
        if(rnd<(distr+it->second)){
            return it->first;
        }
        distr += it->second;
    }

    auto [r,p] = *receivers_.begin();
    return r;
}

void Ramp::deliver_goods(Time t) {
    if (t==0) {
        Package p1;
        push_package(std::move(p1));
    } else if (t%di_==0) {
        Package p3;
        push_package(std::move(p3));
    }
}

void Worker::do_work(Time t) {
    if (now_processed.has_value()){
        if (actual_processing_time == 0) {
            processing_start_time = t;
            actual_processing_time = t + pd_;
            now_processed = q_->pop();
        }
        if (actual_processing_time == t) {
            actual_processing_time = 0;
            push_package(std::move(now_processed.value()));
            now_processed.reset();
        }
        else {
            actual_processing_time--;
        }
    }

}


