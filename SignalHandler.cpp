#include <SignalHandler.h>

#include <csignal>
#include <cstring>

namespace SignalHandler
{

namespace
{
     std::vector<std::pair<int, std::function<void()>>> g_SignalCallbackVector;
     std::mutex eventMutex;
     std::condition_variable eventCv; //signal end
     volatile sig_atomic_t do_shutdown = 0;
     std::atomic<bool> shutdown_requested = false;
}

     void SignalHandler( int signum )
     {
          for ( const auto& sig : g_SignalCallbackVector )
          {
               if ( sig.first == signum )
               {
                    sig.second();
               }
          }
     }

    void InstallSignalsCallback( const std::list<int>& signalList, const std::function<void()>& signalCallback )
    {
          int rc = 0;
          sigset_t   set;
          sigemptyset( &set );
          for (const auto sig : signalList)
          {
               rc = sigaddset( &set, sig );
               if ( rc == -1 )
               {
                    throw std::runtime_error("Could not init signal handler set");
               }
          }

          struct sigaction act;
          memset( &act, 0, sizeof( act ) );
          act.sa_handler = SignalHandler::SignalHandler;
          act.sa_mask = set;

          for ( const auto sig : signalList )
          {
               rc = sigaction( sig, &act, NULL );
               if ( rc == -1 )
               {
                    throw std::runtime_error( "Could not bind signal handler set" );
               }
          }

          for ( const auto sig : signalList )
          {
               SignalHandler::g_SignalCallbackVector.push_back( std::make_pair( sig, signalCallback ) );
          }
     }

     void EmitSignal()
     {
          std::lock_guard<std::mutex> lk( eventMutex );
          do_shutdown = 1;
          shutdown_requested = true;
          eventCv.notify_one();
     }


     void WaitSignal()
     {
          std::unique_lock<std::mutex> unilock( eventMutex );
          eventCv.wait( unilock, []()
               {
                    return do_shutdown && shutdown_requested.load();
               });
     }

} // namespace SignalHandler
