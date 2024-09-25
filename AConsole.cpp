#include "AConsole.h"
#include "ConsoleDriver.h"

AConsole::AConsole(String consoleName) {
    this->name = consoleName;
}

String AConsole::getName()
{
    return this->name;
}
