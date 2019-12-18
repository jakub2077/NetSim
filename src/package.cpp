#include "package.hpp"

std::set<ElementID> Package::assigned_IDs = {};
std::set<ElementID> Package::freed_IDs = {};


Package::Package() {
    if (not freed_IDs.empty()){
        ElementID first_free_ID = *freed_IDs.begin();
        ID_ = first_free_ID;
        freed_IDs.erase(freed_IDs.begin());
        assigned_IDs.insert(first_free_ID);
    }
    else if (not assigned_IDs.empty()){
        ElementID new_ID= *freed_IDs.end() + 1;
        ID_ = new_ID;
    }
    else{
        ElementID new_ID= 0;
        ID_ = new_ID;
    }
}


Package::Package(Package&& other){
    this->ID_ = other.ID_;
}
