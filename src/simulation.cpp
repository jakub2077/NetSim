#include "simulation.hpp"

void simulate(Factory& f, TimeOffset d, std::function<void (Factory&, Time)> rf) {
    Time t=1;
    while (t<=d) {
        f.do_deliveries(t);
        f.do_package_passing();
        f.do_work(t);
        rf(f,t);
        t++;
    }
}