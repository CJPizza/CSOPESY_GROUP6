#include "SchedulerWorker.h"
#include "Process.h"
#include <mutex>

void SchedulerWorker::run()
{
    while(execute)
    {
        /* 
         * lock to prevent racing when storing finished processes in 
         * finished_processes
         */
        std::unique_lock<std::mutex> lock(*mtx);
        this->running = true;
        for (auto& process : this->processes_to_exec) {
            process.setCpuID(this->core_id);
            while(!process.hasFinished()) {
                process.executeInstruction();
            }
            // When process is done
            process.setCpuID(this->core_id);
            // erase from process_to_exec or process_queues[ith_core];
            this->finished_processes.push_back(process);
            this->processes_to_exec.erase(this->processes_to_exec.begin());
        }   
        lock.unlock();
        this->running = false;
        IETThread::sleep(1);
    }
}

bool SchedulerWorker::isRunning() const
{
    return this->running;
}

void SchedulerWorker::stop()
{
    this->execute = false;
}

SchedulerWorker::SchedulerWorker(std::vector<Process>& processes_to_exec, std::vector<Process>& finished_processes) 
    : processes_to_exec(processes_to_exec), finished_processes(finished_processes), core_id(new_id++) {
        this->mtx = std::make_unique<std::mutex>();
    }
