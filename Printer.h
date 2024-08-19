#ifndef PRINTER_H
#define PRINTER_H

#include <mutex>
#include <memory>
#include <iostream>

class Printer
{
public:
     Printer();
     void print( const int& philo_num, const int& time, const std::string& message );

private:
     std::shared_ptr<std::mutex> print_mutex_;
};

#endif