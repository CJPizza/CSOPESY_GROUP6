#include "SchedulerWorker.h"
#include "GlobalScheduler.h"

void SchedulerWorker::run()
{
  while(this->running)
  {
    GlobalScheduler::getInstance()->tick();
  }
}

void SchedulerWorker::update(bool running)
{
  this->running = running;
}

