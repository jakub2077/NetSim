#include "nodes.hpp"

void PackageSender::send_package(){
    if (buffer.has_value()){
        IPackageReceiver* receiver = receiver_preferences_.choose_receiver();
        receiver->receive_package(std::move(buffer.value()));
        buffer.reset();
    }

}

void PackageSender::push_package(Package&& package){
    buffer.emplace(std::move(package));
}


void ReceiverPreferences::add_receiver(IPackageReceiver* receiver) {
    if (receivers_.empty()){
        receivers_[receiver] = 1;
    } else {
        double probability = 1.0/(receivers_.size()+1);

        for (auto& p : receivers_){
            p.second = p.second*(1-probability);
        }
        receivers_[receiver] = probability;
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* receiver) {
    double tmp=receivers_[receiver];
    receivers_.erase(receiver);
    for (auto& p : receivers_) {
        p.second = p.second / (1 - tmp);
    }

}

IPackageReceiver* ReceiverPreferences::choose_receiver() const{
    auto rnd = pg_();

    double distr=0;
    for(auto it=receivers_.begin();it!=receivers_.end();++it){
        if(rnd<(distr+it->second)){
            return it->first;
        }
        distr += it->second;
    }

    auto r = *receivers_.begin();
    return r.first;
}

ReceiverPreferences::ReceiverPreferences(ProbabilityGenerator pg) : pg_(std::move(pg)){}


void Ramp::deliver_goods(Time t) {
    if (t==1) {
        Package p1;
        push_package(std::move(p1));
    } else if ((t-1)%di_==0) {
        Package p3;
        push_package(std::move(p3));
    }
}

void Worker::do_work(Time t) {
    if (now_processed.has_value()||!(q_->empty())){
        if (actual_processing_time == 1) {
            processing_start_time = t;
            actual_processing_time = t + pd_ - 1;
            now_processed = q_->pop();
        }
        if (actual_processing_time == t) {
            actual_processing_time = 1;
            push_package(std::move(now_processed.value()));
            now_processed.reset();
        }
    }
}


