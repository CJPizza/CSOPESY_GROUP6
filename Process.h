#pragma once
#include <string>
//
// TODO: Complete instruction counter and more...

class Process {
public:
    typedef std::string String;

    enum ProcessState
    {
        READY,
        RUNNING,
        WAITING,
        FINISHED
    };

    Process(String processName, int numInstrcution);

    //Process(String processName, );
	// Process(const Process& other) = default; // Use default if possible
	// Process& operator=(const Process& other) = default;

    int totalInstruction;
    int remainingInstruction;

    int getUid() const;
    void executeInstruction();
    String getProcessName() const;
<<<<<<< Updated upstream
    int getCurrentIL();
    int getLinesCode();
    void incrementInstruction();
private:
    String processName;
    int currentIL = 0;
    int linesCode = 100;
=======
    bool hasFinished() const;
    int getRemainingInstructions() const;

private:
    String processName;
    int cpuCoreID = -1;
    int commandCounter;
>>>>>>> Stashed changes
    static int newUID;
    int uid;
};

