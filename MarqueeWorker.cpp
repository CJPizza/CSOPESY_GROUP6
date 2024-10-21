#include <iostream>

#include "MarqueeWorker.h"
#include "ConsoleDriver.h"

void MarqueeWorker::printHeader()
{
  ConsoleDriver::getInstance()->setCursorPosition(0, 0);
  std::cerr << "*****************************************" << std::endl;
  std::cerr << "* Displaying a marquee console ! *" << std::endl;
  std::cerr << "*****************************************" << std::endl;
}


void MarqueeWorker::setDirX()
{
  if (this->x == XBOUNDS)
  {
    this->forward = false;
  }
  if (this->x == 0)
  {
    this->forward = true;
  }
  if (this->x < XBOUNDS && this->forward)
  {
    this->x = x + 1;
  }
  else if (this->x > 0 && !this->forward)
  {
    this->x = x - 1;
  }

}

void MarqueeWorker::setDirY()
{

  if (this->y == YBOUNDS_MIN)
  {
    this->up = false;
  }
  if (this->y == YBOUNDS_MAX)
  {
    this->up = true;
  }
  if (this->y > 0 && this->up)
  {
    this->y = this->y - 1;
  }
  else if (this->y < YBOUNDS_MAX && !this->up)
  {
    this->y = this->y + 1;
  }
}

void MarqueeWorker::printPromptHist()
{
  ConsoleDriver::getInstance()->setCursorPosition(0, YBOUNDS_MAX + 1); // sets at the prompt line
  std::cout << "Enter a command for MARQUEE_CONSOLE: ";
  std::cout << this->sInput;
  std::cout << this->commandHist;
  ConsoleDriver::getInstance()->setCursorPosition(this->xCursor, YBOUNDS_MAX + 1); // sets at the prompt line
}

void MarqueeWorker::run()
{
  while (running)
  {
    system("CLS");
    this->printHeader();
    ConsoleDriver::getInstance()->setCursorPosition(x, y);
    this->setDirX();
    this->setDirY();
    std::cout << "Hello world in marquee!";
    printPromptHist();

    Sleep(REFRESH_DELAY);
  }
}
