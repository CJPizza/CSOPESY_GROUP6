#pragma once
#include <ctime>
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
    bool hasFinished() const;
    int getRemainingInstructions() const;
    void setCpuID(int coreID);
    int getTotalInstruction() const;

private:
    tm timeStamp; // time this process was created
    String processName;
    int cpuCoreID = -1;
    int commandCounter;
    static int newUID; 
    int uid; // unique ID which increments on its own so don't worry bout this
};

