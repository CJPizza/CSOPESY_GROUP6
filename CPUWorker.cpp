#include "CPUWorker.h"
#include "GlobalScheduler.h"
#include <iostream>
#include <mutex>

CPUWorker::CPUWorker() : uid(new_id++) {}

// assings process to this CPUWorker then sets the process state 
// to running
void CPUWorker::assignProcess(std::shared_ptr<Process> process) 
{
  this->process = process;
  this->process->setCpuID(this->uid);
  this->process->setRunning();
  this->executing = true;
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

void CPUWorker::setQuantumDec()
{
  this->quant_cycle_rem = GlobalScheduler::getInstance()->getQuantumCycle();
}

int CPUWorker::getQuantumDec() const
{
  return this->quant_cycle_rem;
}

bool CPUWorker::quantumCycleDone()
{
  return this->quant_cycle_rem == 0;
}

void CPUWorker::setRR()
{
  this->isRR = true;
}

void CPUWorker::run()
{
  // while(executing)
  // {
  //   if (process->hasFinished()) {
  //     executing = false;
  //     // std::cout << process->getProcessName() << " has finished\n";
  //   }
  //   else {
  //     process->executeInstruction();
  //     IETThread::sleep(GlobalScheduler::getInstance()->getDelayPerExec());
  //   }
  // }
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
      else if (isRR && !quantumCycleDone()) {
        // std::cout << "Decrementing Quant: " << quant_cycle_rem << "\n";
        quant_cycle_rem--;
        process->executeInstruction();
      }
    }
  }
  // else {
  //   return;
  // }
  // IETThread::sleep(1);
}
