#include <iomanip>
#include <ios>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

#include "RRScheduler.h"
#include "AScheduler.h"
#include "CPUWorker.h"
#include "GlobalScheduler.h"
#include "Process.h"
#include "SchedulerWorker.h"


void RRScheduler::init()
{
  // std::cout << "RRScheduler init is called\n";
  // std::cout << "num_cpu: " << this->num_cpu;
  // first put a process into a thread so that they execute at the same time??
  // create logical cpus or cpu worker
  this->delay_per_exec = GlobalScheduler::getInstance()->getDelayPerExec();
  this->batch_process_freq = GlobalScheduler::getInstance()->getBatchFreq();
  this->quantum_cycle = GlobalScheduler::getInstance()->getQuantumCycle();

  for (int i = 0; i < num_cpu; i++) {
    // std::cout << "loop is executing\n";
    cpu_workers.emplace_back(CPUWorker());
    cpu_workers[i].setRR();
  }
  // initially move first num_cpu processes in ready queue to cpu_worker threads
  // for (auto& cpu_worker : cpu_workers) {
  //   // assign to process workers then remove in ready queue
  //   if(!this->ready_queue.empty())
  //   {
  //     /*
  //      * Pre-loading in RR causes first num_cpu Processes to finish last when
  //      * they have the same burst time.
  //      */
  //     // cpu_worker.assignProcess(ready_queue.front());
  //     // ready_queue.erase(ready_queue.begin());
  //     // set CPUWorker executing status to true
  //     cpu_worker.setQuantumDec(quantum_cycle);
  //     // cpu_worker.setExecuting(true);
  //   }
  //   else {
  //   std::cout << "ready_queue is empty\n";
  //   }
  //   std::cout << "Core: " << cpu_worker.getCoreID() << " is being assigned Process: " << ready_queue.front()->getProcessName() << "\n";
  // }
  // starts SchedulerWorker which essentially the loop
  IETThread::sleep(1);
}

RRScheduler::RRScheduler(int num_cpu) : AScheduler(ROUND_ROBIN) 
{
  this->num_cpu = num_cpu;
}


void RRScheduler::addProcess(std::shared_ptr<Process> process)
{
  // std::cout << "RRScheduler addProcess called\n";
  if (findProcess(process->getProcessName()) != nullptr)
  {
    std::cout << process->getProcessName() << " already exists";
    return;
  }
  processes[process->getProcessName()] = process;
  this->ready_queue.push_back(process);
}

std::shared_ptr<Process> RRScheduler::findProcess(String process_name)
{
  return processes[process_name];
}


std::unordered_map<String, std::shared_ptr<Process>>& RRScheduler::getProcesses()
{
  return processes;
}

String RRScheduler::returnProcessInfo() const
{
  std::stringstream str_stream, running_stream;
  int cpu_utilized_ctr = 0;
  // Debugging purposes
  // str_stream << "Processes Size: " << processes.size() << "\n";
  // str_stream << "finished_processes size: " << finished_processes.size() << "\n";
  // str_stream << "ready_queue size: " << ready_queue.size() << "\n";
  str_stream << "CPU Utilization: ";
  running_stream << BORDER_H << "\n";
  running_stream << "Running Processes: \n";

  for (auto& cpu : cpu_workers) {
    if (cpu.getCurrentProcess() != nullptr && (cpu.getCurrentProcess()->getCurrState() == Process::RUNNING)) {
      cpu_utilized_ctr += 1;

      running_stream << std::left << std::setfill(' ')
        << std::setw(15) << cpu.getCurrentProcess()->getProcessName()
        << std::setw(30) << ("(" + cpu.getCurrentProcess()->getTimeStartedToStr() + ")")
        << std::setw(15) << ("Core: " + std::to_string(cpu.getCurrentProcess()->getCpuID()))
        // Debugging purposes
        // << std::setw(15) << "QuantumDec: " << cpu.getQuantumDec() << "|| "
        << std::setw(15) << (std::to_string(cpu.getCurrentProcess()->getTotalInstruction() - cpu.getCurrentProcess()->getRemainingInstructions()) 
            + " / " 
            + std::to_string(cpu.getCurrentProcess()->getTotalInstruction()))
        << std::endl;  
    }
  }

  str_stream << (cpu_utilized_ctr * 100 / cpu_workers.size())  << "%" << "\n";
  str_stream << "Cores used: " << cpu_utilized_ctr << "\n";
  str_stream << "Cores available: " << cpu_workers.size() - cpu_utilized_ctr << "\n";
  str_stream << running_stream.str();

  str_stream << "Finished Processes: \n";
  for (auto& curr_process : finished_processes) {
    str_stream << std::left << std::setfill(' ') 
      << std::setw(15) << curr_process->getProcessName()  // Process name column
      << std::setw(30) << ("(" + curr_process->getTimeEndToStr() + ")")  // Time ended column
      << std::setw(15) << ("Core: " + std::to_string(curr_process->getCpuID()))  // Core column
      << std::setw(15) << "Finished" << std::endl;  // Print and go to the next line
  }

  str_stream << BORDER_H << "\n";  // Add the horizontal border at the end
  return str_stream.str();
}

void RRScheduler::startSchedTest()
{
  this->sched_test = true;
  GlobalScheduler::getInstance()->getSchedWorker().update(true);
  GlobalScheduler::getInstance()->getSchedWorker().start();
}

void RRScheduler::stopSchedTest()
{
  this->sched_test = false;
}

// every tick of SchedulerWorker this is called
void RRScheduler::execute()
{
  if ((finished_processes.size() == processes.size()) && ready_queue.empty() && !sched_test)
  {
    GlobalScheduler::getInstance()->getSchedWorker().update(false);
  }

  for (auto& cpu : cpu_workers) {
    // DEBUGGING PURPOSES:
    // std::cout << "ready_queue: \n";
    // for (auto& curr_process : ready_queue) {
    //   std::cout << curr_process->getProcessName() << " ";
    // }
    // std::cout << std::endl;

    // first if condition checks if a cpu worker already has an attached process then checks
    // if it is finished executing the process then cleares the cpu's attached process
    if (cpu.getCurrentProcess() != nullptr) {
      if ((cpu.getCurrentProcess()->getCurrState() == Process::FINISHED)) {
        finished_processes.push_back(cpu.getCurrentProcess());
        cpu.clearProcess();
      } else {
        if (cpu.getQuantumDec() == 0) {
          cpu.getCurrentProcess()->setStateReady();
          ready_queue.push_back(cpu.getCurrentProcess());
          cpu.clearProcess();
        }
      }
    }
    // if statement is better than else since first if statement just frees up the CPU_Worker 
    // this if statement allocates process to free CPU_Worker resulting in every CPU_Worker to have
    // an attached process at all times if ready_queue is not empty.
    if (cpu.getCurrentProcess() == nullptr) {
      if (!ready_queue.empty()) {
        // Assigning of ready_queue to CPUWorkers
        cpu.assignProcess(ready_queue.front());
        cpu.setQuantumDec(this->quantum_cycle);
        ready_queue.erase(ready_queue.begin());
      }
      else {
        continue;
      }
    }
    cpu.start(); 
  }
  IETThread::sleep(delay_per_exec); // delay per execution
}


void RRScheduler::run()
{
  GlobalScheduler::getInstance()->getSchedWorker().update(true);
  GlobalScheduler::getInstance()->getSchedWorker().start();
}
