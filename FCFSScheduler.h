#pragma once

#include <vector>

#include "IETThread.h"
#include "Process.h"
#include "FCFSSchedulerWorker.h"

class FCFSScheduler : public IETThread
{
private:
	int numCores;
	std::vector<std::vector<Process>> processQueues;
    std::vector<Process> finishedProcess;
    std::vector<FCFSSchedulerWorker> workerThreads;
public:
	// FCFSScheduler(int cores) : numCores(cores), processQueues(cores) {}
    FCFSScheduler(int cores);

	void addProcess(const Process& process, int core = 0);
	void sortProcessQueues();
	void runScheduler();
    void run() override;
    void printProgress();
};
