#include <Printer.h>

Printer::Printer()
{
     print_mutex_ = std::make_shared<std::mutex>();
}

void Printer::print( const int& philo_num, const int& time, const std::string& message )
{
     std::lock_guard<std::mutex> lk( *print_mutex_ );
     std::cout << message << std::endl;
}