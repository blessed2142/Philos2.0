#include "OptionsParser.h"
#include <iostream>
#include <thread>
#include <ratio>
#include <chrono>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <atomic>
#include <csignal>

class Printer
{
public:
     Printer()
     {
          print_mutex_ = std::make_shared<std::mutex>();
     }

     void print( const std::string& message )
     {
          std::lock_guard<std::mutex> lk( *print_mutex_ );
          std::cout << print_mutex_.get() << " address " << print_mutex_.use_count()
          << " use_count " << "| Message: " << message << std::endl;
          std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
     }

private:
     std::shared_ptr<std::mutex> print_mutex_;
};

class A
{
public:
     A()
     {
          struct sigaction action;
          action.sa_handler = A::signal_handler;
          sigemptyset(&action.sa_mask);
          action.sa_flags = 0;
          sigaction(SIGINT, &action, NULL);
     }

     void Worker()
     {
          while( !do_shutdown_ && !shutdown_requested_.load() )
          {
            std::cout << "doing work...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
          }
     }

     static volatile sig_atomic_t do_shutdown_;
     static std::atomic<bool> shutdown_requested_;
private:
     static void signal_handler(int)
     {
          do_shutdown_ = 1;
          shutdown_requested_ = true;

          const char str[] = "received signal\n";
          // ok, write is signal-safe
          write(STDERR_FILENO, str, sizeof(str) - 1);
     }
};

volatile sig_atomic_t A::do_shutdown_ = 0;
std::atomic<bool> A::shutdown_requested_ = false;


int main( int argc, char** argv )
{
     A a;
     a.Worker();

     std::cout << "Getting down" << std::endl;

     return 0;
}