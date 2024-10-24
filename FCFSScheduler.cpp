#include "FCFSScheduler.h"
#include "CPUWorker.h"
#include "GlobalScheduler.h"
#include "Process.h"
#include "SchedulerWorker.h"
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>

void FCFSScheduler::init()
{
  // std::cout << "FCFSScheduler init is called\n";
  // std::cout << "num_cpu: " << this->num_cpu;
  // first put a process into a thread so that they execute at the same time??
  // create logical cpus or cpu worker
  this->delay_per_exec = GlobalScheduler::getInstance()->getDelayPerExec();

  for (int i = 0; i < num_cpu; i++) {
    // std::cout << "loop is executing\n";
    cpu_workers.emplace_back(CPUWorker());
    // std::cout << "Core: " <<  cpu_worker.uid << ": is working" << "\n";
  }
  // initially move first num_cpu processes in ready queue to cpu_worker threads
  for (auto& cpu_worker : cpu_workers) {
    // assign to process workers then remove in the queue
    if(this->ready_queue.empty())
    {
      std::cout << "ready_queue is empty\n";
    }
    std::cout << "Core: " << cpu_worker.getCoreID() << " is being assigned Process: " << ready_queue.front()->getProcessName() << "\n";
    cpu_worker.assignProcess(ready_queue.front());
    ready_queue.erase(ready_queue.begin());
    cpu_worker.setExecuting(true);
  }
  // starts SchedulerWorker which essentially the loop
}

FCFSScheduler::FCFSScheduler(int num_cpu) : AScheduler(FCFS) 
{
  this->num_cpu = num_cpu;
}


void FCFSScheduler::addProcess(std::shared_ptr<Process> process)
{
  // std::cout << "FCFSScheduler addProcess called\n";
  if (findProcess(process->getProcessName()) != nullptr)
  {
    std::cout << process->getProcessName() << " already exists";
    return;
  }
  processes[process->getProcessName()] = process;
  this->ready_queue.push_back(process);
}

std::shared_ptr<Process> FCFSScheduler::findProcess(String process_name)
{
  return processes[process_name];
}


std::unordered_map<String, std::shared_ptr<Process>>& FCFSScheduler::getProcesses()
{
  return processes;
}

String FCFSScheduler::returnProcessInfo() const
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
      cpu_utilized_ctr = cpu_utilized_ctr + 1;
      running_stream << cpu.getCurrentProcess()->getProcessName() << "\t" << "(" << cpu.getCurrentProcess()->getTimeStartedToStr() << ")" << "\t" << "Core: " << cpu.getCurrentProcess()->getCpuID() << "\t" << cpu.getCurrentProcess()->getTotalInstruction() - cpu.getCurrentProcess()->getRemainingInstructions() << " / " << cpu.getCurrentProcess()->getTotalInstruction() << "\n";
    }
  }
  str_stream << (cpu_utilized_ctr * 100 / cpu_workers.size())  << "%" << "\n";
  str_stream << "Cores used: " << cpu_utilized_ctr << "\n";
  str_stream << "Cores available: " << cpu_workers.size() - cpu_utilized_ctr << "\n";
  str_stream << running_stream.str();

  str_stream << "Finished Processes: \n";
  for (auto& curr_process : finished_processes) {
    str_stream << curr_process->getProcessName() << "\t" << "(" << curr_process->getTimeEndToStr() << ")" << "\t" << "Core: " << curr_process->getCpuID() << "\t" << "Finished" << "\n";
  }
  str_stream << BORDER_H << "\n";

  return str_stream.str();
}

void FCFSScheduler::execute()
{
  
  // stops SchedulerWorker while loop
  if((finished_processes.size() == processes.size()) && ready_queue.empty())
  {
    // std::cout << "Stopping SchedulerWorker\n";
    GlobalScheduler::getInstance()->getSchedWorker().update(false);
  }

  for (auto& cpu : cpu_workers) {
    {
      if (cpu.getCurrentProcess() != nullptr) {
        if ((cpu.getCurrentProcess()->getCurrState() == Process::FINISHED) && !cpu.getExecuting()) {
          finished_processes.push_back(cpu.getCurrentProcess());
          cpu.clearProcess();
        }
      }
      if (!cpu.getExecuting() && !ready_queue.empty())
      {
        // Assigning of ready_queue to CPUWorkers
        cpu.assignProcess(ready_queue.front());
        ready_queue.erase(ready_queue.begin());
        cpu.setExecuting(true);
      }
    }
    cpu.start();
  }

  IETThread::sleep(delay_per_exec); // delay per execution
}


void FCFSScheduler::run()
{
  GlobalScheduler::getInstance()->getSchedWorker().update(true);
  GlobalScheduler::getInstance()->getSchedWorker().start();
  // this->sched_worker().update(true);
  // this->sched_worker().start();
}
