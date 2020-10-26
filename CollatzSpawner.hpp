#pragma once
#ifndef __COP_COLLATZ_SPAWNER__
#define __COP_COLLATZ_SPAWNER__

#include "CollatzCalculator.hpp"

#include <map>      // std::map
#include <mutex>    // std::mutex
#include <string>   // std::string
#include <thread>   // std::thread
#include <utility>  // std::pair
#include <vector>   // std::vector

#define MAX_STOPPING_ENTRIES 1000

class CollatzSpawner {
    private:
        int range;
        int threadCount;
        size_t counter;
        bool noLock;
        std::mutex currentLock;
        std::mutex mapLock;
        std::map<int,int> values;
        void threadCode();
        template<typename Callback>
        void handleLock(std::mutex&, const Callback&);
    public:
        CollatzSpawner(int N, int T, bool noLock);
        std::map<int,int> run();
};

#endif