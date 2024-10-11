#include "Process.h"
#include "IETThread.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <fstream>
#include <filesystem>

// TODO: complete missing fields or functions in the once requirements are specified

Process::Process(String nameIn, int numInstruction)
    : uid(newUID++)
{
    this->processName = nameIn;
    this->totalInstruction = numInstruction;
    this->remainingInstruction = numInstruction;
    time_t curr_time = time(NULL);
    this->timeStamp = *localtime(&curr_time);
    this->createFile();
}

int Process::getUid() const
{
    return this->uid;
}

//int Process::getCurrentIL()
//{
//    return this->currentIL;
//}

String Process::getProcessName() const
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
    std::fstream file(this->getProcessName()+".txt", std::ios::in | std::ios::out | std::ios::app); 
    if (!file)
    {
        std::cerr << "Error opening file." << std::endl;
    }
    if (this->remainingInstruction > 0)
    {
        // std::cout << "Executing instruction for Process " << this->uid << "; " << this->processName << "\n";
        this->remainingInstruction = this->remainingInstruction - 1;
        // Testing purposes
        // call file append here
        file << this->getProcessName() << "\t" << "(" << this->getTimeToStr() << ")" << "\t" << "Core: " << this->getCpuID() << " " << "Hello world from " << this->getProcessName() << "\n";
        IETThread::sleep(100);
    }
    else {
        // std::cout << "Process " << this->uid << "; " << this->processName << " has already finished.\n";
    }
}

void Process::setCpuID(int coreID)
{
    cpuCoreID = coreID;
}

int Process::getCpuID() const
{
    return this->cpuCoreID;
}

// void Process::incrementInstruction()
// {
//     if (this->currentIL < this->linesCode)
//     {
//         this->currentIL++;
//     }
//
// }

String Process::getTimeToStr() const
{
    char buffer[80];
    strftime(buffer, 80, "%m/%d/%Y %I:%M:%S%p", &this->timeStamp);
    return String(buffer);
}
int Process::newUID = 0;

void Process::createFile()
{
    this->deleteFile();
    std::ofstream logFile(this->processName + ".txt", std::ios::app);
    // If the file is new, write the header
        logFile << "Process name: " << this->getProcessName() << "\n";
        logFile << "Logs:" << "\n" << "\n";
    // Log the print command with timestamp and core info
    // logFile << "(" << this->getTimeToStr() << ") Core:" <<  " \"" << message << "\"" << endl;
    logFile.close();
}

void Process::deleteFile() {
    String filePath = this->processName + ".txt";
    std::filesystem::path path(filePath);

    // Check if the file exists
    if (std::filesystem::exists(path)) {
        // Attempt to remove the file
        std::error_code ec; // For error handling
        std::filesystem::remove(path, ec);
        
        if (ec) {
            // std::cerr << "Error deleting file: " << ec.message() << std::endl;
        } else {
            // std::cout << "File deleted successfully." << std::endl;
        }
    } else {
        // std::cout << "File does not exist." << std::endl;
    }
}
// string getName() const {
//     return name;
// }
// };

