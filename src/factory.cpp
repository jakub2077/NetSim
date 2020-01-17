#include "factory.hpp"

bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors){
    if (node_colors[sender] == NodeColor::VERIFIED){
        return true;
    }
    node_colors[sender] = NodeColor::VISITED;

    if (sender->receiver_preferences_.get_preferences().empty()){
        throw std::logic_error("No receivers");
    }

    bool has_receivers = false;
    //bool storehouse_reached = false;
    for (auto r: sender->receiver_preferences_.get_preferences()) {
        if (r.first->get_receiver_type() == ReceiverType::STOREHOUSE) {
            has_receivers = true;
        } else if (r.first->get_receiver_type() == ReceiverType::WORKER) {
            IPackageReceiver* receiver_ptr = r.first;
            auto worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);

            if (sendrecv_ptr == sender){
                break;
            } else {
                has_receivers = true;

                if (node_colors[sendrecv_ptr] != NodeColor::VISITED) {
                    has_receivers = has_reachable_storehouse(sendrecv_ptr, node_colors);
                }
            }
        }
    }

    node_colors[sender] = NodeColor::VERIFIED;

    return has_receivers;
}

bool Factory::is_consistent() {
    std::map<const PackageSender*, NodeColor> node_colors;

    for (auto& r: ramps_) {
        node_colors[&r] = NodeColor::UNVISITED;
    }
    for (auto& w: workers_) {
        node_colors[&w] = NodeColor::UNVISITED;
    }

    try {
        for (auto& r: ramps_) {
            if (!(has_reachable_storehouse(&r, node_colors))) {
                return false;
            }
        }
    } catch (std::logic_error &e) {
        return false;
    }
    return true;
}

