#pragma once
#include "ICommand.h"
#include <ctime>
#include <memory>
#include <string>
#include <vector>
//
// TODO: Complete instruction counter and more...

typedef std::string String;
class Process {
public:

    enum ProcessState
    {
        READY,
        RUNNING,
        WAITING,
        FINISHED
    };

    Process(String processName, int num_instrcution);

    int total_ins; // total instruction
    int   rem_ins; // remaining instruction

    int getUid() const;
    int getCpuID() const;
    // Instruction will be replaced by commands
    int getTotalInstruction() const;
    void executeInstruction();

    void executeCurrCommand() const;
    void moveToNextLine();


    String getProcessName() const;
    bool hasFinished() const;
    int getRemainingInstructions() const;
    void setCpuID(int core_id);
    String getTimeStartToStr() const;
    String getTimeEndToStr();
    void deleteFile();
    void createFile();

    void setFinished();
    void setRunning();
    ProcessState getCurrState();

private:
    inline static int new_uid = 0; 
    int uid; // unique ID which increments on its own so don't worry bout this
    tm time_stamp; // time this process was created
    tm time_finished; // time finished
    String name;
    typedef std::vector<std::shared_ptr<ICommand>> Commands;
    Commands command_list; // lists of command to exec
    // add vector of commandList for command processing

    int core_id = -1;
    int command_counter;
    ProcessState curr_state;

};
