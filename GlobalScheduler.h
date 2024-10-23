#pragma once

#include <memory>
#include <unordered_map>

#include "AScheduler.h"
#include "FCFSScheduler.h"
#include "SchedulerWorker.h"
/*
 * This class would manage Process generation for scheduler-test and will select appropriate
 * scheduling method based on `config.txt`
 */

class GlobalScheduler {
    public:
        typedef std::unordered_map<String, int> config_kvs;
        typedef std::unordered_map<String, std::shared_ptr<Process>> process_kvs;

        static GlobalScheduler* getInstance();
        static void initialize();
        static void destroy();
        void loadConfig(); // load config.txt
        void startScheduler() const;

        std::shared_ptr<Process> createUniqueProcess();
        void generateProcesses(); // generateProcesses needed for scheduler-test
        void addProcess(std::shared_ptr<Process> newProcess); // adds process to the selected scheduler
        std::shared_ptr<Process> findProcess(String process_name);

        String strProcessesInfo() const;

        SchedulerWorker& getSchedWorker();
        void tick(); // emulates CPU tick?
        
        int getDelayPerExec() const;
    private:
        GlobalScheduler() = default;
        ~GlobalScheduler() = default;
        GlobalScheduler(GlobalScheduler const&) {};
        GlobalScheduler& operator=(GlobalScheduler const&) {return *this;};
        static GlobalScheduler* sharedInstance;

        // process_kvs processes;

        AScheduler* scheduler;

        int num_cpu = 1; // number of logical cores
        int quantum_cycles = 0; // quantum cycle for round robin_scheduler; initially set to 0 in cases
                                 // where ROUND_ROBIN is not selected
        int batch_process_freq;  
        int min_ins; // minimum instruction per process
        int max_ins; // maximum instruction per process
        int delay_per_exec; // delay in ms per execution
        SchedulerWorker sched_worker;

        /* 
         * Prefix for string name generation for processes
         * when generating processes
         */
        String process_prefix = "Process_";
        int process_counter; // postfix for processes

        /*
         * config.txt values will be saved here; in a hashtable format
         * ex. config["num_cpu"] would access saved config to num_cpu.
         * keys for config:
         * num-cpu 
         * scheduler 
         * quantum_cycles
         * batch-process-freq 
         * min-ins
         * max-ins
         * delay-per-exec
         */

        /*
         * scheduler in `config` would be mapped accordingly
         * FCFS == 0
         * RR   == 1
         */
};
