#ifndef PHILO_H
#define PHILO_H

#include <Fork.h>
#include <Printer.h>
#include <chrono>
#include <OptionsParser.h>
#include <condition_variable>

class Philo
{
public:
     // Philo(    const int&     own_index,
     //           const Options& options,
     //           const Printer& printer,
     //           const Fork&    left_fork,
     //           const Fork&    right_fork,
     //           const std::shared_ptr<std::condition_variable> fed_up_cv,
     //           const std::shared_ptr<std::mutex> fed_up_cv_mutex );
     Philo(    const int&     own_index,
               const Options& options,
               const Printer& printer,
               const Fork&    left_fork,
               const Fork&    right_fork);

     void Start( const std::chrono::high_resolution_clock::time_point& start_time );
     void Stop();
     bool Philo::IsDead();
     int GetOwnIndex();
     std::pair< std::shared_ptr<std::condition_variable>, std::shared_ptr<std::mutex> >
     GetFedCvMutexPair();

private:
     void Eat();
     void SleepAndThink();
     void Routine();


     int       own_index_;
     int       times_eated_;
     bool      work_;
     bool      fed_up_;
     std::shared_ptr<std::condition_variable> fed_up_cv_;
     std::shared_ptr<std::mutex> fed_up_cv_mutex_;

     Options   options_;
     Printer   printer_;
     Fork      left_fork_;
     Fork      right_fork_;

     std::chrono::high_resolution_clock::time_point start_time_;
     std::chrono::high_resolution_clock::time_point last_meal_;
};

#endif