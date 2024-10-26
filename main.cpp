#include <string>

#include "AConsole.h"
#include "ConsoleDriver.h"
#include "GlobalScheduler.h"
#include "Process.h"


typedef std::string String;

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
