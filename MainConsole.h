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
    void setInMain();
    void setOutMain();
    bool getInMain() const;
    HANDLE consoleHandle;
private:
    bool inMain = true;
};
