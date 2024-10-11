#include "IETThread.h"
#include "Process.h"
#include <vector>
class FCFSSchedulerWorker : public IETThread {
public:
    FCFSSchedulerWorker(std::vector<Process> *processesToExecute, std::vector<Process> *finishedProcesses); 
    ~FCFSSchedulerWorker() = default;
    void run() override;
private:
    std::vector<Process> *processesToExecute;
    std::vector<Process> *finishedProcesses;
};
