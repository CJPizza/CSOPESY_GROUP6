#pragma once

#include <unordered_map>

#include "AScheduler.h"
#include "FCFSScheduler.h"
/*
 * This class would manage Process generation for scheduler-test and will select appropriate
 * scheduling method based on `config.txt`
 */

class GlobalScheduler {
    public:
        typedef std::unordered_map<String, int> config_kvs;

        static GlobalScheduler* getInstance();
        static void initialize();
        static void destroy();

        void generateProcesses(); // generateProcesses needed for scheduler-test
        void addProcess(std::shared_ptr<Process> newProcess); // adds process to the selected scheduler
        void loadConfig(); // load config.txt
        void findProcess(String process_name);


        void tick(); // emulates CPU tick?
    private:
        GlobalScheduler();
        ~GlobalScheduler() = default;
        GlobalScheduler(GlobalScheduler const&) {};
        GlobalScheduler& operator=(GlobalScheduler const&) {return *this;};
        static GlobalScheduler* sharedInstance;

        AScheduler* scheduler;

        // int num_cpus = 0; // number of logical cores
        // int quantum_cycles = -1; // quantum cycle for round robin_scheduler; initially set to -1 in cases
        //                          // where different scheduler will not utilize this
        // int batch_process_freq;  
        // int min_ins; // minimum instruction per process
        // int max_ins; // maximum instruction per process
        // int delay_per_exec; // delay in ms per execution

        config_kvs config;
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

        // FCFSScheduler* fcfs_scheduler; 
        /* 
         * Add for for different types of scheduler
         * */
};
