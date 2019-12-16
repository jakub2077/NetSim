#include "storage_types.hpp"

//in progress
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
