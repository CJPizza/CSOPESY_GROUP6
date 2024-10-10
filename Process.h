#pragma once
#include <string>
//
// TODO: Complete instruction counter and more...

class Process {
public:
    typedef std::string String;
    Process(String processName);
    const int uid;
    int getUid();
    String getProcessName() const;
    int getCurrentIL();
    int getLinesCode();
    void incrementInstruction();
private:
    String processName;
    int currentIL = 0;
    int linesCode = 100;
    static int newUID;
};

