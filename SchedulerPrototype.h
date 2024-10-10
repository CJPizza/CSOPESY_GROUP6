#pragma once
#include <iostream>
#include <thread>
#include <queue>
#include <vector>
#include <fstream>
#include <ctime>
#include <mutex>
#include <string>
#include <chrono>
#include <random>
#include <algorithm>
#include "AConsole.h"

using namespace std;

class SchedulerPrototype : public AConsole
{
    public:
        SchedulerPrototype();
        ~SchedulerPrototype() = default;
        void onEnabled() override;
        void process() override;
        void display() override;
        
        struct Process
        {
            string name;
            int totalTasks;  // Total tasks to complete
            int completedTasks;  // Completed tasks
            time_t startTime;  // Start time
            int coreId;  // Core where it's running

            Process(string n, int t) : name(n), totalTasks(t), completedTasks(0), startTime(time(0)), coreId(-1) {}
        };

        void logPrintCommand(Process* process, string message);
        void displayUI();
        void scheduler();
        void startScheduler();
};
// Struct to hold process information
