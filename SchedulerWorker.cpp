#include "SchedulerWorker.h"

#include "GlobalScheduler.h"

void SchedulerWorker::run()
{
  GlobalScheduler::getInstance()->tick();
}

void SchedulerWorker::update(bool running)
{
  this->running = running;
}

