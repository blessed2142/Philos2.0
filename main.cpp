#include "OptionsParser.h"
#include <iostream>
#include <thread>
#include <ratio>
#include <chrono>
#include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/time.h>
#include <mutex>

class A
{
public:
     A( const int& id, const std::shared_ptr<std::mutex>& fork ) : id_( id ), fork_( fork )
     {
          // std::mutex muta = fork_.get();
          std::cout << "Id: " << id_ << "address: " <<  fork_.get() << std::endl;
     }

     void bringTheAction()
     {
          for ( ; ; )
          {
               std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
               std::lock_guard<std::mutex> lk( *fork_ );
               std::cout << "Id: " << id_ << " took ownership" << std::endl;
               std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
          }
     }

private:
     std::shared_ptr<std::mutex>   fork_;
     int                           id_;
};

int main( int argc, char** argv )
{
     std::shared_ptr<std::mutex> muta = std::make_shared<std::mutex>();
     A a1( 1, muta );
     A a2( 2, muta );

     std::thread t1( &A::bringTheAction, &a1 );
     std::thread t2( &A::bringTheAction, &a2 );

     t1.join();
     t2.join();




     // OptionParser opt_parser( argc, argv );
     // try
     // {
     //      opt_parser.init();
     // }
     // catch( const std::exception& e )
     // {
     //      std::cout << "Exception occurred during arg parse: " << e.what() << std::endl;
     //      return 1;
     // }

     return 0;
}

// class A
// {
// public:
//      A( int& i ) : i_( i )
//      {

//      }
//      void doWork( bool& flag )
//      {
//           i_ = 1488;
//           flag = true;
//      }
// private:
//      int& i_;
// };

// int main( int argc, char** argv )
// {
//      int i = 0;
//      bool flag = false;
//      A a( i );
//      std::thread t( &A::doWork, &a, std::ref( flag ) );
//      t.join();

//      std::cout << "Flag: " << std::boolalpha << flag << " int i: " << i << std::endl;
//      return 0;
// }

// int main( int argc, char** argv )
// {
//      // auto start = std::chrono::high_resolution_clock::now();

//      // for ( int i = 1; i < 100; ++i)
//      // {
//      //      auto now = std::chrono::high_resolution_clock::now();

//      //      auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>( now - start ).count();

//      //      std::cout << int_ms << " ms" << std::endl;
//      //      // now.
//      //      std::this_thread::sleep_until( std::chrono::round<std::chrono::milliseconds>( now + std::chrono::milliseconds( 200 ) )  );
//      //      // ft_usleep( 200 );
//      //      // superSleep( start, std::chrono::milliseconds( 200 * i ) );
//      //      // usleep( 200000 );
//      // }

//      int i = 5;

//      A a( i );
//      std::thread t( &A::DoSum, &a );
//      t.join();

//      std::cout << i << std::endl;

//      std::cout << "qq" << std::endl;

//      return 0;
// }

