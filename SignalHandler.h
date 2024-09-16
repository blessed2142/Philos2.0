#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

#include <mutex>
#include <condition_variable>
#include <atomic>
#include <list>
#include <functional>

namespace SignalHandler
{
    /// @brief Метод вызовет callback в порядке добавления через InstallSignalsCallback, если signum соотвествует обработчку.
    /// Вызов всех callback не гарантирован и ограничен кодом обработчиков.
    /// @param signum 
    void SignalHandler(int signum);

    /// @brief Устанавливет список сигналов и их обработчиков
    /// @param signalList 
    /// @param signalCallback 
    void InstallSignalsCallback(const std::list<int>& signalList, const std::function<void()>& signalCallback);

    /// @brief Снимает с ожидания WaitSignal
    void EmitSignal();

    /// @brief Ожидает согнала (EmitSignal или EmergencyStop)
    void WaitSignal();
} // namespace SignalHandler


#endif