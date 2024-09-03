#include <Waiter.h>

Waiter::Waiter( const Options& options, const Printer& printer ) :
options_( options ),
printer_( printer )
{
     for ( int i = 0; i < options_.philosophers; ++i )
     {
          forks_.emplace_back( i + 1 );
     }
}

void Waiter::CreatePhilos()
{
     int philo_index = 1;
     for ( auto it = forks_.begin(); it != forks_.end(); ++it )
     {
          philos_.emplace_back( philo_index++, options_, printer_, *it, 
          std::next( it ) != forks_.end() ? *( std::next( it ) ) : *( forks_.begin() ) );
     }
}

void Waiter::BeginSumulation()
{
     auto sim_start_time_ = std::chrono::high_resolution_clock::now();
     for ( auto& philo : philos_ )
     {
          philo.Start( sim_start_time_ );
     }
}

void Waiter::ObserveTable( std::vector<Philo>& philos, const Printer& printer,
     const std::chrono::high_resolution_clock::time_point& sim_start_time )
{
     auto stopAllPhilos = [&philos]()
     {
          for ( auto& philo : philos )
          {
               philo.Stop();
          }
     };

     for ( int i = 0; i < philos_.size() ; )
     {
          if ( philos[i].IsDead() )
          {
               printer.Print( philos_[i].GetOwnIndex(), sim_start_time, "is dead" );
               printer.Stop();
               // cv for end notify;
          }
     }
}

void Waiter::FeedChecker()
{

}
