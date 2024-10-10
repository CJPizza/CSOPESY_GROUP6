#pragma once
#include "AConsole.h"

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
private:
};
