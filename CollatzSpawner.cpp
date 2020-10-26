#include "CollatzSpawner.hpp"

CollatzSpawner::CollatzSpawner(int N, int T, bool noLock=false) {
    this->range = N;
    this->threadCount = T;
    this->counter = 2;
    this->noLock = noLock;

    for (int i = 0; i <= MAX_STOPPING_ENTRIES; i++) {
        values.insert({i, 0});
    }
};

/**
 * @brief Helper function to handle locking & unlocking mutex in a thread. Takes a callback function
 */
template <typename Callback>
void CollatzSpawner::handleLock(std::mutex& mut, const std::string& tID, const Callback& func) {
    if (noLock) {
        func();
        return;
    }
    while(true) {
        if (mut.try_lock()) {
            func();
            mut.unlock();
            break;
        }
    }
    // func();
    // mut.unlock();
}

void CollatzSpawner::threadCode(const std::string& tID) {
    std::cout << "Thread " << tID << "\n";
    while (counter <= range) {
        // get the number we need to calculate
        int currentVal = 0;
        handleLock(currentLock, tID, [&]() {
            currentVal = counter;
            counter++;
        });
        auto results = CollatzCalculator::collatz(currentVal);
        handleLock(mapLock, tID, [&]() {
            // values.insert({results.first, results.second});
            values.at(results.second)++;
        });
    }
    std::terminate();
}

std::map<int,int> CollatzSpawner::run() {
    std::vector<std::thread> threads(threadCount); // I can't use arrays, I don't remember how. vectors are all I know
    int t_counter = 0;
    // for (auto& t : threads) {
    //     std::cout << "Creating new thread..." << std::endl;
    //     t = std::thread(&CollatzSpawner::threadCode, this, std::to_string(t_counter)); // start the thread
    //     t.join(); // wait for all of the threads to finish
    //     t_counter++;
    // }
    for (size_t i = 0; i < threadCount; i++) {
        threads.emplace(threads.begin()+i, std::thread(&CollatzSpawner::threadCode, this, std::to_string(t_counter)));
        // threads.at(i).join();
        t_counter++;
    }
    std::cout << "Size: " << threads.size() << std::endl;
    for(size_t i = 0; i < threadCount; i++) {
        std::thread& t = threads.at(i);
        if(!t.joinable()) {
            std::cout << "Thread " << i << " is not joinable!\n";
        } else {
            t.join();
        }
    }
    return values;
}