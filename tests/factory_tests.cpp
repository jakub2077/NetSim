#include "gtest/gtest.h"

#include "factory.hpp"

TEST(HasStorehouse, All){
    Storehouse s1(1);

    ProbabilityGenerator f = fixed_prob_06;
    ReceiverPreferences receiverPreferences1(f);
    receiverPreferences1.add_receiver(&s1);

    std::unique_ptr<IPackageQueue> pq1 = std::make_unique<PackageQueue>(PackageQueue(FIFO));
    Worker w1(1,1,std::move(pq1),receiverPreferences1);

    ReceiverPreferences receiverPreferences2(f);
    receiverPreferences2.add_receiver(&w1);
    Ramp r1(1,2,receiverPreferences2);

    Time i=1;
    while (i<=10) {
        //Dostawa
        r1.deliver_goods(i);
        std::cout << r1.get_sending_buffer().has_value();
        //Prekazanie
        r1.send_package();
        w1.send_package();

        //Przetworzenie
        w1.do_work(i);
        i++;
    }

    EXPECT_EQ(s1.get_queue_size(),5);
    EXPECT_EQ(w1.get_queue_size(),0);
    EXPECT_FALSE(w1.get_sending_buffer().has_value());

    std::map<const PackageSender*, NodeColor> node_colors;

    node_colors[&r1] = NodeColor::UNVISITED;
    node_colors[&w1] = NodeColor::UNVISITED;

    EXPECT_TRUE(has_reachable_storehouse(&r1,node_colors));
}