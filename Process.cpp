#include "Process.h"
#include "IETThread.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <fstream>
#include <filesystem>

/*
 * TODO: Implement ICommand and stuff, then finish executeCurrCommand executeInstruction
 * will be deprecated.
 */

Process::Process(String name, int num_ins)
    : uid(new_uid++)
{
    this->name = name;
    this->total_ins = num_ins;
    this->rem_ins = num_ins;
    time_t curr_time = time(NULL);
    this->time_stamp = *localtime(&curr_time);
    this->createFile();
    this->curr_state = READY;
}

int Process::getUid() const
{
    return this->uid;
}

String Process::getProcessName() const
{
    return this->name;
}

int Process::getTotalInstruction() const
{
    return this->total_ins;
}

int Process::getRemainingInstructions() const 
{
    return this->rem_ins;
}

bool Process::hasFinished() const 
{
    return this->rem_ins == 0;
}

void Process::executeInstruction()
{
    // std::cout << "Core: " << this->cpuCoreID << std::endl;
    std::fstream file(this->getProcessName()+".txt", std::ios::in | std::ios::out | std::ios::app); 
    if (!file)
    {
        std::cerr << "Error opening file." << std::endl;
    }
    if (this->rem_ins > 0)
    {
        this->rem_ins = this->rem_ins - 1;
        // call file append here
        // appends to file `process_name.txt`
        file << this->getProcessName() << "\t" << "(" << this->getCurrTimeToStr() << ")" << "\t" << "Core: " << this->getCpuID() << " " << "Hello world from " << this->getProcessName() << "\n";
        // 13ms seems to be the minimum val to synchronize process execution between cores
        // it can be adjsted to 1 but its order would not be sequential
        IETThread::sleep(1);
    }
    else {
        // std::cout << "Process " << this->uid << "; " << this->processName << " has already finished.\n";
    }
    file.close();
}

void Process::setCpuID(int core_id)
{
    this->core_id = core_id;
}

int Process::getCpuID() const
{
    return this->core_id;
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
    strftime(buffer, 80, "%m/%d/%Y %I:%M:%S%p", &this->time_stamp);
    return String(buffer);
}

String Process::getCurrTimeToStr()
{
    time_t time_dump = time(NULL);
    // this->time_stamp = *localtime(&curr_time);
    tm curr_time = *localtime(&time_dump);
    char buffer[80];
    strftime(buffer, 80, "%m/%d/%Y %I:%M:%S%p", &curr_time);
    return String(buffer);
}

int Process::new_uid = 0;

void Process::createFile()
{
    this->deleteFile();
    std::ofstream log_file(this->name + ".txt", std::ios::app);
    // If the file is new, write the header
        log_file << "Process name: " << this->getProcessName() << "\n";
        log_file << "Logs:" << "\n" << "\n";
    // Log the print command with timestamp and core info
    // log_file << "(" << this->getTimeToStr() << ") Core:" <<  " \"" << message << "\"" << endl;
    log_file.close();
}

void Process::deleteFile() 
{
    String filePath = this->name + ".txt";
    std::filesystem::path path(filePath);

    // Check if the file exists
    if (std::filesystem::exists(path)) {
        // Attempt to remove the file
        std::error_code ec; // For error handling
        std::filesystem::remove(path, ec);
        
        if (ec) {
            std::cerr << "Error deleting file: " << ec.message() << std::endl;
            return;
        } else {
            // std::cout << "File deleted successfully." << std::endl;
        }
    } else {
        // std::cout << "File does not exist." << std::endl;
    }
}

void Process::executeCurrCommand() const
{
    this->command_list[this->command_counter]->execute();
}


void Process::moveToNextLine()
{
    this->command_counter++;
}
