#pragma once
#include "AConsole.h"
#include "FCFSScheduler.h"
#include "SchedulerManager.h"

class MainConsole : public AConsole 
{
public:
    MainConsole();
    ~MainConsole() = default;
    void onEnabled() override;
    void process() override;
    void display() override;
    HANDLE console_handle;
    void printHeader() const;
    void lsUI() const;
    FCFSScheduler fcfs_scheduler = FCFSScheduler(4);
    std::vector<Process> processes;
private:
    SchedulerManager* sched_manager;
    bool initialized = true; // checks if initialized command was called 
};
