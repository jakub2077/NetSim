#include "storage_types.hpp"

//in progress

/*
PackageQueue::PackageQueue(PackageQueueType queue_type) {
    switch(queue_type){
        case PackageQueueType::FIFO:{
            std::deque<Package> queue=queue_;
            break;
        }
        case PackageQueueType::LIFO: {}
            std::deque<Package> queue=queue_;
            break;
        }
    }
*/

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
    Package package(100000);
    return package;
}