#pragma once
#include <windows.h>
#include <string>

#include "IETThread.h"

static constexpr int REFRESH_DELAY = 15;

static constexpr int XBOUNDS = 120;
static constexpr int YBOUNDS_MAX = 25;
static constexpr int YBOUNDS_MIN = 3;
static constexpr int PROMPT_XCURSOR = 37;


//class IKeyboardEvent 
//{
//    public:
//        virtual void OnKeyDown(char key) = 0;
//        virtual void OnKeyUp(char key) = 0;
//};
//
//class KeyboardEventHandler : public IKeyboardEvent 
//{
//    public:
//        void OnKeyDown(char key) override;
//        void OnKeyUp(char key) override;
// 
//};

class MarqueeWorker : public IETThread
{
  public:
    typedef std::string String;
    MarqueeWorker() = default;
    ~MarqueeWorker() = default;

    void setDirX();
    void setDirY();
    void run() override;

    String commandHist = "";
    String sInput = "";

    int x = 1;
    int y = YBOUNDS_MIN + 1;
    int xCursor = PROMPT_XCURSOR; // xCoord for cursor after printing prompt
    bool forward = true;
    bool running = true;
    bool up = false;

    void printHeader();
    void printPromptHist();
  private:
};
