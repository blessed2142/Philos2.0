#ifndef PHILO_H
#define PHILO_H

#include <Fork.h>
#include <Printer.h>
#include <chrono>
#include <OptionsParser.h>

class Philo
{
public:
     Philo(    const int&     own_index,
               const Options& options,
               const Printer& printer,
               const Fork&    left_fork,
               const Fork&    right_fork_ );

private:
     int       own_index_;
     int       times_eated_;

     Options   options_;
     Printer   printer_;
     Fork      left_fork_;
     Fork      right_fork_;

     std::chrono::high_resolution_clock::time_point start_time_;
     std::chrono::high_resolution_clock::time_point last_meal_;
};

#endif