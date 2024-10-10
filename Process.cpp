#include "Process.h"

// TODO: complete missing fields or functions in the once requirements are specified

Process::Process(String nameIn) 
    : uid(newUID++)
{
    this->processName = nameIn;
    this->linesCode = 100;
}

int Process::getUid() 
{
    return this->uid;
}

int Process::getCurrentIL()
{
    return this->currentIL;
}

Process::String Process::getProcessName() const
{
    return this->processName;
}

int Process::getLinesCode()
{
    return this->linesCode;
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