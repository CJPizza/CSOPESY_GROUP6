#include <iostream>
#include <memory>

#include "BaseScreen.h"
#include "ConsoleDriver.h"

BaseScreen::BaseScreen(std::shared_ptr<Process> process, String processName): AConsole(processName)
{
    this->attachedProcess = process;
}

void BaseScreen::onEnabled()
{
    ConsoleDriver::getInstance()->drawConsole();
    /*
     * Toggles display and process (Input handling)??
     * */
}

void BaseScreen::process()
{
    //put exit command here (when exit go back to main menu)
    std::cerr << "root:\\> ";
    String sInput;
    std::getline(std::cin, sInput);
    
    if (sInput == "exit") {
        ConsoleDriver::getInstance()->returnToPreviousConsole();
    }
}

void BaseScreen::display()
{
    /*
     * This is where we print??
     * */
    if (this->attachedProcess == nullptr) {
        std::cerr << "Process not properly attached" << std::endl;
    }
    this->printProcessInfo();
}

void BaseScreen::printProcessInfo() const
{
    std::cerr << "Process: " << this->attachedProcess->getProcessName() << std::endl;
    std::cerr << "ID: " << this->attachedProcess->getUid() << std::endl;
    std::cerr << std::endl;
    std::cerr << "Current instruction line: " << this->attachedProcess->getCurrentIL() << std::endl;
    std::cerr << "Lines of code: " << this->attachedProcess->getLinesCode() << std::endl;
    // std::cerr << "root:\\> ";
}
