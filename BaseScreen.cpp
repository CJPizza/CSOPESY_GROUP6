#include <chrono>
#include <ctime>
#include <iostream>
#include <memory>
#include <iomanip>
#include <ostream>
#include <string>
#include <sstream>

#include "BaseScreen.h"
#include "ConsoleDriver.h"
#include "MainConsole.h"

BaseScreen::BaseScreen(std::shared_ptr<Process> process, String processName): AConsole(processName)
{
    this->attached_process = process;
    // const auto now = std::chrono::system_clock::now();
    // this->timeCreated = std::chrono::system_clock::to_time_t(now);
}


// void BaseScreen::loadHeaderToStr()
// {
//     // char timeString[std::size("mm/dd/yyyy, hh:mm:ss")]
//     tm time = this->timeStamp;
//     String hr12;
//     if (time.tm_hour >= 12) {
//         time.tm_hour = time.tm_hour - 12;
//         hr12 = "PM";
//     }
//     else {
//         hr12 = "AM";
//     }
//     std::stringstream strStream;
//
//     strStream << "Process: " << this->attached_process->getProcessName() << std::endl;
//     strStream << "ID: " << this->attached_process->getUid() << std::endl;
//     strStream << std::endl;
//     strStream << "Current instruction line: " << this->attached_process->getCurrentIL()  
//         << " / " << this->attached_process->getLinesCode() << std::endl;
//     // strStream << "Lines of code: " << this->attached_process->getLinesCode() << std::endl;
//     strStream << "Timestamp: " << std::setfill('0') << std::setw(2) << time.tm_mon+1 << "/"
//         << std::setfill('0') << std::setw(2)  << time.tm_mday << "/"
//         << time.tm_year + 1900 << ", "
//         << std::setfill('0') << std::setw(2) << time.tm_hour << ":"
//         << std::setfill('0') << std::setw(2) << time.tm_min << ":" 
//         << std::setfill('0') << std::setw(2) << time.tm_sec << " " << hr12
//         << std::endl;
//
//     this->command_hist.append(strStream.str());
// }

void BaseScreen::onEnabled()
{
    // ConsoleDriver::getInstance()->drawConsole();
    this->printProcessInfo();
}

void BaseScreen::process()
{
    //put exit command here (when exit go back to main console)
    this->command_hist.append("root:\\> ");

    String sInput;
    std::getline(std::cin, sInput);
    this->command_hist.append(sInput+"\n");
    if(sInput == "process-smi"){
        if(this->attached_process->hasFinished()){
            std::cerr << "Finished!" << std::endl;
        }

        std::cerr << "Current instruction line: " << this->attached_process->getRemainingInstructions() << "\n";
        std::cerr << "Lines of code: " << this->attached_process->getTotalInstruction() << "\n";
    }
    else if (sInput == "exit") {
            //if exit and curr instruction == line of code print cant go back na
            //remove from console table ? but then if we do this it could create duplicate processes (in terms of name)   
            //or we can add boolean na if isFinished == true then cant go back na
        ConsoleDriver::getInstance()->returnToPreviousConsole();
    }
    else {
        std::cerr << "Unknown command: " << sInput << std::endl;
        this->command_hist.append("Unknown command: " + sInput + "\n");
    }
    // this->command_hist.append("\n");
}

void BaseScreen::display()
{
    /*
     * This is where we print??
     * */
    if (this->attached_process == nullptr) {
        std::cerr << "Process not properly attached" << std::endl;
    }
    std::cerr << "root:\\> ";

}

void BaseScreen::printProcessInfo() const
{
    // char timeString[std::size("mm/dd/yyyy, hh:mm:ss")]
    // tm time = this->timeStamp;
    // String hr12;
    // if (time.tm_hour >= 12) {
    //     time.tm_hour = time.tm_hour - 12;
    //     hr12 = "PM";
    // }
    // else {
    //     hr12 = "AM";
    // }
    std::cerr << "Process: " << this->attached_process->getProcessName() << std::endl;
    std::cerr << "ID: " << this->attached_process->getUid() << std::endl;
    std::cerr << std::endl;
    //std::cerr << "Current instruction line: " << this->attached_process->getCurrentIL();
        //<< " / " << this->attached_process->getLinesCode() << std::endl;
    // std::cerr << "Lines of code: " << this->attached_process->getLinesCode() << std::endl;
    // Time printing
    // std::cerr << "Timestamp: " << std::setfill('0') << std::setw(2) << time.tm_mon+1 << "/"
    //     << std::setfill('0') << std::setw(2)  << time.tm_mday << "/"
    //     << time.tm_year + 1900 << ", "
    //     << std::setfill('0') << std::setw(2) << time.tm_hour << ":"
    //     << std::setfill('0') << std::setw(2) << time.tm_min << ":" 
    //     << std::setfill('0') << std::setw(2) << time.tm_sec << " " << hr12
    //     << std::endl;
    std::cerr << this->command_hist;
    // std::cerr << "root:\\> ";
}
