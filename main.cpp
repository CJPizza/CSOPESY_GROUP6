#include <iostream>
#include <sstream>
#include <string>

#include "AConsole.h"
#include "ConsoleDriver.h"


typedef std::string String;

// TODO: other classes when invoking ConsoleDriver::getInstance() seems to return a null_ptr 
// which causes issues i.e. HANDLE not being returned from ConsoleDriver causing it to crash

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
