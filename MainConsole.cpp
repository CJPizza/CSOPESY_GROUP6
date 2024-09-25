#include "MainConsole.h"
#include "ConsoleDriver.h"

#include <cstdio>
#include <iostream>

MainConsole::MainConsole(): AConsole("Main")
{
    this->name = "Main";
}

void MainConsole::onEnabled()
{
    this->display();
    // this->process();
}

void MainConsole::display()
{
    std::cerr << "  ____ ____   ___  ____  _____ ______   __";
    std::cerr << "\n";
    std::cerr << " / ___/ ___| / _ \\|  _ \\| ____/ ___\\ \\ / /";
    std::cerr << "\n";
    std::cerr << "| |   \\___ \\| | | | |_) |  _| \\___ \\\\ V / ";
    std::cerr << "\n";
    std::cerr << "| |___ ___) | |_| |  __/| |___ ___) || |";
    std::cerr << "\n";
    std::cerr << " \\____|____/ \\___/|_|   |_____|____/ |_|";
    std::cerr << "\n                  GROUP 6";
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    ConsoleDriver::getInstance()->getConsoleHandle().SetConsoleTextAttribute(color, 10);
    std::cerr << "\n\nHello. Welcome to the CSOPESY Command Line!" << std::endl;
    ConsoleDriver::getInstance()->getConsoleHandle().SetConsoleTextAttribute(color, 10);
    std::cerr << "Type 'exit' to quit, 'clear' to clear the screen" << std::endl;
    SetConsoleTextAttribute(color, 7);
    std::cerr << "Enter a command: ";
}

// void MainConsole::process() 
// {
//
// }
