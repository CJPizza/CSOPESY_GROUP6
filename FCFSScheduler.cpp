#include "FCFSScheduler.h"
#include "CPUWorker.h"
#include "GlobalScheduler.h"
#include "Process.h"
#include "SchedulerWorker.h"
#include <iostream>
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
    std::cout << "Core: " << cpu_worker.uid << " is being assigned Process: " << ready_queue.front()->getProcessName() << "\n";
    cpu_worker.assignProcess(ready_queue.front());
    ready_queue.erase(ready_queue.begin());
    cpu_worker.executing = true;
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
  std::stringstream str_stream;
  str_stream << "Processes Size: " << processes.size() << "\n";
  str_stream << "finished_processes size: " << finished_processes.size() << "\n";
  str_stream << "Running Processes: \n";
  for (auto& cpu : cpu_workers) {
    if (cpu.process->getCurrState() == Process::RUNNING) {
      str_stream << cpu.process->getProcessName() << "\t" << "(" << cpu.process->getTimeStartToStr() << ")" << "\t" << "Core: " << cpu.process->getCpuID() << "\t" << cpu.process->getTotalInstruction() - cpu.process->getRemainingInstructions() << " / " << cpu.process->getTotalInstruction() << "\n";
    }
  }

  str_stream << "Finished Processes: \n";
  for (auto& curr_process : finished_processes) {
      str_stream << curr_process->getProcessName() << "\t" << "(" << curr_process->getTimeStartToStr() << ")" << "\t" << "Core: " << curr_process->getCpuID() << "\t" << "Finished" << "\n";
  }

  // for (const std::pair<const String, std::shared_ptr<Process>>& n : this->processes){
  //     str_stream << n.first << ": "  << "Core: " << n.second->getCpuID() << "\t" << n.second->getRemainingInstructions() << "/" << n.second->getTotalInstruction() << "\n";
  // }
  return str_stream.str();
}

void FCFSScheduler::execute()
{
  // std::cout << "FCFSScheduler is executing";
  if((finished_processes.size() == processes.size()))
  {
    // stops looping even if one of the cpus is executing
    // GlobalScheduler::getInstance()->getSchedWorker().update(false);
  }

  for (auto& cpu : cpu_workers) {
    if (!cpu.executing && !ready_queue.empty())
    {
      // cpu.assignProcess(ready_queue.front());
      if (cpu.process->getCurrState() == Process::FINISHED)
      {
        finished_processes.push_back(cpu.process);
      }
      cpu.process = ready_queue.front();
      ready_queue.erase(ready_queue.begin());
      // cpu.executing = true;
    }
    // std::cout << "Core: " <<  cpu.uid << ": is working" << "\n";
      cpu.start();
  }

  IETThread::sleep(delay_per_exec); // delay per execution
  // for (auto& cpu : cpu_workers) {
  //   // stop from running
  // }
  // add delay per exec here
  // std::cout << "FCFSScheduler is almost finished" << "\n";
}


void FCFSScheduler::run()
{
  GlobalScheduler::getInstance()->getSchedWorker().update(true);
  GlobalScheduler::getInstance()->getSchedWorker().start();
  // this->sched_worker().update(true);
  // this->sched_worker().start();
}
