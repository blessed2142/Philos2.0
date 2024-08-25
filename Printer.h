#ifndef PRINTER_H
#define PRINTER_H

#include <mutex>
#include <memory>
#include <iostream>

class Printer
{
public:
     Printer()
     {
          print_mutex_ = std::make_shared<std::mutex>();
          should_print_ = std::make_shared<bool>( true );
     }

     /* Оставлю на случай использования класса как shared_ptr */
     // ~Printer()
     // {
     //      if (  print_mutex_->try_lock() )
     //      {
     //           print_mutex_->unlock();
     //      }
     // }

     void Print( const int& philo_num, const int& time, const std::string& message )
     {
          if ( !( *should_print_ ) )
          {
               return ;
          }
          std::lock_guard<std::mutex> lk( *print_mutex_ );
          std::cout << message << std::endl;
     }

     void Stop()
     {
          *should_print_ = false;
     }

private:
     std::shared_ptr<std::mutex>   print_mutex_;
     std::shared_ptr<bool>         should_print_;
};

#endif