#include "CPUWorker.h"
#include <iostream>

CPUWorker::CPUWorker() : uid(new_id++) {}

// assings process to this CPUWorker then sets the process state 
// to running
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

void CPUWorker::setQuantumDec(int quant_rem)
{
  this->quant_cycle_rem = quant_rem;
}

int CPUWorker::getQuantumDec() const
{
  return this->quant_cycle_rem;
}

void CPUWorker::setRR()
{
  this->isRR = true;
}

void CPUWorker::run()
{
  if (process != nullptr) {
    if (this->process->hasFinished())
    {
      // TESTING Purposes
      // std::cout << "Process: " << process->getProcessName() << " has finished\n";
      this->process->setFinished();
      // this->executing = false;
    }
    else {
      if (!isRR)
      {
        process->executeInstruction();
      }
      else if (isRR && quant_cycle_rem > 0) {
        // std::cout << "Decrementing Quant: " << quant_cycle_rem << "\n";
        quant_cycle_rem--;
        process->executeInstruction();
      }
    }
  }
  // IETThread::sleep(1);
  // std::cout << "executing...";
}
