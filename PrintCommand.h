#pragma once
#include "ICommand.h"
#include <string>
class PrintCommand : public ICommand
{
    public:
        typedef std::string String;
        PrintCommand(int pid, String& to_print);
        void execute() override;
    private:
        String to_print;
};
