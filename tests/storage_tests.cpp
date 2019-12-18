#include "gtest/gtest.h"

#include "storage_types.hpp"

TEST(PackageQueueTest, push_and_pop_FIFO) {
    Package p1(1);
    Package p2(2);
    Package p3(3);

    PackageQueue q1(PackageQueueType::FIFO);

    q1.push(std::move(p1));
    q1.push(std::move(p2));
    q1.push(std::move(p3));

    EXPECT_EQ(q1.pop().get_id(),1);
    EXPECT_EQ(q1.pop().get_id(),2);
    EXPECT_EQ(q1.pop().get_id(),3);
}

TEST(PackageQueueTest, push_and_pop_LIFO) {
    Package p1(1);
    Package p2(2);
    Package p3(3);

    PackageQueue q1(PackageQueueType::LIFO);

    q1.push(std::move(p1));
    q1.push(std::move(p2));
    q1.push(std::move(p3));

    EXPECT_EQ(q1.pop().get_id(),3);
    EXPECT_EQ(q1.pop().get_id(),2);
    EXPECT_EQ(q1.pop().get_id(),1);
}