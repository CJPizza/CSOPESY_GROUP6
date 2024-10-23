#pragma once
#include "AConsole.h"
#include "FCFSScheduler.h"

class MainConsole : public AConsole 
{
public:
    MainConsole();
    ~MainConsole() = default;
    void onEnabled() override;
    void process() override;
    void display() override;
    HANDLE console_handle;
    void printHeader() const;
    void lsUI() const;
    std::vector<Process> processes;
private:
    bool initialized = false; // checks if initialized command was called 
};
