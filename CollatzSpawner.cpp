#include "CollatzSpawner.hpp"

CollatzSpawner::CollatzSpawner(int N, int T, bool noLock=false) {
    this->range = N;
    this->threadCount = T;
    this->counter = 2;
    this->noLock = noLock;

    // initialize map of frequencies to 0
    for (int i = 0; i <= MAX_STOPPING_ENTRIES; i++) {
        values.insert({i, 0});
    }
};

/**
 * @brief Helper function to handle locking & unlocking mutex in a thread. Takes a callback function
 */
template <typename Callback>
void CollatzSpawner::handleLock(std::mutex& mut, const Callback& func) {
    if (noLock) {
        // we don't want to use those fancy locks, we just want to run the code and be finished
        func();
        return;
    }
    while(true) {
        // try to lock the mutex; if we can lock it, we know we have exclusive access
        if (mut.try_lock()) {
            func();
            mut.unlock();
            break;
        }
    }
}

/**
 * @brief Code that each Thread will run. Calculates a Collatz number & adds entries to map
 */
void CollatzSpawner::threadCode() {
    while (counter <= range) {
        // get the number we need to calculate
        int currentVal = 0;

        // grab the value, increment for all . we need to lock it so that only we have access
        handleLock(currentLock, [&]() {
            currentVal = counter;
            counter++;
        });
        auto results = CollatzCalculator::collatz(currentVal);
        
        // update map with results
        handleLock(mapLock, [&]() {
            values.at(results.second)++;
        });
    }
}

std::map<int,int> CollatzSpawner::run() {
    // I can't use arrays, I don't remember how. vectors are all I know
    std::vector<std::thread> threads(threadCount); 
    for (size_t i = 0; i < threadCount; i++) {
        // we use emplace to construct the threads in place inside of the vector
        threads.emplace(threads.begin()+i, std::thread(&CollatzSpawner::threadCode, this));
    }
    
    // the main thread will exit if we don't tell it not to. join all threads if they are joinable
    for(int i = 0; i < threadCount; i++) {
        std::thread& t = threads.at(i);
        if(!t.joinable()) {
            throw "ERROR: Thread " + std::to_string(i) + " is not joinable!";
        } else {
            t.join();
        }
    }
    return values;
}
