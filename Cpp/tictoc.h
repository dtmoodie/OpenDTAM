#ifndef TIC_TOC
#define TIC_TOC

#include <iostream>
#include <boost/date_time.hpp>

// Just a static variable that will be visible only within this file
static boost::posix_time::ptime start_time;
//static struct timespec start_time;
static void tic() {
//clock_gettime(CLOCK_MONOTONIC, &start_time);
    start_time = boost::posix_time::microsec_clock::universal_time();

}

static double toc() {
  boost::posix_time::ptime tv2 = boost::posix_time::microsec_clock::universal_time();

  boost::posix_time::time_duration delta = (tv2 - start_time);

  double sec = delta.total_seconds();
  double nsec = delta.total_nanoseconds();

  double elapsed= (sec + 1.0e-9 * nsec);

    time_t end_time=time(0);
    std::cout<<"Elapsed time is "<<elapsed<<" seconds."<<std::endl;
    return elapsed;
}
static double tocq() {
    boost::posix_time::ptime tv2 = boost::posix_time::microsec_clock::universal_time();

    boost::posix_time::time_duration delta = (tv2 - start_time);

    double sec = delta.total_seconds();
    double nsec = delta.total_nanoseconds();
    
    double elapsed= (sec + 1.0e-9 * nsec);
    
    time_t end_time=time(0);
    return elapsed;
}

#endif //TIC_TOC
