#include "gtest/gtest.h"
#include "simulation.hpp"

TEST(SimulationTest1, Simulate1) {
    Factory factory;
    factory.add_ramp(Ramp(1, 1));
    factory.add_worker(Worker(1, 1, std::make_unique<PackageQueue>(PackageQueueType::FIFO)));
    factory.add_storehouse(Storehouse(1));

    ReceiverPreferences prefs;

    Ramp& r = *(factory.find_ramp_by_id(1));
    r.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(1)));

    Worker& w = *(factory.find_worker_by_id(1));
    w.receiver_preferences_.add_receiver(&(*factory.find_storehouse_by_id(1)));

    simulate(factory, 3, [](Factory&, TimeOffset) {});

    // Robotnik ma pustą kolejkę i bufor.
    EXPECT_EQ(w.cbegin(), w.cend());
    EXPECT_FALSE(w.get_sending_buffer().has_value());

    // Magazyn zawiera półprodukt.
    auto storehouse_it = factory.storehouse_cbegin();
    ASSERT_NE(storehouse_it->cbegin(), storehouse_it->cend());
    EXPECT_EQ(storehouse_it->cbegin()->get_id(), 1);
}

TEST(SimulationTest2, Simulate2) {
    // R -> W1 -> S1
    //      W1 -> W2 -> S2

    Factory factory;
    factory.add_ramp(Ramp(1, 1));
    factory.add_worker(Worker(1, 1, std::make_unique<PackageQueue>(PackageQueueType::FIFO)));
    factory.add_worker(Worker(2, 1, std::make_unique<PackageQueue>(PackageQueueType::FIFO)));
    factory.add_storehouse(Storehouse(1));
    factory.add_storehouse(Storehouse(2));

    Ramp& r = *(factory.find_ramp_by_id(1));
    r.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(1)));

    Worker& w1 = *(factory.find_worker_by_id(1));
    w1.receiver_preferences_.add_receiver(&(*factory.find_storehouse_by_id(1)));
    w1.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(2)));

    Worker& w2 = *(factory.find_worker_by_id(2));
    w2.receiver_preferences_.add_receiver(&(*factory.find_storehouse_by_id(2)));

    EXPECT_FALSE(factory.is_consistent());

    simulate(factory, 3, [](Factory&, TimeOffset) {});

    // Robotnik ma pustą kolejkę i bufor.
    EXPECT_EQ(w1.cbegin(), w1.cend());
    EXPECT_FALSE(w1.get_sending_buffer().has_value());

    // Magazyn zawiera półprodukt.
    auto storehouse_it = factory.storehouse_cbegin();
    ASSERT_NE(storehouse_it->cbegin(), storehouse_it->cend());
    EXPECT_EQ(storehouse_it->cbegin()->get_id(), 1);
}

