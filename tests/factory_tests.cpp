#include "gtest/gtest.h"

#include "factory.hpp"

TEST(FactoryTest1, UberTest) {
    // R -> W1 -> W2 -> S1
    //      W1 -> W3 -> W3

    Factory factory;
    factory.add_ramp(Ramp(1, 1));
    factory.add_worker(Worker(1, 1, std::make_unique<PackageQueue>(PackageQueueType::FIFO)));
    factory.add_worker(Worker(2, 1, std::make_unique<PackageQueue>(PackageQueueType::FIFO)));
    factory.add_worker(Worker(3, 1, std::make_unique<PackageQueue>(PackageQueueType::FIFO)));
    factory.add_storehouse(Storehouse(1));

    Ramp& r = *(factory.find_ramp_by_id(1));
    r.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(1)));

    Worker& w1 = *(factory.find_worker_by_id(1));
    w1.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(2)));
    w1.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(3)));

    Worker& w2 = *(factory.find_worker_by_id(2));
    w2.receiver_preferences_.add_receiver(&(*factory.find_storehouse_by_id(1)));

    Worker& w3 = *(factory.find_worker_by_id(3));
    w3.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(3)));

    EXPECT_FALSE(factory.is_consistent());
}