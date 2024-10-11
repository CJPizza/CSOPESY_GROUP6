#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <windows.h>
#include <memory>

#include "BaseScreen.h"
#include "MainConsole.h"
#include "MarqueeConsole.h"

typedef std::string String;
const String MAIN_CONSOLE = "MAIN_CONSOLE";
const String MARQUEE_CONSOLE = "MARQUEE_CONSOLE";
const String SCHEDULER_CONSOLE = "SCHEDULER_CONSOLE";

class ConsoleDriver {
    public:
        typedef std::string String;
        typedef std::unordered_map<String, std::shared_ptr<AConsole>> ConsoleTable;

        static ConsoleDriver* getInstance();
        static void initialize();
        static void destroy();

        void drawConsole() const;
        void process() const;

        void registerScreen(std::shared_ptr<BaseScreen> screenRef);
        void switchToScreen(String screenName);
        void unregisterScreen(String screenName);

        void switchConsole(String screenName);
        void returnToPreviousConsole(); 

        void setCursorPosition(int posX, int posY) const;

        void exitApplication();
        bool isRunning() const;

        HANDLE getConsoleHandle() const;

        // DEBUG PURPOSES
        // void printTest() const;
        
    private:
        ConsoleDriver();
        ~ConsoleDriver() = default;
        ConsoleDriver(ConsoleDriver const&) {};
        ConsoleDriver& operator=(ConsoleDriver const&) {return *this;};
        static ConsoleDriver* sharedInstance;

        ConsoleTable consoleTable;
        std::shared_ptr<AConsole> currentConsole;
        std::shared_ptr<AConsole> previousConsole;
        //
        const std::shared_ptr<MainConsole> mainConsole = std::make_shared<MainConsole>();
        const std::shared_ptr<MarqueeConsole> marqueeConsole = std::make_shared<MarqueeConsole>();

        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        bool running = true;
};
