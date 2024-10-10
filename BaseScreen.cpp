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
    this->attachedProcess = process;
    // const auto now = std::chrono::system_clock::now();
    // this->timeCreated = std::chrono::system_clock::to_time_t(now);
    time_t curr_time = time(NULL);
    this->timeStamp = *localtime(&curr_time);
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
//     strStream << "Process: " << this->attachedProcess->getProcessName() << std::endl;
//     strStream << "ID: " << this->attachedProcess->getUid() << std::endl;
//     strStream << std::endl;
//     strStream << "Current instruction line: " << this->attachedProcess->getCurrentIL()  
//         << " / " << this->attachedProcess->getLinesCode() << std::endl;
//     // strStream << "Lines of code: " << this->attachedProcess->getLinesCode() << std::endl;
//     strStream << "Timestamp: " << std::setfill('0') << std::setw(2) << time.tm_mon+1 << "/"
//         << std::setfill('0') << std::setw(2)  << time.tm_mday << "/"
//         << time.tm_year + 1900 << ", "
//         << std::setfill('0') << std::setw(2) << time.tm_hour << ":"
//         << std::setfill('0') << std::setw(2) << time.tm_min << ":" 
//         << std::setfill('0') << std::setw(2) << time.tm_sec << " " << hr12
//         << std::endl;
//
//     this->commandHist.append(strStream.str());
// }

void BaseScreen::onEnabled()
{
    // ConsoleDriver::getInstance()->drawConsole();
    this->printProcessInfo();
}

void BaseScreen::process()
{
    //put exit command here (when exit go back to main console)
    this->commandHist.append("root:\\> ");

    String sInput;
    std::getline(std::cin, sInput);
    this->commandHist.append(sInput+"\n");
    if (sInput == "exit") {
        ConsoleDriver::getInstance()->returnToPreviousConsole();
    }
    else {
        std::cerr << "Unknown command: " << sInput << std::endl;
        this->commandHist.append("Unknown command: " + sInput + "\n");
    }
    // this->commandHist.append("\n");
}

void BaseScreen::display()
{
    /*
     * This is where we print??
     * */
    if (this->attachedProcess == nullptr) {
        std::cerr << "Process not properly attached" << std::endl;
    }
    std::cerr << "root:\\> ";

}

tm& BaseScreen::getTime()
{
    return this->timeStamp;
}

void BaseScreen::printProcessInfo() const
{
    // char timeString[std::size("mm/dd/yyyy, hh:mm:ss")]
    tm time = this->timeStamp;
    String hr12;
    if (time.tm_hour >= 12) {
        time.tm_hour = time.tm_hour - 12;
        hr12 = "PM";
    }
    else {
        hr12 = "AM";
    }
    std::cerr << "Process: " << this->attachedProcess->getProcessName() << std::endl;
    std::cerr << "ID: " << this->attachedProcess->getUid() << std::endl;
    std::cerr << std::endl;
    std::cerr << "Current instruction line: " << this->attachedProcess->getCurrentIL()  
        << " / " << this->attachedProcess->getLinesCode() << std::endl;
    // std::cerr << "Lines of code: " << this->attachedProcess->getLinesCode() << std::endl;
    std::cerr << "Timestamp: " << std::setfill('0') << std::setw(2) << time.tm_mon+1 << "/"
        << std::setfill('0') << std::setw(2)  << time.tm_mday << "/"
        << time.tm_year + 1900 << ", "
        << std::setfill('0') << std::setw(2) << time.tm_hour << ":"
        << std::setfill('0') << std::setw(2) << time.tm_min << ":" 
        << std::setfill('0') << std::setw(2) << time.tm_sec << " " << hr12
        << std::endl;
    std::cerr << this->commandHist;
    // std::cerr << "root:\\> ";
}
