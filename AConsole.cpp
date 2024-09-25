#include "AConsole.h"
#include "ConsoleDriver.h"

AConsole::AConsole(String consoleName) {
    this->name = consoleName;
}

AConsole::String AConsole::getName()
{
    return this->name;
}
