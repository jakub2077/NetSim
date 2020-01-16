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

            }
            has_receivers = true;

            if (node_colors[sendrecv_ptr] != NodeColor::VISITED) {
                has_receivers = has_reachable_storehouse(sendrecv_ptr, node_colors);
            }
        }
    }

    node_colors[sender] = NodeColor::VERIFIED;

    return has_receivers;
}