#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "AConsole.h"
#include "ConsoleDriver.h"
#include "FCFSScheduler.h"
#include "Process.h"


typedef std::string String;

// TODO: other classes when invoking ConsoleDriver::getInstance() seems to return a null_ptr 
// which causes issues i.e. HANDLE not being returned from ConsoleDriver causing it to crash

int main()
{	
    ConsoleDriver::initialize();
    // std::srand(static_cast<unsigned>(std::time(0)));
    // std::vector<Process> processes;
    // processes.emplace_back("Process_1", 10);
    // processes.emplace_back("Process_2", 20);
    // processes.emplace_back("Process_3", 30);
    // processes.emplace_back("Process_4", 20);
    // processes.emplace_back("Process_5", 10);
    // processes.emplace_back("Process_6", 10);
    // processes.emplace_back("Process_7", 10);
    // processes.emplace_back("Process_8", 10);
    // processes.emplace_back("Process_9", 10);
    // processes.emplace_back("Process_10", 10);

    // FCFSScheduler fcfsscheduler(4);
    //
    //
    // for (const auto& process : processes) {
    //     // specify cores in here since default core will alwaye be @ 0
    //     fcfsscheduler.addProcess(process);
    // }
    // fcfsscheduler.sortProcessQueues();
    //
    // for (int i = 0; i < processes.size(); i++) {
    //     fcfsscheduler.addProcess(processes[i], i % 4);
    // }
    //
    // fcfsscheduler.runScheduler();

    String sInput;
    bool running = true;

    while (running)
    {
        
        // TODO: create a singleton for processScheduler
        // as a temporary application of FCFSScheduler I'll just put
        // its initialization at ConsoleDriver constructor
        ConsoleDriver::getInstance()->process(); 
        ConsoleDriver::getInstance()->drawConsole();

        running = ConsoleDriver::getInstance()->isRunning();
    }

    ConsoleDriver::destroy();

    return 0;
}
