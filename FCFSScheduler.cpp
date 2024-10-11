#include "FCFSScheduler.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

void FCFSScheduler::addProcess(const Process& process, int core)
{
	if (core >= 0 && core <= this->numCores)
	{
		processQueues[core].push_back(process);
	}
	else
	{
		std::cerr << "Invalid core specifed for process addition.\n";
	}
}

void FCFSScheduler::sortProcessQueues()
{
	for (auto& queue : this->processQueues)
	{
		std::sort(queue.begin(), queue.end(), [](const Process& a, const Process& b) {
			return a.getRemainingInstructions() > b.getRemainingInstructions();
			});
	}
}

void FCFSScheduler::runScheduler()
{
    // std::cout << "Numcores " << this->numCores;
	// while (!this->processQueues[0].empty())
	// {
	// 	for (int core = 0; core < numCores; ++core)
	// 	{
	// 		if (!this->processQueues[core].empty()) {
 //                std::cout << "Core: " << core << "; is called" << std::endl;
	// 			Process currentProcess = this->processQueues[core].back();
	// 			this->processQueues[core].pop_back();
	//
	// 			while (!currentProcess.hasFinished()) {
	// 				currentProcess.executeInstruction();
	// 			}
	//
 //                // this->finishedProcess.push_back(currentProcess);
	// 		}
	// 	}
	// }

    for (auto& currThread : workerThreads) {
        // specify cores in here since default core will alwaye be @ 0
        currThread.run();
    }
}

FCFSScheduler::FCFSScheduler(int numCores)
    : numCores(numCores), processQueues(numCores)
{
    // this->numCores = numCores;
    // this->processQueues.resize(numCores);
    for (int i = 0; i < numCores; i++) {
        workerThreads.emplace_back(FCFSSchedulerWorker(&processQueues[i], &finishedProcess)); 
    }
}

void FCFSScheduler::printProgress()
{
    for (auto& queue : this->processQueues) {
        for (auto& process : queue) {
            std::cout << process.getProcessName() << " " << process.getRemainingInstructions() << "/" << process.getTotalInstruction() << std::endl;
        }
    }
}

void FCFSScheduler::run()
{
    for (auto& currThread : workerThreads) {
        // specify cores in here since default core will alwaye be @ 0
        currThread.start();
    }
}
