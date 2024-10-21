#include <iostream>

#include "ConsoleDriver.h"
#include "MainConsole.h"
#include "AConsole.h"
#include "BaseScreen.h"

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
    return this->console_handle;
}

void ConsoleDriver::drawConsole() const
{
    if (this->curr_console != nullptr) {
        this->curr_console->display();
    }
    else
    {
        std::cerr << "There is no assigned console. Please check." << std::endl;
    }
}


void ConsoleDriver::process() const
{
    if (this->curr_console != nullptr) {
        this->curr_console->process();
    }
    else {
        std::cerr << "There is no assigned console. Please check." << std::endl;
    }
}

void ConsoleDriver::registerScreen(std::shared_ptr<BaseScreen> screenRef)
{
    if (this->console_table.find(screenRef->getName()) != this->console_table.end())
    {
        std::cerr << "Screen name " << screenRef->getName() << " already exists. Please use a different name." << std::endl;
        this->curr_console->command_hist.append("\nScreen name " + screenRef->getName() + " already exists. Please use a different name.\n");
        return;
    }
    this->console_table[screenRef->getName()] = screenRef;
    this->switchToScreen(screenRef->getName());
}

void ConsoleDriver::unregisterScreen(String screenName) 
{
    if (this->console_table.find(screenName) != this->console_table.end()) {
        this->console_table.erase(screenName);
    }
    else {
        std::cerr << "Unable to unregister " << screenName << std::endl;
        this->curr_console->command_hist.append("\nUnable to unregister " + screenName + "\n");
    }
}

/*
 * Console name is marquee, main and memory
 * */

void ConsoleDriver::switchConsole(String consoleName)
{
    if (this->console_table.find(consoleName) != this->console_table.end()) {
        // system("cls");
        this->prev_console = this->curr_console;
        this->curr_console = this->console_table[consoleName];
        this->curr_console->onEnabled();
        // std::cerr << this->curr_console->getName();
    }
    else 
    {
        std::cerr << "Console name " << consoleName << " not found. Was it initialized?" << std::endl;
        this->curr_console->command_hist.append("\nConsole name "+consoleName+" not found. Was it initialized?\n");
    }
}

void ConsoleDriver::switchToScreen(String screenName)
{
    if (this->console_table.find(screenName) != this->console_table.end()) {
        system("cls");
        this->prev_console = this->curr_console;
        this->curr_console = this->console_table[screenName];
        this->curr_console->onEnabled();
    }
    else {
        std::cerr << "Screen name " << screenName << " not found." << std::endl;
        this->curr_console->command_hist.append("\nScreen name " + screenName + " not found.\n");
    }
}

void ConsoleDriver::returnToPreviousConsole()
{
    if (this->prev_console != nullptr) {
        this->switchConsole(this->prev_console->getName());
        this->prev_console = nullptr;
    }
}

/*
 * Handles going to menu? if inside a submenu and assings irunning to fase if inside a main console
 */

void ConsoleDriver::exitApplication() 
{
    if (this->prev_console == nullptr) {
        this->running = false;
    }
    else {
        this->curr_console = this->prev_console;
        this->prev_console = nullptr;
    }
}

bool ConsoleDriver::isRunning() const
{
    return this->running;
}


void ConsoleDriver::setCursorPosition(int posX, int posY) const
{
    COORD coord;
    coord.X = posX;
    coord.Y = posY;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

ConsoleDriver::ConsoleDriver()
{
    this->running = true;

    //const std::shared_ptr<MainConsole> main_console = std::make_shared<MainConsole>();
    // const std::shared_ptr<MarqueeConsole> main_console = std::make_shared<MarqueeConsole>();
    // const std::shared_ptr<SchedulingConsole> main_console = std::make_shared<SchedulingConsole>();
    // const std::shared_ptr<MemorySimulationConsole> main_console = std::make_shared<MemorySimulationConsole>();

    // For MarqueeConsole demo disable MAIN_CONSOLE atm
    this->console_table[MAIN_CONSOLE] = this->main_console;
    this->console_table[MARQUEE_CONSOLE] = this->marquee_console;

    // For MarqueeConsole demo disable MAIN_CONSOLE atm
    // this->switchConsole(MAIN_CONSOLE);
    this->switchConsole(MAIN_CONSOLE);
}

