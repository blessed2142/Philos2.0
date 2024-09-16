#ifndef GCAPPLICATION_HPP
#define GCAPPLICATION_HPP

#include <condition_variable>
#include <mutex>
#include <future>

namespace gc
{


class GcApplication
{
private:
  GcApplication(const GcApplication& orig) :
    m_exit_code(orig.m_exit_code),
    m_execruning(orig.m_execruning)
  {

  };
public:
  /*
  * @param settings_path
  */
  GcApplication() :
    m_exit_code(-1),
    m_execruning(false)
  {

  };
  /*
   */
  ~GcApplication() {};
  /*
   * @param signum
   * @comment вызывается по системному прерыванию - завершает вечный цикл
   * можно использовать при завершении программы, если требуеться вернуть код завершения программы
   * слот для служебных целей. (прерывание по сигналу)
   */
  void endProgram(int signum = 0)
  {
    if(m_execruning)
    {
      m_exit_code = signum;
      m_cv_gc_app_exit.notify_one();
    }
    else
      std::exit(signum);
  };
  /* @return код завершения программы
   * метод для переопределения в наследуемом классе
   */
  virtual int run()
  {
    return m_exit_code;
  };

  virtual void work() = 0;
  /*
  * @return код завершения
  * вечный цикл - выход из приложения
  */
  int exec()
  {
    m_execruning = true;
    //ждет пока exit код поменяет свое значение, на значение отличное от -1
    std::unique_lock<std::mutex> unilock(gcapp_mutex);
    m_cv_gc_app_exit.wait(unilock, [this]()
    {
      work();
      return m_exit_code != -1;
    });
    return m_exit_code;
  };
  /*
   * @param a_exitcode
   * Прерывает цикл exec, завершая программу указанным кодом
   */
  void exit(int a_exitcode)
  {
    if(m_execruning)
    {
      m_exit_code = a_exitcode;
      m_cv_gc_app_exit.notify_one();
    }
    else
      std::exit(a_exitcode);
  };

protected:
  //набор для остановки программы
  std::mutex gcapp_mutex;
  std::condition_variable m_cv_gc_app_exit; //signal end
  int m_exit_code;
  bool m_execruning;
};

}

#endif // GCAPPLICATION_HPP