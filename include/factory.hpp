#ifndef NETSIM_FACTORY_HPP
#define NETSIM_FACTORY_HPP

#include "types.hpp"
#include "storage_types.hpp"
#include "nodes.hpp"

enum class NodeColor { UNVISITED, VISITED, VERIFIED };

bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors);

class Factory{
public:
    //Storehouse
    void add_storehouse(Storehouse&& storehouse) {storehouses_.add(storehouse);}

    void remove_storehouse(ElementID id) {storehouses_.remove_by_id(id);}

    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) { return storehouses_.find_by_id(id);}

    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const { return storehouses_.find_by_id(id);}

    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const {return storehouses_.cbegin();}

    NodeCollection<Storehouse>::const_iterator storehouse_cend() const {return storehouses_.cend();}

private:
    NodeCollection<Storehouse> storehouses_;
};

#endif //NETSIM_FACTORY_HPP
