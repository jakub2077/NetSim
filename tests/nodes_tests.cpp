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

    auto p1 = *receiverPreferences.begin();

    EXPECT_DOUBLE_EQ(p1.second,1.0/3.0);

    receiverPreferences.remove_receiver(&s3);

    auto p2 = *receiverPreferences.begin();

    EXPECT_EQ(p2.second,0.5);
}

TEST(ReceiverPreferencesTest, Randomizer){
    Storehouse s1(1);
    Storehouse s2(2);
    Storehouse s3(3);

    ProbabilityGenerator f = fixed_prob_09;
    ReceiverPreferences receiverPreferences(f);

    receiverPreferences.add_receiver(&s1);
    receiverPreferences.add_receiver(&s2);
    receiverPreferences.add_receiver(&s3);

    auto s = receiverPreferences.choose_receiver();

    EXPECT_EQ(s3.get_id(),s->get_id());
}


TEST(RampAndStorehouseTest, All){
    Storehouse s1(1);
    Storehouse s2(2);

    ProbabilityGenerator f = fixed_prob_06;
    ReceiverPreferences receiverPreferences(f);

    receiverPreferences.add_receiver(&s1);
    receiverPreferences.add_receiver(&s2);

    Ramp r1(1,2,receiverPreferences);

    Time i=1;
    while (i<10) {
        r1.deliver_goods(i);
        r1.send_package();
        i++;
    }

    EXPECT_EQ(s2.get_queue_size(),5);
}

TEST(RampAndStorehouseTest, Alll){
    Storehouse s1(1);
    Storehouse s2(2);

    Ramp r1(1,2);

    r1.receiver_preferences_.add_receiver(&s1);
    r1.receiver_preferences_.add_receiver(&s2);


    Time i=1;
    while (i<10) {
        r1.deliver_goods(i);
        r1.send_package();
        i++;
    }

    EXPECT_EQ(s1.get_queue_size(),2);
    EXPECT_EQ(s2.get_queue_size(),3);
}

TEST(WorkerReceiveAndSendTest, RampAndWorkerNormal){
    Storehouse s1(1);

    ProbabilityGenerator f = fixed_prob_06;
    ReceiverPreferences receiverPreferences1(f);
    receiverPreferences1.add_receiver(&s1);


    std::unique_ptr<IPackageQueue> pq1 = std::make_unique<PackageQueue>(PackageQueue(FIFO));
    Worker w1(1,1,std::move(pq1),receiverPreferences1);

    ReceiverPreferences receiverPreferences2(f);
    receiverPreferences2.add_receiver(&w1);
    Ramp r1(1,1,receiverPreferences2);

    Time i=1;
    while (i<=2) {
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

    EXPECT_EQ(s1.get_queue_size(),1);
    EXPECT_EQ(w1.get_queue_size(),0);
    EXPECT_TRUE(w1.get_sending_buffer().has_value());
}

TEST(WorkerReceiveAndSendTest2, RampFaster){
    Storehouse s1(1);

    ProbabilityGenerator f = fixed_prob_06;
    ReceiverPreferences receiverPreferences1(f);
    receiverPreferences1.add_receiver(&s1);


    std::unique_ptr<IPackageQueue> pq1 = std::make_unique<PackageQueue>(PackageQueue(FIFO));
    Worker w1(1,2,std::move(pq1),receiverPreferences1);

    ReceiverPreferences receiverPreferences2(f);
    receiverPreferences2.add_receiver(&w1);
    Ramp r1(1,1,receiverPreferences2);

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

    EXPECT_EQ(s1.get_queue_size(),4);
    EXPECT_EQ(w1.get_queue_size(),5);
    EXPECT_TRUE(w1.get_sending_buffer().has_value());
}

TEST(WorkerReceiveAndSendTest2, WorekerFaster){
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
}

TEST(WorkerReceiveAndSendTest, WorkerSending){
    Storehouse s1(1);
    Storehouse s2(2);

    ProbabilityGenerator f = fixed_prob_06;
    ReceiverPreferences receiverPreferences1(f);
    receiverPreferences1.add_receiver(&s1);
    receiverPreferences1.add_receiver(&s2);


    std::unique_ptr<IPackageQueue> pq1 = std::make_unique<PackageQueue>(PackageQueue(FIFO));
    Worker w1(1,1,std::move(pq1),receiverPreferences1);

    ReceiverPreferences receiverPreferences2(f);
    receiverPreferences2.add_receiver(&w1);
    Ramp r1(1,1,receiverPreferences2);

    Time i=1;
    while (i<=2) {
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

    EXPECT_EQ(s1.get_queue_size(),0);
    EXPECT_EQ(s2.get_queue_size(),1);
    EXPECT_EQ(w1.get_queue_size(),0);
    EXPECT_TRUE(w1.get_sending_buffer().has_value());
}

TEST(PackageSenderTest, BufferClear){
    Storehouse s2(1);

    ProbabilityGenerator f1 = fixed_prob_06;
    ReceiverPreferences receiverPreferences2(f1);
    receiverPreferences2.add_receiver(&s2);


    std::unique_ptr<IPackageQueue> pq2 = std::make_unique<PackageQueue>(PackageQueue(FIFO));
    Worker w1(1,2,std::move(pq2),receiverPreferences2);

    ReceiverPreferences receiverPreferences3(f1);
    receiverPreferences3.add_receiver(&w1);
    Ramp r1(1,2,receiverPreferences3);

    r1.deliver_goods(0);
    r1.send_package();
    EXPECT_EQ(r1.get_sending_buffer(),std::nullopt);
}

TEST(ReceiverPreferencesTest1, RemoveReceiversRescalesProbability1) {
    // Upewnij się, że usunięcie odbiorcy spowoduje przeskalowanie pozostałych prawdopodobieństw.
    ReceiverPreferences rp;

    Storehouse r1(1);
    Storehouse r2(2);

    //MockReceiver r1, r2;
    rp.add_receiver(&r1);
    rp.add_receiver(&r2);

    rp.remove_receiver(&r2);

    ASSERT_EQ(rp.get_preferences().find(&r2), rp.get_preferences().end());

    EXPECT_EQ(rp.get_preferences().at(&r1), 1.0);
}


