#include "FCFSScheduler.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <mutex>
#include <sstream>
#include <string>

void FCFSScheduler::addProcess(const Process& process, int core)
{
  if (core >= 0 && core <= this->num_cores)
  {
    process_queues[core].push_back(process);
  }
  else
  {
    std::cerr << "Invalid core specifed for process addition.\n";
  }
}

// Not needed in FCFS since this function sorts the vector such that
// the process wit the most instructions will be executed first
void FCFSScheduler::sortProcessQueues()
{
  for (auto& queue : this->process_queues)
  {
    std::sort(queue.begin(), queue.end(), [](const Process& a, const Process& b) {
        return a.getRemainingInstructions() > b.getRemainingInstructions();
        });
  }
}

/* TODO: Change implementation such that we put into a vector all the cores which keeps track if they
 * are executing a process we then change it into a FREE state look into doc neil's implementation
 *
 */

// void FCFSScheduler::runScheduler()
// {
//     // std::cout << "Numcores " << this->num_cores;
// 	// while (!this->process_queues[0].empty())
// 	// {
// 	// 	for (int core = 0; core < num_cores; ++core)
// 	// 	{
// 	// 		if (!this->process_queues[core].empty()) {
//  //                std::cout << "Core: " << core << "; is called" << std::endl;
// 	// 			Process currentProcess = this->process_queues[core].back();
// 	// 			this->process_queues[core].pop_back();
// 	//
// 	// 			while (!currentProcess.hasFinished()) {
// 	// 				currentProcess.executeInstruction();
// 	// 			}
// 	//
//  //                // this->done_processes.push_back(currentProcess);
// 	// 		}
// 	// 	}
// 	// }
//
//     for (auto& currThread : worker_threads) {
//         // specify cores in here since default core will alwaye be @ 0
//         currThread.run();
//     }
// }

FCFSScheduler::FCFSScheduler(int num_cores)
  : num_cores(num_cores), process_queues(num_cores)
{
  /*
   * Placement of process creation is temporary at the moment going to
   * move this at SchedulerManager
   */
  for (int i = 0; i < 10; i++) {
    this->processes.emplace_back(Process("Process_"+std::to_string(i), 2000));
  }
  for (int i = 0; i < num_cores; i++) {
    worker_threads.emplace_back(SchedulerWorker(process_queues[i], done_processes)); 
  }
}

String FCFSScheduler::strProgress() const
{
  std::stringstream s_stream;
  s_stream << "Running processes" << "\n";
  for (auto& queue : this->process_queues) {
    for (auto& process : queue) {
      if (process.getCpuID() == -1) {
        s_stream << process.getProcessName() << "\t" << "(" << process.getTimeToStr() << ")" << "\t" << "Core: " << "N/A " << "\t" << process.getRemainingInstructions() << "/" << process.getTotalInstruction() << std::endl;
      } else {
        s_stream << process.getProcessName() << "\t" << "(" << process.getTimeToStr() << ")" << "\t" << "Core: " << process.getCpuID() << "  " << process.getRemainingInstructions() << "/" << process.getTotalInstruction() << std::endl;
      }
    }
  }
  /*
   * TODO: Fix timestamp for ending time
   */
  s_stream << "Finished processes" << "\n";
  for (auto& process : this->done_processes) {
    s_stream << process.getProcessName() << "\t" << "(" << process.getTimeToStr() << ")" << "\t" << "Finished" << "\t" << process.getTotalInstruction() - process.getRemainingInstructions() << "/"<< process.getTotalInstruction() << "\n";
  }
  return s_stream.str();
}

void FCFSScheduler::run()
{
  // initializes worker_threads
  for (auto& curr_thread : worker_threads) {
    curr_thread.start();
  }
  while (!this->processes.empty()) {
    for (int i = 0; i < num_cores; i++) {
      if (!this->worker_threads[i].isRunning()) {
        // need to add this check below
        if (!this->processes.empty()) 
        {
          addProcess(processes.front(), i);
          this->processes.erase(this->processes.begin());
        }
      }
      // need to add this to synchronize  process allocation to logical cores
      IETThread::sleep(5);
      /* 
       * TODO: would be implemented when `config.txt` is needed create a
       * variable that would hold the delay value within the config.txt
       */
      // IETThread::sleep(delay_ms);
    }
  }
  for (auto& curr_thread : worker_threads) {
    curr_thread.stop();
  }

}
