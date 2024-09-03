#ifndef WAITER_H
#define WAITER_H

#include <OptionsParser.h>
#include <vector>
#include <Philo.h>
#include <thread>
#include <deque>
#include <condition_variable>
#include <Fork.h>
#include <Printer.h>

class Waiter
{
public:
     Waiter( const Options&, const Printer& );

     void CreatePhilos();
     void BeginSumulation();
     void ObserveTable( std::vector<Philo>& philos, const Printer& printer,
     const std::chrono::high_resolution_clock::time_point& sim_start_time );
     void FeedChecker();
private:
     Options options_;
     std::vector<Fork> forks_;
     std::vector<Philo> philos_;
     Printer printer_;
     std::chrono::high_resolution_clock::time_point sim_start_time_;

     Waiter( const Waiter&);
     Waiter &operator=( const Waiter& );


};

#endif