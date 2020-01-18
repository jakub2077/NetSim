#ifndef NETSIM_FACTORY_HPP
#define NETSIM_FACTORY_HPP

#include "types.hpp"
#include "storage_types.hpp"
#include "nodes.hpp"

enum class NodeColor { UNVISITED, VISITED, VERIFIED };

bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors);


class Factory {
    
public:
    Factory() = default;


    void add_ramp(Ramp&& ramp) {ramps_.add(ramp);}
    void remove_ramp(ElementID id) {ramps_.remove_by_id(id);}
    NodeCollection<Ramp>::iterator find_ramp_by_id (ElementID id) {return ramps_.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator find_ramp_by_id (ElementID id) const {return ramps_.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator ramp_cbegin() const {return ramps_.cbegin();}
    NodeCollection<Ramp>::const_iterator ramp_cend() const {return ramps_.cend();}

    void add_worker(Worker&& worker) {workers_.add(worker);}
    void remove_worker(ElementID id) {workers_.remove_by_id(id);}
    NodeCollection<Worker>::iterator find_worker_by_id (ElementID id) {return workers_.find_by_id(id);}
    NodeCollection<Worker>::const_iterator find_worker_by_id (ElementID id) const {return workers_.find_by_id(id);}
    NodeCollection<Worker>::const_iterator worker_cbegin() const {return workers_.cbegin();}
    NodeCollection<Worker>::const_iterator worker_cend() const {return workers_.cend();}

    void add_storehouse(Storehouse&& (storehouse)) {storehouses_.add(storehouse);}
    void remove_storehouse(ElementID id) {storehouses_.remove_by_id(id);}
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
