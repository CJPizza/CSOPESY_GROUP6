#include "Process.h"
#include "IETThread.h"
#include <cstdlib>
#include <iostream>
#include <unistd.h>

// TODO: complete missing fields or functions in the once requirements are specified

Process::Process(String nameIn, int numInstruction)
    : uid(newUID++)
{
    this->processName = nameIn;
    this->totalInstruction = numInstruction;
    this->remainingInstruction = numInstruction;
    time_t curr_time = time(NULL);
    this->timeStamp = *localtime(&curr_time);
}

int Process::getUid() const
{
    return this->uid;
}

//int Process::getCurrentIL()
//{
//    return this->currentIL;
//}

Process::String Process::getProcessName() const
{
    return this->processName;
}

//int Process::getLinesCode()
//{
//    return this->linesCode;
//}

int Process::getTotalInstruction() const
{
    return this->totalInstruction;
}

int Process::getRemainingInstructions() const 
{
    return this->remainingInstruction;
}

bool Process::hasFinished() const 
{
    return this->remainingInstruction == 0;
}

void Process::executeInstruction()
{
    // std::cout << "Core: " << this->cpuCoreID << std::endl;
    if (this->remainingInstruction > 0)
    {
        // std::cout << "Executing instruction for Process " << this->uid << "; " << this->processName << "\n";
        this->remainingInstruction = this->remainingInstruction - 1;
        // Testing purposes
        IETThread::sleep(1000);
    }
    else {
        // std::cout << "Process " << this->uid << "; " << this->processName << " has already finished.\n";
    }
}

void Process::setCpuID(int coreID)
{
    cpuCoreID = coreID;
}

// void Process::incrementInstruction()
// {
//     if (this->currentIL < this->linesCode)
//     {
//         this->currentIL++;
//     }
//
// }

int Process::newUID = 0;


// string getName() const {
//     return name;
// }
// };
