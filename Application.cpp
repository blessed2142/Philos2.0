#include <Application.h>
#include <csignal>
#include <SignalHandler.h>

Application::Application()
{
     std::list<int> signals { SIGINT };

     auto callback = []()
     {
          SignalHandler::EmitSignal();
     };
     SignalHandler::InstallSignalsCallback( signals, callback );
}


void Application::Work()
{
     while ( true );
}

void Application::Run()
{
     
}

void Application::Exec()
{
     SignalHandler::WaitSignal();
     exit( 0 );
}
