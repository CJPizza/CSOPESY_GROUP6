#pragma once

#include <deque>
#include <mutex>
#include <vector>

#include "IETThread.h"
#include "Process.h"
#include "SchedulerWorker.h"

class FCFSScheduler : public IETThread
{
public:
	// FCFSScheduler(int cores) : numCores(cores), processQueues(cores) {}
    FCFSScheduler(int cores);

	void addProcess(const Process& process, int core = 0);
	void sortProcessQueues();
	// void runScheduler();
    void run() override;
    void printProgress();

protected:
    // std::deque<SchedulerWorker> free_threads; // stores all free threads

private:
	int num_cores;
    // TODO: Would probably move these in to a scheduler manager class
	std::vector<std::vector<Process>> process_queues; // Ready Queues for each threads
    std::vector<Process> processes; // processes before they are allocated to each threads
    std::vector<Process> done_processes; // processes that are finish
    std::vector<SchedulerWorker> worker_threads; // logical cores emulation
    std::mutex mtx;
};
