#pragma once
#include <unordered_map>

#include "FCFSScheduler.h"
/*
 * This class would manage Process generation for scheduler-test and will select appropriate
 * scheduling method based on `config.txt`
 *
 */

class SchedulerManager {
    public:
        typedef std::unordered_map<String, int> config_kvs;
        SchedulerManager();
        ~SchedulerManager();

        void generateProcesses(); // generateProcesses needed for scheduler-test
        void stopGenerateProcesses(); //scheduler-stop
        int getMinIns();
        int getMaxIns();

    private:
        int cpu_cycle_count = 0; // current cpu cycle
        int num_cpus = 0; // number of logical cores
        int quantum_cycles = -1; // quantum cycle for round robin_scheduler; initially set to -1 in cases
                                 // where different scheduler will not utilize this
        int batch_process_freq; // 
        int min_ins; // minimum instruction per process
        int max_ins; // maximum instruction per process
        int delay_per_exec; // delay in ms per execution


        config_kvs config;

        FCFSScheduler* fcfs_scheduler; 
        /* 
         * Add for for different types of scheduler
         * */
};
