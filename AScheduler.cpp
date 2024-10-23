#include "AScheduler.h"
#include <iostream>

AScheduler::AScheduler(SchedulingAlgorithm sched_algo)
{

}

void AScheduler::addProcess(std::shared_ptr<Process> new_process)
{
  if (processes[new_process->getProcessName()] != nullptr)
  {
    std::cout << "Process already exists";
    return;
  }

  processes[new_process->getProcessName()] = new_process;
}

std::shared_ptr<Process> AScheduler::findProcess(String process_name)
{
  // would return nullptr if it does not exits
  return processes[process_name];
}

void AScheduler::run()
{

}
