#include "CPUWorker.h"

CPUWorker::CPUWorker() : uid(new_id++) {}

  // mtx might not be needed and passing finished_processes
void CPUWorker::assignProcess(std::shared_ptr<Process> process) 
{
  this->process = process;
  this->process->setCpuID(this->uid);
  this->process->setRunning();
  // std::cout << "CPU is assigned Process: " << this->process->getProcessName() << "\n";
}

std::shared_ptr<Process> CPUWorker::getCurrentProcess() const
{
  return this->process;
}

void CPUWorker::setExecuting(bool executing)
{
  this->executing = executing;
}

int CPUWorker::getCoreID() const
{
  return this->uid;
}

void CPUWorker::run()
{
  // std::cout << "CPU is running now\n";
  this->executing = true;
  if (this->process->hasFinished())
  {
    // std::cout << "Process has finished\n";
    // this->finished_processes.push_back(this->process);
    this->process->setFinished();
    this->executing = false;
    return;
  }
  // std::cout << "executing...";
  process->executeInstruction();
  IETThread::sleep(5);
}
