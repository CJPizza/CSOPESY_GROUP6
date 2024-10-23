#include "FCFSScheduler.h"
#include "CPUWorker.h"
#include "GlobalScheduler.h"
#include "SchedulerWorker.h"

void FCFSScheduler::init()
{
  // first put a process into a thread so that they execute at the same time??
  // create logical cpus or cpu worker
  for (int i = 0; i < num_cpu; i++) {
    cpu_workers.emplace_back(CPUWorker());
  }
  // initially move first num_cpu processes in ready queue to cpu_worker threads
  for (auto& cpu_worker : cpu_workers) {
    // assign to process workers then remove in the queue
    cpu_worker.assignProcess(process_queues.front());
    process_queues.erase(process_queues.begin());
  }

  // starts SchedulerWorker which essentially the loop
}

FCFSScheduler::FCFSScheduler(int num_cpu) : AScheduler(FCFS) 
{
  this->num_cpu = num_cpu;
}


void FCFSScheduler::addProcess(std::shared_ptr<Process> process)
{
  if (GlobalScheduler::getInstance()->findProcess(process->getProcessName()) != nullptr)
  {

    this->processes_order.push_back(process->getProcessName());
  }
}

void FCFSScheduler::execute()
{
  if (process_queues.empty())
  {
    // stops loop mechanism of SchedWorker
    GlobalScheduler::getInstance()->getSchedWorker().update(false);
    return;
  }
  for (auto& cpu : cpu_workers) {
    if (!cpu.executing)
    {
      cpu.assignProcess(process_queues.front());
      process_queues.erase(process_queues.begin());
    }
  }
}


void FCFSScheduler::run()
{
  GlobalScheduler::getInstance()->getSchedWorker().update(true);
  GlobalScheduler::getInstance()->getSchedWorker().start();
}
