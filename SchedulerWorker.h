#pragma once
#include "IETThread.h"
#include "Process.h"
#include <memory>
#include <mutex>
#include <vector>

/*
 * This class emulates logical cores
 */

class SchedulerWorker : public IETThread {
public:
    SchedulerWorker(std::vector<Process>& processes_to_exec, std::vector<Process>& finished_processes); 

    bool isRunning() const;

    void run() override;
    void stop();

private:
    inline static int new_id = 0;
    int core_id;
    bool running = false; // corresponds to process execution
    bool execute = true;
    std::unique_ptr<std::mutex> mtx;
    std::vector<Process> &processes_to_exec;
    std::vector<Process> &finished_processes;
    // std::mutex mtx;
};
