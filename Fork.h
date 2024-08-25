#ifndef FORK_H
#define FORK_H

#include <memory>
#include <mutex>


class Fork
{
public:
     Fork( const int& index ) : index_( index )
     {
          mutex_ = std::make_shared<std::mutex>();
     }

     /* Оставим на случай если буду использовать Fork обернутую в shared_ptr */
     // ~Fork()
     // {
     //      if ( mutex_->try_lock() )
     //      {
     //           mutex_->unlock();
     //      }
     // }

     /* В принципе можно сделать методы lock/unlock для lock_guard */
     void Take()
     {
          mutex_->lock();
     }

     void Release()
     {
          mutex_->unlock();
     }

private:
     const int                     index_;
     std::shared_ptr<std::mutex>   mutex_;
};


#endif