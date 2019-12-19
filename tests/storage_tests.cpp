#include "gtest/gtest.h"

#include "storage_types.hpp"

TEST(PackageQueueTest, PopQueueFIFO){
    PackageQueue PQ_FIFO(PackageQueueType::FIFO);

    Package p1;
    Package p2;
    Package p3;

    PQ_FIFO.push(std::move(p1));
    PQ_FIFO.push(std::move(p2));

    PQ_FIFO.push(std::move(p3));

    Package temp = PQ_FIFO.pop();
    Package temp2 = PQ_FIFO.pop();

    ASSERT_EQ(temp.get_id(),1);
    ASSERT_EQ(temp2.get_id(),2);
}

TEST(PackageQueueTest, PopQueueLIFO){
    PackageQueue PQ_LIFO(PackageQueueType::LIFO);

    Package p1;
    Package p2;
    Package p3;

    PQ_LIFO.push(std::move(p1));
    PQ_LIFO.push(std::move(p2));
    PQ_LIFO.push(std::move(p3));

    Package temp = PQ_LIFO.pop();
    Package temp2 = PQ_LIFO.pop();
    Package temp3 = PQ_LIFO.pop();

    ASSERT_EQ(temp.get_id(),3);
    ASSERT_EQ(temp2.get_id(),2);
    ASSERT_EQ(temp3.get_id(),1);
}
