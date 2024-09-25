#include "ConsoleDriver.h"
#include "MainConsole.h"
#include "AConsole.h"
#include "BaseScreen.h"
#include <iostream>
// #include <unordered_map>

const String MAIN_CONSOLE = "MAIN_CONSOLE";

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

void ConsoleDriver::getConsoleHandle() const
{
    return this->getConsoleHandle();
}

void ConsoleDriver::drawConsole() const
{
    if (this->currentConsole != nullptr) {
        this->currentConsole->display();
    }
    std::cerr << "There is no assigned console. Please check." << std::endl;
}

void ConsoleDriver::process() const
{
    if (this->currentConsole != nullptr) {
        this->currentConsole->process
    }
    else {
        std::cerr << "There is no assigned console. Please check." << std::endl;
    }
}

void ConsoleDriver::registerScreen(std::shared_ptr<BaseScreen> screenRef)
{
    if(this->consoleTable.contains(screenRef->getName())) 
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
        this->previousConsole = this->currentConsole;
        this->currentConsole = this->consoleTable[screenName];
        this->currentConsole->onEnabled;
    }
}

/*
 * Console name is marquee, main and memory
 * */

void ConsoleDriver::switchConsole(String consoleName)
{
    if(this->consoleTable.contains(consoleName))
    {
        system("cls");
        this->previousConsole = this->currentConsole;
        this->currentConsole = this->consoleTable[consoleName];
        this->currentConsole->onEnabled();
    }
    else 
    {
        std::cerr << "Console name " << consoleName << " not found. Was it initialized?" << std::endl;
    }
}

void ConsoleDriver::exitApplication() 
{
    if (this->previousConsole == nullptr) {
        this->running = false;
    }
    else {
        this->currentConsole = this->previousConsole;
        this->previousConsole = nullptr;
    }
}

ConsoleDriver::ConsoleDriver()
{
    this->running = true;

    this->consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    const std::shared_ptr<MainConsole> mainConsole = std::make_shared<MainConsole>();
    // const std::shared_ptr<MarqueeConsole> mainConsole = std::make_shared<MarqueeConsole>();
    // const std::shared_ptr<SchedulingConsole> mainConsole = std::make_shared<SchedulingConsole>();
    // const std::shared_ptr<MemorySimulationConsole> mainConsole = std::make_shared<MemorySimulationConsole>();


    this->consoleTable[MAIN_CONSOLE] = mainConsole;

    this->switchConsole(MAIN_CONSOLE);
}
