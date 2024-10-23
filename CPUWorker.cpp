#include "CPUWorker.h"

void CPUWorker::assignProcess(std::shared_ptr<Process> process)
{
  this->process = process;
}

void CPUWorker::run()
{
  if (process->hasFinished())
  {
    this->executing = false;
    return;
  }
  process->executeInstruction();
}
