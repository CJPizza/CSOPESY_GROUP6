#include "Process.h"
#include <cstdlib>
#include <iostream>

// TODO: complete missing fields or functions in the once requirements are specified

Process::Process(String nameIn, int numInstruction)
    : uid(newUID++)
{
    this->processName = nameIn;
<<<<<<< Updated upstream
    this->linesCode = 100;
=======
    this->totalInstruction = numInstruction;
    this->remainingInstruction = numInstruction;
    this->commandCounter = 0;
>>>>>>> Stashed changes
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
    if (this->remainingInstruction > 0)
    {
        std::cout << "Executing instruction for Process " << this->uid << "; " << this->processName << "\n";
        this->remainingInstruction = this->remainingInstruction - 1;
    }
    else {
        std::cout << "Process " << this->uid << "; " << this->processName << " has already finished.\n";
    }
}

void Process::incrementInstruction()
{
    if (this->currentIL < this->linesCode)
    {
        this->currentIL++;
    }

}

int Process::newUID = 0;


// string getName() const {
//     return name;
// }
// };