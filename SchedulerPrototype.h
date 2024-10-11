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
#include <windows.h>

#include "AConsole.h"

using namespace std;
typedef std::string String;

class SchedulerPrototype : public AConsole
{
    public:
        HANDLE consoleHandle;
        SchedulerPrototype();
        ~SchedulerPrototype() = default;
        void onEnabled() override;
        void process() override;
        void display() override;
        void startScheduler(); //process
        
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
        void displayUI(); //display
        void scheduler(); //onenabled
        string getTimeString(time_t startTime);
        void cpuWorker(int coreId);

        // Global variables
        queue<Process*> readyQueue;  // Ready queue for processes
        vector<Process*> runningProcesses;  // Processes running on CPU
        vector<Process*> finishedProcesses; // Finished processes
        mutex queueMutex;  // Mutex for queue synchronization
        mutex displayMutex;  // Mutex for display synchronization

        private:
            bool schedulerRunning = true;
            static const int coreCount = 4;
            bool cores[coreCount] = {false};  // Core availability (false = free, true = busy)
            std::thread schedulerThread;
};
// Struct to hold process information
