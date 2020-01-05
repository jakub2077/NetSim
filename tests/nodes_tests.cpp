#include "gtest/gtest.h"
#include "nodes.hpp"

TEST(ReceiverPreferencesTest, Insertion){
    PackageStockpile ps1;
    PackageStockpile ps2;
    PackageStockpile ps3;

    Storehouse s3(3);
    Storehouse s2(2);
    Storehouse s1(1);

    ProbabilityGenerator f = fixed_prob_05;
    ReceiverPreferences receiverPreferences(f);

    receiverPreferences.add_receiver(&s1);
    receiverPreferences.add_receiver(&s2);
    receiverPreferences.add_receiver(&s3);

    auto [r1,p1] = *receiverPreferences.begin();
    auto [r2,p2] = *receiverPreferences.begin();
    auto [r3,p3] = *receiverPreferences.begin();

    EXPECT_DOUBLE_EQ(p1,1.0/3.0);
    EXPECT_DOUBLE_EQ(p2,1.0/3.0);
    EXPECT_DOUBLE_EQ(p3,1.0/3.0);

    receiverPreferences.remove_receiver(&s3);

    auto [r32,p32] = *receiverPreferences.begin();

    EXPECT_EQ(p32,0.5);
}

TEST(ReceiverPreferencesTest, Randomizer){
    Storehouse s3(3);
    Storehouse s2(2);
    Storehouse s1(1);

    ProbabilityGenerator f = fixed_prob_05;
    ReceiverPreferences receiverPreferences(f);

    receiverPreferences.add_receiver(&s1);
    receiverPreferences.add_receiver(&s2);
    receiverPreferences.add_receiver(&s3);

    auto s = receiverPreferences.choose_receiver();

    EXPECT_EQ(s2.get_id(),s->get_id());
}


TEST(RampAndStorehouseTest, All){
    PackageStockpile p1;
    PackageStockpile p2;

    std::unique_ptr<IPackageStockpile> ps1 = std::make_unique<PackageStockpile>(std::move(p1));
    std::unique_ptr<IPackageStockpile> ps2 = std::make_unique<PackageStockpile>(std::move(p1));

    Storehouse s1(1,std::move(ps1));
    Storehouse s2(2,std::move(ps2));

    ProbabilityGenerator f = fixed_prob_06;
    ReceiverPreferences receiverPreferences(f);

    receiverPreferences.add_receiver(&s1);
    receiverPreferences.add_receiver(&s2);

    Ramp r1(1,2,receiverPreferences);

    Time i=0;
    while (i<10) {
        r1.deliver_goods(i);
        r1.send_package();
        i++;
    }

    EXPECT_TRUE(true);
}

