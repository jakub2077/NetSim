#ifndef NETSIM_FACTORY_HPP
#define NETSIM_FACTORY_HPP

#include "types.hpp"
#include "storage_types.hpp"
#include "nodes.hpp"

template <class Node> class NodeCollection{
public:
    NodeCollection() {}

    using container_t = typename std::list<Node>;

    using iterator = typename container_t::iterator;

    using const_iterator = typename container_t::const_iterator;

    NodeCollection(container_t collection) : collection_(collection) {}

    void add(Node& node);

    void remove_by_id(ElementID id_);

    typename NodeCollection<Node>::iterator find_by_id(ElementID id_);

    typename NodeCollection<Node>::const_iterator find_by_id(ElementID id_) const;

    typename NodeCollection<Node>::iterator begin() { return collection_.begin();}

    typename NodeCollection<Node>::iterator end() { return collection_.end();}

    typename NodeCollection<Node>::const_iterator cbegin() const { return collection_.cbegin();}

    typename NodeCollection<Node>::const_iterator cend() const { return collection_.cend();}

private:
    container_t collection_;
};

template <class Node>
void NodeCollection<Node>::add(Node& node){
    collection_.push_back(std::move(node));
}

template <class Node>
void NodeCollection<Node>::remove_by_id(ElementID id_){
    auto position = find_by_id(id_);
    if (position!=collection_.end()){
        collection_.erase(position);
    }
}

template <class Node>
typename NodeCollection<Node>::iterator NodeCollection<Node>::find_by_id(ElementID id_){
    return std::find_if(collection_.begin(),collection_.end(),
                        [id_](const auto& elem){ return (elem.get_id() == id_);});
}

template <class Node>
typename NodeCollection<Node>::const_iterator NodeCollection<Node>::find_by_id(ElementID id_) const{
    return std::find_if(collection_.begin(),collection_.end(),
                        [id_](const auto& elem){ return (elem.get_id() == id_);});
}

enum class NodeColor { UNVISITED, VISITED, VERIFIED };

bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors);


class Factory {
    
public:
    Factory() = default;


    void add_ramp(Ramp&& ramp) {ramps_.add(ramp);}
    void remove_ramp(ElementID id);
    NodeCollection<Ramp>::iterator find_ramp_by_id (ElementID id) {return ramps_.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator find_ramp_by_id (ElementID id) const {return ramps_.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator ramp_cbegin() const {return ramps_.cbegin();}
    NodeCollection<Ramp>::const_iterator ramp_cend() const {return ramps_.cend();}

    void add_worker(Worker&& worker) {workers_.add(worker);}
    void remove_worker(ElementID id);
    NodeCollection<Worker>::iterator find_worker_by_id (ElementID id) {return workers_.find_by_id(id);}
    NodeCollection<Worker>::const_iterator find_worker_by_id (ElementID id) const {return workers_.find_by_id(id);}
    NodeCollection<Worker>::const_iterator worker_cbegin() const {return workers_.cbegin();}
    NodeCollection<Worker>::const_iterator worker_cend() const {return workers_.cend();}

    void add_storehouse(Storehouse&& (storehouse)) {storehouses_.add(storehouse);}
    void remove_storehouse(ElementID id);
    NodeCollection<Storehouse>::iterator find_storehouse_by_id (ElementID id) {return storehouses_.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id (ElementID id) const {return storehouses_.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const {return storehouses_.cbegin();}
    NodeCollection<Storehouse>::const_iterator storehouse_cend() const {return storehouses_.cend();}

    bool is_consistent();
    void do_deliveries(Time t);
    void do_package_passing();
    void do_work(Time t);

private:
    NodeCollection<Ramp> ramps_;
    NodeCollection<Worker> workers_;
    NodeCollection<Storehouse> storehouses_;
};

#endif //NETSIM_FACTORY_HPP
