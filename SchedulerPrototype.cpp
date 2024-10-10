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

<<<<<<< HEAD
#include "SchedulerPrototype.h"

using namespace std;

SchedulerPrototype::SchedulerPrototype() : AConsole(SCHEDULER_CONSOLE)
{
}

void SchedulerPrototype::onEnabled()
{
    //threading?
}

void SchedulerPrototype::display()
{
    
}
//i think all these headers go to .h
=======
using namespace std;

// Struct to hold process information
struct Process
{
    string name;
    int totalTasks;  // Total tasks to complete
    int completedTasks;  // Completed tasks
    time_t startTime;  // Start time
    int coreId;  // Core where it's running

    Process(string n, int t) : name(n), totalTasks(t), completedTasks(0), startTime(time(0)), coreId(-1) {}
};

>>>>>>> 8d76f9538bef1230ca594d22e2aaf9d4f5ddc5fc
// Global variables
queue<Process*> readyQueue;  // Ready queue for processes
vector<Process*> runningProcesses;  // Processes running on CPU
vector<Process*> finishedProcesses; // Finished processes
mutex queueMutex;  // Mutex for queue synchronization
mutex displayMutex;  // Mutex for display synchronization

bool schedulerRunning = true;
const int coreCount = 4;
bool cores[coreCount] = {false};  // Core availability (false = free, true = busy)

// Helper function to get formatted time string
string getTimeString(time_t rawTime)
{
    char buffer[80];
    struct tm* timeinfo = localtime(&rawTime);
    strftime(buffer, 80, "%m/%d/%Y %I:%M:%S%p", timeinfo);
    return string(buffer);
}

// Function to log print commands to a file
void logPrintCommand(Process* process, string message)
{
    ifstream checkFile(process->name + ".txt");
    bool fileExists = checkFile.good();
    checkFile.close();

    ofstream logFile(process->name + ".txt", ios::app);

    // If the file is new, write the header
    if (!fileExists)
    {
        logFile << "Process name: " << process->name << endl;
        logFile << "Logs:" << endl << endl;
    }

    // Log the print command with timestamp and core info
    logFile << "(" << getTimeString(time(0)) << ") Core:" << process->coreId << " \"" << message << "\"" << endl;

    logFile.close();
}

// Simulate work for a CPU core
void cpuWorker(int coreId)
{
    // Set up the random number generator for sleep duration between 10ms to 1000ms
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(10, 1000); // Random time between 10ms and 1000ms

    while (schedulerRunning)
    {
        queueMutex.lock();
        if (!readyQueue.empty())
        {
            // Get next process from the ready queue
            Process* process = readyQueue.front();
            readyQueue.pop();
            process->coreId = coreId;
            runningProcesses.push_back(process);
            queueMutex.unlock();

            // Simulate process execution
            while (process->completedTasks < process->totalTasks)
            {
                // Generate a random sleep duration for each task
                int sleepDuration = dist(gen);
                this_thread::sleep_for(chrono::milliseconds(sleepDuration));  // Simulate task execution

                process->completedTasks++;
                logPrintCommand(process, "Hello world from " + process->name + "!");
            }

            // Move to finished queue
            queueMutex.lock();
            runningProcesses.erase(remove(runningProcesses.begin(), runningProcesses.end(), process), runningProcesses.end());
            finishedProcesses.push_back(process);
            queueMutex.unlock();
        }
        else
        {
            queueMutex.unlock();
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
}

// Display the UI
void displayUI()
{
    while (schedulerRunning)
    {
        displayMutex.lock();
        system("cls");
        cout << "------------------------------------------" << endl;
        cout << "Running processes:" << endl;

        for (auto process : runningProcesses)
        {
            cout << process->name << "\t(" << getTimeString(process->startTime) << ")\tCore:\t" 
                 << process->coreId << "\t" << process->completedTasks << " / " << process->totalTasks << endl;
        }

        cout << endl << "Finished processes:" << endl;

        for (auto process : finishedProcesses)
        {
            cout << process->name << "\t(" << getTimeString(process->startTime) << ")\tCore:\t" 
                 << process->coreId << "\t" << process->totalTasks << " / " << process->totalTasks << endl;
        }

        cout << "------------------------------------------" << endl;
        displayMutex.unlock();

        this_thread::sleep_for(chrono::seconds(1));  // Refresh every second
    }
}

// Scheduler function to distribute processes
void scheduler()
{
    for (int i = 0; i < coreCount; i++)
    {
        thread(cpuWorker, i).detach();
    }
}

int main()
{
    // Simulate creating some processes and adding to ready queue
    readyQueue.push(new Process("process01", 5876));
    readyQueue.push(new Process("process02", 5876));
    readyQueue.push(new Process("process03", 1000));
    readyQueue.push(new Process("process04", 80));
    readyQueue.push(new Process("process05", 5876));
    readyQueue.push(new Process("process06", 5876));
    readyQueue.push(new Process("process07", 1000));
    readyQueue.push(new Process("process08", 80));

    // Start the scheduler
    thread schedulerThread(scheduler);
    thread uiThread(displayUI);

    // Allow simulation to run for a period of time
    this_thread::sleep_for(chrono::minutes(2));

    // Stop the simulation
    schedulerRunning = false;

    schedulerThread.join();
    uiThread.join();

    return 0;
}