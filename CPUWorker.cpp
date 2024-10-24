#include "CPUWorker.h"
#include <iostream>

CPUWorker::CPUWorker() : uid(new_id++) {}

  // mtx might not be needed and passing finished_processes
void CPUWorker::assignProcess(std::shared_ptr<Process> process) 
{
  this->process = process;
  this->process->setCpuID(this->uid);
  this->process->setRunning();
}

std::shared_ptr<Process> CPUWorker::getCurrentProcess() const
{
  return this->process;
}

void CPUWorker::setExecuting(bool executing)
{
  this->executing = executing;
}

bool CPUWorker::getExecuting() const
{
  return this->executing;
}

int CPUWorker::getCoreID() const
{
  return this->uid;
}

void CPUWorker::clearProcess()
{
  this->process = nullptr;
}

void CPUWorker::run()
{
  if (executing && process != nullptr) {
    if (this->process->hasFinished())
    {
      // TESTING Purposes
      // std::cout << "Process: " << process->getProcessName() << " has finished\n";
      this->process->setFinished();
      // this->finished_processes.push_back(this->process);
      this->executing = false;
      return;
    }
    process->executeInstruction();
    IETThread::sleep(1);
  }
  // std::cout << "executing...";
}
