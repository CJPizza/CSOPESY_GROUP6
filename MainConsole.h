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
    HANDLE console_handle;
    void printHeader() const;
    void lsUI() const;
    FCFSScheduler fcfs_scheduler = FCFSScheduler(4);
    std::vector<Process> processes;
private:
};
