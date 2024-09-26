#include <iostream>

#include "ConsoleDriver.h"
#include "MainConsole.h"
#include "AConsole.h"
#include "BaseScreen.h"

//

ConsoleDriver* ConsoleDriver::sharedInstance = nullptr;

ConsoleDriver* ConsoleDriver::getInstance() 
{
    if (sharedInstance == nullptr) 
    {
        sharedInstance = new ConsoleDriver();
    }
    return sharedInstance;
}

void ConsoleDriver::initialize()
{
    // sharedInstance = new ConsoleDriver();
    if (sharedInstance == nullptr) {
        sharedInstance = new ConsoleDriver();
    } else {
        std::cerr << "ConsoleDriver already initialized." << std::endl;
    }
}

void ConsoleDriver::destroy()
{
    delete sharedInstance;
}

HANDLE ConsoleDriver::getConsoleHandle() const
{
    return this->consoleHandle;
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
        this->currentConsole->process();
    }
    else {
        std::cerr << "There is no assigned console. Please check." << std::endl;
    }
}

void ConsoleDriver::registerScreen(std::shared_ptr<BaseScreen> screenRef)
{
    if (this->consoleTable.find(screenRef->getName()) != this->consoleTable.end())
    {
        std::cerr << "Screen name " << screenRef->getName() << " already exists. Please use a different name." << std::endl;
        return;
    }

    this->consoleTable[screenRef->getName()] = screenRef;
}

void ConsoleDriver::unregisterScreen(String screenName) 
{
    if (this->consoleTable.find(screenName) != this->consoleTable.end()) {
        this->consoleTable.erase(screenName);
    }
    else {
        std::cerr << "Unable to unregister " << screenName << std::endl;
    }
}


/*
 * Console name is marquee, main and memory
 * */

void ConsoleDriver::switchConsole(String consoleName)
{
    if (this->consoleTable.find(consoleName) != this->consoleTable.end()) {
        // system("cls");
        this->previousConsole = this->currentConsole;
        this->currentConsole = this->consoleTable[consoleName];
        this->currentConsole->onEnabled();
        // std::cerr << this->currentConsole->getName();
    }
    else 
    {
        std::cerr << "Console name " << consoleName << " not found. Was it initialized?" << std::endl;
    }
}

void ConsoleDriver::switchToScreen(String screenName)
{
    if (this->consoleTable.find(screenName) != this->consoleTable.end()) {
        // disables `Enter a command:` prompt within MainConsole when entering a screen
        this->mainConsole->setOutMain();
        this->previousConsole = this->currentConsole;
        this->currentConsole = this->consoleTable[screenName];
        this->currentConsole->onEnabled();
    }
    else {
        std::cerr << "Screen name " << screenName << " not found." << std::endl;
    }
}

void ConsoleDriver::returnToPreviousConsole()
{
    if (this->previousConsole != nullptr) {
        // Manages "Enter a command: " output from MainConsole within BaseScreen
        // might need to update this since it will do so for every return to console
        // in the future; such as MarqueeConsole and SchedulingConsole
        this->mainConsole->setInMain();

        this->switchConsole(this->previousConsole->getName());
        this->previousConsole = nullptr;
    }
}

/*
 * Handles going to menu? if inside a submenu and assings running to fase if inside a main console
 */

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

bool ConsoleDriver::isRunning() const
{
    return this->running;
}

// DEBUG purposes
void ConsoleDriver::printTest() const
{
    std::cerr << "printTest Function called" << std::endl;
}

ConsoleDriver::ConsoleDriver()
{
    this->running = true;

    this->consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    const std::shared_ptr<MainConsole> mainConsole = std::make_shared<MainConsole>();
    // const std::shared_ptr<MarqueeConsole> mainConsole = std::make_shared<MarqueeConsole>();
    // const std::shared_ptr<SchedulingConsole> mainConsole = std::make_shared<SchedulingConsole>();
    // const std::shared_ptr<MemorySimulationConsole> mainConsole = std::make_shared<MemorySimulationConsole>();

    this->consoleTable[MAIN_CONSOLE] = this->mainConsole;

    this->switchConsole(MAIN_CONSOLE);
}

