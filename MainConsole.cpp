#include <cstdio>
#include <iostream>
#include <memory>
#include <windows.h>
#include <sstream>
#include <string>

#include "MainConsole.h"
#include "BaseScreen.h"
#include "ConsoleDriver.h"
#include "Process.h"

MainConsole::MainConsole(): AConsole(MAIN_CONSOLE)
{
    this->name = MAIN_CONSOLE;
    this->consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void MainConsole::onEnabled()
{
    // if (this->commandHist.length() == 0) {
    //     loadHeaderToStr();
    // }

    this->display();
    /*
     * Calling ConsoleDriver::getInstance() within onEnabled() causes issue
     * for now HANDLE will be initialized here for terminal formatting
     */

    // ConsoleDriver::getInstance()->printTest();
    // ConsoleDriver::getInstance()->drawConsole();
}

void MainConsole::process() 
{
    
    // system("cls");
    String sInput;
    std::getline(std::cin, sInput);

    // Split the input into command and parameters
    std::stringstream s_in(sInput);
    String command, param, name;

    s_in >> command;
    s_in >> param;

    this->commandHist.append(command + " " + param);
    if (command == "initialize")
    {
        std::cerr << "initialize command recognized. Doing something.\n";
        this->commandHist.append("initialize command recognized. Doing something.\n");
        // std::cerr << "\n\nEnter a command: ";
    }
    else if (command == "screen")
    {
        if (param == "-s") {
            s_in >> name;
            //std::cerr << "screen -s command: " << name << std::endl;
            //screen -s <name> : creates then add to table then go to new screeen
            if (name.length() > 0) {
                this->commandHist.append(" " + name);
                std::shared_ptr<Process> newProcess = std::make_shared<Process>(name);
                std::shared_ptr<BaseScreen> newScreen = std::make_shared<BaseScreen>(newProcess, newProcess->getProcessName());
                ConsoleDriver::getInstance()->registerScreen(newScreen);
            }

        }
        else if (param == "-r") {
            // std::cerr << "screen -r command\n";
            //screen -r <name>: goes back to that same screen
            s_in >> name;
            if (name.length() > 0) {
                this->commandHist.append(" " + name);
                ConsoleDriver::getInstance()->switchToScreen(name);
            }
        }
        else if (param == "-ls") {
            std::cerr << "screen -ls command\n";
            this->commandHist.append("screen -ls command\n");
        }
        else {
            std::cerr << "Unknown command: " << param;
            this->commandHist.append("Unknown command: " + param);
            // std::cerr << "Enter a command: ";
        }
    }
    else if (command == "scheduler-test")
    {
        std::cerr << "scheduler-test command recognized. Doing something.\n";
        this->commandHist.append("\nscheduler-test command recognized. Doing something.\n");
        // std::cerr << "\n\nEnter a command: ";
    }
    else if (command == "scheduler-stop")
    {
        std::cerr << "scheduler-stop command recognized. Doing something.\n";
        // std::cerr << "\n\nEnter a command: ";
        this->commandHist.append("\nscheduler-stop command recognized. Doing something.\n");
    }
    else if (command == "report-util")
    {
        std::cerr << "report-util command recognized. Doing something.\n";
        // std::cerr << "\n\nEnter a command: ";
        this->commandHist.append("\nreport-util command recognized. Doing something.\n");
    }
    else if (command == "clear")
    {
        system("CLS");
        this->commandHist = "";
        this->onEnabled();
        return;
    }
    else if (command == "exit")
    {
        std::cerr << "exit command recognized. Exiting application.\n";
        ConsoleDriver::getInstance()->exitApplication();
        return;
    }
    else
    {
        std::cerr << "Unknown command.\n";
        this->commandHist.append("\nUnknown command.\n");
        // std::cerr << "Enter a command: ";
    }

    if (this->getInMain()){
        std::cerr << "\n\nEnter a command: ";
    }
    this->commandHist.append("\n\nEnter a command: ");
    // std::cerr << "\n\nEnter a command: ";
}    

void MainConsole::setInMain()
{
    this->inMain = true;
}

void MainConsole::setOutMain()
{
    this->inMain = false;
}

bool MainConsole::getInMain() const
{
    return this->inMain;
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
    HANDLE color = this->consoleHandle;
    SetConsoleTextAttribute(color, 10);
    std::cerr << "\n\nHello. Welcome to the CSOPESY Command Line!" << std::endl;
    SetConsoleTextAttribute(color, 14);
    std::cerr << "Type 'exit' to quit, 'clear' to clear the screen" << std::endl;
    SetConsoleTextAttribute(color, 7);
    std::cerr << "Enter a command: ";
    std::cerr << this->commandHist;
}
