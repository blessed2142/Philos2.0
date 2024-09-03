#include <Philo.h>
#include <thread>

Philo::Philo(  const int&     own_index,
               const Options& options,
               const Printer& printer,
               const Fork&    left_fork,
               const Fork&    right_fork) :
own_index_( own_index ),
times_eated_( 0 ),
work_( true ),
fed_up_( false ),
fed_up_cv_( std::make_shared<std::condition_variable>() ),
fed_up_cv_mutex_( std::make_shared<std::mutex>() ),
options_( options ),
printer_( printer ),
left_fork_( left_fork ),
right_fork_( right_fork )
{
}

void Philo::Start( const std::chrono::high_resolution_clock::time_point& start_time )
{
     start_time_ = last_meal_ = start_time;
     std::thread t( &Philo::Routine, this );
     t.join();
}

void Philo::Stop()
{
     work_ = false;
}

void Philo::Eat()
{
     if ( !work_ )
     {
          return ;
     }

     auto routine = [&]()
     {
          printer_.Print( own_index_, start_time_, "has taken a fork" );
          printer_.Print( own_index_, start_time_, "is eating" );
          last_meal_ = std::chrono::high_resolution_clock::now();
          std::this_thread::sleep_until( std::chrono::round<std::chrono::milliseconds>(
               std::chrono::high_resolution_clock::now() + std::chrono::milliseconds( options_.time_to_eat ) )  );
          ++times_eated_;
          if ( times_eated_ == options_.must_eat )
          {
               Stop();
               {
                    std::unique_lock lock( *fed_up_cv_mutex_ );
                    fed_up_cv_->notify_one();
                    // fed_up_ = true;
               }
          }
     };

     if ( own_index_ % 2 == 1 )
     {
          right_fork_.Take();
          left_fork_.Take();
          routine();
          left_fork_.Release();
          right_fork_.Release();
     }
     else
     {
          left_fork_.Take();
          right_fork_.Take();
          routine();
          left_fork_.Release();
          right_fork_.Release();
     }
}

void Philo::SleepAndThink()
{
     if ( !work_ )
     {
          return ;
     }

     printer_.Print( own_index_, start_time_,  "is sleeping" );
     std::this_thread::sleep_until( std::chrono::round<std::chrono::milliseconds>(
          std::chrono::high_resolution_clock::now() + std::chrono::milliseconds( options_.time_to_sleep ) )  );
     printer_.Print( own_index_, start_time_,  "is thinking" );
}

void Philo::Routine()
{
     for ( ; work_ ; )
     {
          Eat();
          SleepAndThink();
     }
}

bool Philo::IsDead()
{
     return last_meal_ + std::chrono::milliseconds( options_.time_to_die ) < 
     std::chrono::high_resolution_clock::now();
}
