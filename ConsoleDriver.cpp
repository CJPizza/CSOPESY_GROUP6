#include "ConsoleDriver.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <ostream>
#include <MainConsole.h>

ConsoleDriver* ConsoleDriver::sharedInstance = nullptr;
ConsoleDriver* ConsoleDriver::getInstance()
{
    return sharedInstance;
}

void ConsoleDriver::initialize()
{
    sharedInstance = new ConsoleDriver();
}

void ConsoleDriver::destroy()
{
    delete sharedInstance;
}

void ConsoleDriver::registerScreen(std::shared_ptr<BaseScreen> screenRef)
{
    if(this.consoleTable.contains(screenRef->getName())) 
    {
        std::cerr << "Screen name " << screenRef->getName() << "already exists. Please use a different name." << std::endl;
        return;
    }

    this->consoleTable[screenRef->getName()] = screenRef;
}

void ConsoleDriver::switchToScreen(String screenName)
{
    if(this->consoleTable.contains(screenName))
    {
        system("cls");
        this.previousConsole = 
    }
}

void ConsoleDriver::switchConsole(String consoleName)
{
    if(this->consoleTable.contains(consoleName))
    {
        system("cls");
        this.previousConsole = this.currentConsole;
        this.currentConsole = this.conoleTable[consoleName];
        this.currentConsole = onEnabled;
    }
    else {
        std::cerr << "Console name " << consoleName << " not found. Was it initialized?" << std::endl;
    }
}

ConsoleDriver::ConsoleDriver()
{
    this->running = true;

    this->consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    // const std::shared_ptr<MainConsole> mainConsole = std::make_shared<MainConsole>();
    // const std::shared_ptr<MarqueeConsole> mainConsole = std::make_shared<MarqueeConsole>();
    // const std::shared_ptr<SchedulingConsole> mainConsole = std::make_shared<SchedulingConsole>();
    // const std::shared_ptr<MemorySimulationConsole> mainConsole = std::make_shared<MemorySimulationConsole>();

    this.switchConsole(MAIN_CONSOLE);
}
