#include "gtest/gtest.h"

#include "package.hpp"

TEST(PackageTest, IDassignmentManual){

    Package* p1 = new Package();
    Package* p2 = new Package();

    ASSERT_EQ(p1->get_id(),1);
    ASSERT_EQ(p2->get_id(),2);

    delete p1;

    Package* p3 = new Package();

    ASSERT_EQ(p3->get_id(),1);

    delete p2;
    delete p3;
}