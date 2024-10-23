#pragma once
#include "IETThread.h"

/* From my understanding this class loops the execution
 * which allows for synchronized execution of processes
 */

class SchedulerWorker : public IETThread {
public:
  SchedulerWorker() = default;
  ~SchedulerWorker() = default;

  void update(bool running); // update running state
  void run() override;

private:
  bool running = false;
};
