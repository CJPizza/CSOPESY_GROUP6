#pragma once

#include "IETThread.h"

class ICommand
{
    public:
        enum CommandType {
            IO, 
            PRINT
        };

        ICommand(int pid, CommandType command_type);
        CommandType getCommandType();
        virtual void execute();

    protected:
        int pid;
        CommandType command_type;
};

inline ICommand::CommandType ICommand::getCommandType()
{
    return this-> command_type;
}
