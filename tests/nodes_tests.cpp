#include "gtest/gtest.h"
#include "nodes.hpp"

TEST(ReceiverPreferencesTest, Insertion){
    Storehouse s3(3);
    Storehouse s2(2);
    Storehouse s1(1);

    double (*fixed_prob_ptr)(){random_prob};

    ReceiverPreferences receiverPreferences(fixed_prob_ptr);

    receiverPreferences.add_receiver(&s1);
    receiverPreferences.add_receiver(&s2);
    receiverPreferences.add_receiver(&s3);

    auto [r1,p1] = *receiverPreferences.begin();

    EXPECT_EQ(p1,0.25);

    receiverPreferences.remove_receiver(&s3);

    auto [r2,p2] = *receiverPreferences.begin();

    EXPECT_EQ(p2,0.5);
}

TEST(ReceiverPreferencesTest, Randomizer){
    Storehouse s3(3);
    Storehouse s2(2);
    Storehouse s1(1);

    double (*fixed_prob_ptr)(){fixed_prob};

    ReceiverPreferences receiverPreferences(fixed_prob_ptr);

    double rnd=0.8;

    receiverPreferences.add_receiver(&s1);
    receiverPreferences.add_receiver(&s2);
    receiverPreferences.add_receiver(&s3);

    auto s = receiverPreferences.choose_receiver(rnd);

    EXPECT_EQ(s3.get_id(),s->get_id());
}
