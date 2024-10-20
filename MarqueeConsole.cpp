#include <string>
#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <conio.h>

#include "MarqueeConsole.h"
#include "AConsole.h"
#include "ConsoleDriver.h"


MarqueeConsole::MarqueeConsole() : AConsole(MARQUEE_CONSOLE)
{
}

void MarqueeConsole::onEnabled()
{
    this->workerThread->start();
	this->workerThread->running = true;
    this->running = true;
}

void MarqueeConsole::display()
{
}

void MarqueeConsole::process()
{
    this->pollKeyboard();
}

void MarqueeConsole::pollKeyboard()
{
    while (this->running) {

		if (_kbhit()) {
			char key = _getch(); // Get the pressed key

			// Handle key press for command entry
			if (key == '\r' || key == '\n') {
				if (workerThread->sInput == "exit") {
					this->running = false;
					workerThread->running = false;
					ConsoleDriver::getInstance()->returnToPreviousConsole();
					workerThread->sInput.clear();
					workerThread->xCursor = PROMPT_XCURSOR;
				}
				else {
					workerThread->commandHist += "\nCommand processed in MARQUEE_CONSOLE: " + workerThread->sInput;
				}
				workerThread->sInput.clear(); // Clear input after processing
				workerThread->xCursor = PROMPT_XCURSOR;
			}
			else if ((key == 127 || key == 8) && workerThread->xCursor > 37) { // Backspace handling
				if (!workerThread->sInput.empty()) {
					workerThread->sInput.pop_back();
					workerThread->xCursor = workerThread->xCursor - 1;
				}
			}
			else {
				workerThread->sInput += key; // Append the character to input
				workerThread->xCursor = workerThread->xCursor + 1;
			}
		}
		Sleep(POLLING_DELAY); 
	}
}

