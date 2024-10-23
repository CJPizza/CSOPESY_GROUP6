#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "AConsole.h"
#include "ConsoleDriver.h"
#include "GlobalScheduler.h"
#include "Process.h"


typedef std::string String;

// TODO: other classes when invoking ConsoleDriver::getInstance() seems to return a null_ptr 
// which causes issues i.e. HANDLE not being returned from ConsoleDriver causing it to crash

int main()
{	
  ConsoleDriver::initialize();
  GlobalScheduler::initialize();

  String sInput;
  bool running = true;

  while (running)
  {
    ConsoleDriver::getInstance()->process(); 
    ConsoleDriver::getInstance()->drawConsole();

    running = ConsoleDriver::getInstance()->isRunning();
  }

  ConsoleDriver::destroy();
  GlobalScheduler::destroy();

  return 0;
}
