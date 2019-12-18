#include "storage_types.hpp"

void PackageQueue::push(Package &&product) {
    switch(queue_type_){
        case PackageQueueType::FIFO:{
            queue_.push_back(std::move(product));
            break;
        }
        case PackageQueueType::LIFO:{
            queue_.push_back(std::move(product));
            break;
        }
    }
}

Package PackageQueue::pop() {
    switch(queue_type_){
        case PackageQueueType::FIFO:{
            Package package(std::move(queue_.front()));
            queue_.pop_front();
            return package;
        }
        case PackageQueueType::LIFO:{
            Package package(std::move(queue_.back()));
            queue_.pop_back();
            return package;
        }
    }
    Package package;
    return package;
}