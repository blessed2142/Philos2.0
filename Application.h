#ifndef APPLICATION_H
#define APPLICATION_H

#include <condition_variable>
#include <mutex>
#include <vector>
#include <list>

class Application
{
public:
     Application();

     virtual void Work();
     virtual void Run();
     virtual void Exec();
protected:
     std::condition_variable  cv_exit;
     std::mutex               cv_exit_mutex;
};


#endif