#include "IETThread.h"

class SchedulerWorker : public IETThread {
public:
  SchedulerWorker();
  ~SchedulerWorker();

  void update(bool running); // update running state
  void run();

private:
  bool running = false;

};
