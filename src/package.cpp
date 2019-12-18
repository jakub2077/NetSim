#include "package.hpp"

std::set<ElementID> Package::assigned_IDs = {};
std::set<ElementID> Package::freed_IDs = {};


Package::Package() {
    if (not freed_IDs.empty()){
        ElementID first_free_ID = *freed_IDs.begin();
        id_ = first_free_ID;
        freed_IDs.erase(freed_IDs.begin());
        assigned_IDs.insert(first_free_ID);
    }
    else if (not assigned_IDs.empty()){
        ElementID new_ID= *assigned_IDs.end() + 1;
        id_ = new_ID;
        assigned_IDs.insert(new_ID);
    }
    else{
        ElementID new_ID= 1;
        id_ = new_ID;
        assigned_IDs.insert(new_ID);
    }
}

/*
Package& Package::operator= (const Package&&) noexcept{
    ElementID tmp = this->id_;
    delete this;
    this->id_ = tmp;
    return *this;
}
*/
bool Package::operator==(const Package& rhs) const {
    return id_ == rhs.id_;
}

bool Package::operator!=(const Package& rhs) const {
    return !(rhs == *this);
}
