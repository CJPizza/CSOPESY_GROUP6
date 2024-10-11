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
    // void loadHeaderToStr();
    HANDLE consoleHandle;
    void printHeader() const;
    void lsUI() const;
    FCFSScheduler fcfsscheduler = FCFSScheduler(4);
    std::vector<Process> processes;
private:
};
