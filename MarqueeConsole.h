#pragma once
#include "AConsole.h"
#include "MarqueeWorker.h"

static constexpr int POLLING_DELAY = 10;


class MarqueeConsole : public AConsole
{
public:
    MarqueeConsole();
    ~MarqueeConsole() = default;

    void onEnabled() override;
    void process() override;
    void display() override;
    void pollKeyboard();

    String sInput = "";
    String commandHist = "";

    MarqueeWorker* workerThread = new MarqueeWorker();
private:
    bool running = false;
};

