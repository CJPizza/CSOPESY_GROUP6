#include <memory>
#include <unordered_map>
#include <windows.h>
#include "AConsole.h"

class ConsoleDriver {
    public:
        typedef std::unordered_map<String, std::shared_ptr<AConsole>> ConsoleTable;

        static ConsoleDriver* getInstance();
        static void initialize();
        static void destroy();

        
    private:
        ConsoleDriver();
        ~ConsoleDriver() = default;
        ConsoleDriver(ConsoleDriver const&) {};
        ConsoleDriver& operator=(ConsoleDriver const&) {};
        static ConsoleDriver* sharedInstance;

        ConsoleTable consoleTable;
        std::shared_ptr<AConsole> currentConsole;
        std::shared_ptr<AConsole> previousConsole;

        HANDLE consoleHandle;
        bool running = true;

};
