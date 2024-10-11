#include "FCFSSchedulerWorker.h"
#include "Process.h"

void FCFSSchedulerWorker::run()
{
    for (auto& process : *this->processesToExecute) {
        while(!process.hasFinished()) {
            process.executeInstruction();
        }
        
        finishedProcesses.push_back(process);
    }   
}

FCFSSchedulerWorker::FCFSSchedulerWorker(std::vector<Process>* processesToExecute, std::vector<Process>& finshedProcesses)
{
    this->processesToExecute = processesToExecute;
    this->finishedProcesses = finshedProcesses;
}
