#include "gtest/gtest.h"

#include "storage_types.hpp"

TEST(PackageQueueTest, push_and_pop_FIFO) {

    Package* p1 = new Package();
    Package* p2 = new Package();
    Package* p3 = new Package();

    PackageQueue q1(PackageQueueType::FIFO);

    q1.push(std::move(*p1));
    q1.push(std::move(*p2));
    q1.push(std::move(*p3));

    EXPECT_EQ(q1.pop().get_id(),1);
    EXPECT_EQ(q1.pop().get_id(),2);
    EXPECT_EQ(q1.pop().get_id(),3);

    delete p1;
    delete p2;
    delete p3;
}

TEST(PackageQueueTest, push_and_pop_LIFO) {

    Package* p1 = new Package();
    Package* p2 = new Package();
    Package* p3 = new Package();

    PackageQueue q1(PackageQueueType::LIFO);

    q1.push(std::move(*p1));
    q1.push(std::move(*p2));
    q1.push(std::move(*p3));

    EXPECT_EQ(q1.pop().get_id(),3);
    EXPECT_EQ(q1.pop().get_id(),2);
    EXPECT_EQ(q1.pop().get_id(),1);

    delete p1;
    delete p2;
    delete p3;
}

TEST(PackageQueueTest, PopQueueFIFO){
    PackageQueue PQ_FIFO(PackageQueueType::FIFO);
    PQ_FIFO.push(Package());
    PQ_FIFO.push(Package());
    PQ_FIFO.push(Package());

    Package temp = PQ_FIFO.pop();
    Package temp2 = PQ_FIFO.pop();

    ASSERT_EQ(temp.get_id(),1);
    ASSERT_EQ(temp2.get_id(),2);
}

TEST(PackageQueueTest, PopQueueLIFO){
    PackageQueue PQ_LIFO(PackageQueueType::LIFO);
    PQ_LIFO.push(Package());
    PQ_LIFO.push(Package());
    PQ_LIFO.push(Package());

    Package temp = PQ_LIFO.pop();
    Package temp2 = PQ_LIFO.pop();

    ASSERT_EQ(temp.get_id(),3);
    ASSERT_EQ(temp2.get_id(),2);
}
