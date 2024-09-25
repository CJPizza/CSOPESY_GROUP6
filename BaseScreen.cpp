#include <iostream>
#include <memory>

#include "BaseScreen.h"
#include "ConsoleDriver.h"

BaseScreen::BaseScreen(std::shared_ptr<Process> process, String processName): AConsole(processName)
{

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

}

void BaseScreen::display()
{
    /*
     * This is where we print??
     * */
    this->printProcessInfo();
}

void BaseScreen::printProcessInfo() const
{
    std::cerr << "Process: " << this->attachedProcess->getProcessName() << std::endl;
    std::cerr << "ID: " << this->attachedProcess->getUid() << std::endl;
    std::cerr << std::endl;
    std::cerr << "Current instruction line: " << this->attachedProcess->getCurrentIL();
    std::cerr << "Lines of code: " << this->attachedProcess->getLinesCode();
    std::cerr << "root:\\> ";
}
