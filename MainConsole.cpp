#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <memory>
#include <windows.h>
#include <sstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

#include "MainConsole.h"
#include "BaseScreen.h"
#include "ConsoleDriver.h"
#include "GlobalScheduler.h"
#include "Process.h"

MainConsole::MainConsole(): AConsole(MAIN_CONSOLE)
{
  this->name = MAIN_CONSOLE;
  this->console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void MainConsole::onEnabled()
{
  // if (this->command_hist.length() == 0) {
  //     loadHeaderToStr();
  // }

  // this->display();
  /*
   * Calling ConsoleDriver::getInstance() within onEnabled() causes issue
   * for now HANDLE will be initialized here for terminal formatting
   */

  // ConsoleDriver::getInstance()->printTest();
  // ConsoleDriver::getInstance()->drawConsole();
  if (this->command_hist == "")
  {
    this->command_hist.append("Enter a command: ");
  }
  this->printHeader();
  // this->fcfsscheduler.runScheduler();
  //this->fcfs_scheduler.start();
}

void MainConsole::process() 
{
  // system("cls");
  String sInput;
  std::getline(std::cin, sInput);

  // Split the input into command and parameters
  std::stringstream s_in(sInput);
  String command, param, name, textfile;

  s_in >> command;
  s_in >> param;

  this->command_hist.append(command + " " + param);
  if (command == "initialize")
  {
    // if initialize is already called
    if (initialized)
    {
      std::cout << "Already initialized";
      command_hist.append("\nAlready initialized");
    }
    GlobalScheduler::getInstance()->loadConfig();
    GlobalScheduler::getInstance()->generateProcesses();
    GlobalScheduler::getInstance()->startScheduler();
    this->initialized = true;
    // DEBUG Purposes:
    return;
  }
  if (initialized) {
    if (command == "screen")
    {
      if (param == "-s") {
        s_in >> name;
        //std::cerr << "screen -s command: " << name << std::endl;
        //screen -s <name> : creates then add to table then go to new screeen
        /*
         * Creates a process then instantly executes using whatever scheduler selected in 
         * config.txt
         */
        if (name.length() > 0) {
          this->command_hist.append(" " + name);
          std::shared_ptr<Process> newProcess = std::make_shared<Process>(name, 0);
          // TODO: move BaseScreen as a member of MainConsole and at MainConsole constructor we add processes initialized here 
          // to BaseScreen as well.
          std::shared_ptr<BaseScreen> newScreen = std::make_shared<BaseScreen>(newProcess, newProcess->getProcessName());

          ConsoleDriver::getInstance()->registerScreen(newScreen);
          ConsoleDriver::getInstance()->switchToScreen(newProcess->getProcessName());
        }
      }
      else if (param == "-r") {
        // std::cerr << "screen -r command\n";
        //screen -r <name>: goes back to that same screen
        s_in >> name;
        if (name.length() > 0) {
          this->command_hist.append(" " + name);
          ConsoleDriver::getInstance()->switchToScreen(name);
          //return;
        }
      }
      else if (param == "-ls") {
        // std::cerr << "screen -ls command\n";
        // this->command_hist.append("screen -ls command\n");
        // String str_progress = this->fcfs_scheduler.strProgress();
        String str_progress = GlobalScheduler::getInstance()->strProcessesInfo();
        std::cerr << str_progress;
        this->command_hist.append("\n"+str_progress);
      }
      else {
        std::cerr << "Unknown command: " << param;
        this->command_hist.append("Unknown command: " + param);
        // std::cerr << "Enter a command: ";
      }
    }
    else if (command == "scheduler-test")
    {
      /* 
       * This would manage process generation
       */

    }
    else if (command == "scheduler-stop")
    {
      // std::cerr << "scheduler-stop command recognized. Doing something.\n";
      /* 
       * This would stop process creation
       */

    }
    // std::cerr << "\n\nEnter a command: ";
    // this->command_hist.append("\nscheduler-stop command recognized. Doing something.\n");

    else if (command == "report-util")
    {
      std::cerr << "report-util command recognized. Doing something.\n";
      // std::cerr << "\n\nEnter a command: ";
      this->command_hist.append("\nreport-util command recognized. Doing something.\n");
    }
    else if (command == "clear")
    {
      system("CLS");
      this->command_hist = "";
      this->printHeader();
      return;
    }
    else if (command == "marquee")
    {

      ConsoleDriver::getInstance()->switchConsole(MARQUEE_CONSOLE);
    }
    else {
      std::cerr << "Unknown command: " << param;
      this->command_hist.append("Unknown command: " + param);
      // std::cerr << "Enter a command: ";
    }
  }
  if (command == "exit")
  {
    std::cerr << "exit command recognized. Exiting application.\n";
    ConsoleDriver::getInstance()->exitApplication();
    return;
  }
  else
  {
    if(!initialized)
    {
      std::cerr << "Unknown command: " << param;
      this->command_hist.append("Unknown command: " + param);
    }

    // std::cerr << "Unknown command.\n";
    // this->command_hist.append("\nUnknown command.\n");
    // std::cerr << "Enter a command: ";
  }

  //this->command_hist.append("\nEnter a command: ");
  // std::cerr << "\n\nEnter a command: ";
}

void MainConsole::display()
{
  std::cerr << "\nEnter a command: ";
  this->command_hist.append("\nEnter a command: ");
}

void MainConsole::printHeader() const
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
  HANDLE color = this->console_handle;
  SetConsoleTextAttribute(color, 10);
  std::cerr << "\n\nHello. Welcome to the CSOPESY Command Line!" << std::endl;
  SetConsoleTextAttribute(color, 14);
  std::cerr << "Type 'exit' to quit, 'clear' to clear the screen" << std::endl;
  SetConsoleTextAttribute(color, 7);
  // std::cerr << "Enter a command: ";
  std::cerr << this->command_hist;
}

void MainConsole::lsUI() const
{
  std::cout << "------------------------------------------" << std::endl;
  std::cout << "Running processes: " << std::endl;

}
