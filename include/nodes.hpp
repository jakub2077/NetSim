#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP

#include "types.hpp"

enum ReceiverType{
    Worker,
    Storage;
};

class ReceiverPreferences{
};

class IPackageReceiver{
public:
    virtual void receive_package(Package&& p) = 0;

    virtual ReceiverType get_receiver_type() const = 0;

    virtual ElementID get_id() const = 0;
};

//not implemented
class PackageSender{
public:
    void send_package();

    std::optional<Package> get_sending_buffer();

    ReceiverPreferences receiver_preferences;
protected:
    void push_package(Package);

};

#endif //NETSIM_NODES_HPP
