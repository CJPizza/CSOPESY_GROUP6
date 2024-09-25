#include <iostream>
#include <sstream>
#include <string>

#include "AConsole.h"
#include "ConsoleDriver.h"


// void printHeader()
// {
//     std::cerr << "  __
//__   _  __  ___
//____   __";
//     std::cerr << "\n";
//     std::cerr << " / ___/ ___| / _ \\|  _ \\| ____/ ___\\ \\ / /";
//     std::cerr << "\n";
//     std::cerr << "| |   \\___ \\| | | | |_) |  | \\__ \\\\ V / ";
//     std::cerr << "\n";
//     std::cerr << "| |___ _) | |_| |  _/| |__
//_) || |";
//     std::cerr << "\n";
//     std::cerr << " \\____|____/ \\___/|_|   |_____|____/ |_|";
//     std::cerr << "\n                  GROUP 6";
//
//     HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
//     SetConsoleTextAttribute(color, 10);
//     std::cerr << "\n\nHello. Welcome to the CSOPESY Command Line!" << endl;
//     SetConsoleTextAttribute(color, 14);
//     std::cerr << "Type 'exit' to quit, 'clear' to clear the screen" << endl;
//     SetConsoleTextAttribute(color, 7);
//     std::cerr << "Enter a command: ";
// }
//

typedef std::string String;

// TODO: other classes when invoking ConsoleDriver::getInstance() seems to return a null_ptr 
// which causes issues i.e. HANDLE not being returned from ConsoleDriver causing it to crash
//
// void userInput(const String& sInput)
// {

//     // uses stringstream to slice input into substring
//     std::stringstream s_in(sInput);

//     String command;
//     String param;
//     String name;

//     // assumes command parameter will only be one use while loop if more than one
//     s_in >> command;
//     s_in >> param;

//     if (command == "initialize")
//     {
//         std::cerr << "initialize command recognized. Doing something.\n";
//         std::cerr << "\nEnter a command: ";
//     }

//     else if (command == "screen")
//     {
        
//         if (param == "-s") {
//             s_in >> name;
            

//         } else if (param == "-r") {
//             std::cerr << "screen -r command";

//         } else if (param =="-ls") {
//             std::cerr << "screen -ls command";
//         }
//         std::cerr << "\nEnter a command: ";
//     }

//     else if (command == "scheduler-test")
//     {
//         std::cerr << "scheduler-test command recognized. Doing something.\n";
//         std::cerr << "\nEnter a command: ";
//     }

//     else if (command == "scheduler-stop")
//     {
//         std::cerr << "scheduler-stop command recognized. Doing something.\n";
//         std::cerr << "\nEnter a command: ";
//     }

//     else if (command == "report-util")
//     {
//         std::cerr << "report-util command recognized. Doing something.\n";
//         std::cerr << "\nEnter a command: ";
//     }

//     else if (command == "clear")
//     {
//         system("CLS");
//         //print the thingy
//     }

//     else if (command == "exit")
//     {
//         std::cerr << "exit command recognized. Doing something.\n";
//         ConsoleDriver::getInstance()->exitApplication();
//         exit(0);
//     }

//     else
//     {
//         std::cerr << "Unknown command.";
//         std::cerr << "\n\nEnter a command: ";
//     }
// }

int main()
{	
    ConsoleDriver::initialize();

    String sInput;
    bool running = true;

    while (running)
    {
        
        // getline(std::cin, sInput);
        // userInput(sInput);
        ConsoleDriver::getInstance()->process(); 

        running = ConsoleDriver::getInstance()->isRunning();
    }

    ConsoleDriver::destroy();

    return 0;
}
