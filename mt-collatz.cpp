#include "CollatzSpawner.hpp"

#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define MIN_ARGS 3
#define MAX_ARGS 4
#define BILLION 1e9

// converts an argument to an int if that argument is an int
// credit: https://stackoverflow.com/questions/2797813/how-to-convert-a-command-line-argument-to-int
int argToInt(char* arg) { 
    int r;
    std::istringstream ss(arg);   
    if (!(ss >> r || ss.eof())) {
        throw "Bad argument: " + std::string(arg);
    }
    return r;
}

void printUsage() {
    std::cout << "mt-collatz N T [-nolock]\n\n";
    std::cout << "\tN - Range of numbers for which a Collatz sequence must be computed.\n";
    std::cout << "\tT - the number of threads the program will create and launch.\n";
    std::cout << "\t-nolock - disable locking, allowing for race conditions.\n";
}

int main(int argc, char** args) {

    // Validate args input
    if (argc < MIN_ARGS || argc > MAX_ARGS) {
        std::cout << "ERROR: Incorrect # of arguments.\n";
        printUsage();
        exit(3);
    }

    // Collatz number
    int N;
    
    // thread count
    int T;

    // is -nolock in the args?
    bool noLock = argc >= 3 && args[3][0] == '-'; 

    std::cout << "noLock: " << (noLock ? "True" : "False") << "\n";

    try {
        N = argToInt(args[1]);
        T = argToInt(args[2]);
    } catch (const char* err) {
        std::cout << err << std::endl;
        exit(2);
    }

    CollatzSpawner spawner(N, T, noLock);

    // define time-related variables
    struct timespec start, end; 

    // start timer
    clock_gettime(CLOCK_REALTIME, &start);

    std::map<int,int> results;

    try {
        // run the Collatz calculations
        results = spawner.run();
    } catch (const char* err) {
        std::cerr << err << std::endl;
        exit(4);
    }

    // end the timer
    clock_gettime(CLOCK_REALTIME, &end);

    // calculate final time
    double timeSec = (end.tv_sec - start.tv_sec);
    double timeNan = (end.tv_nsec - start.tv_nsec);
    double time = timeSec + (timeNan / (1 * BILLION));

    // output in correct format
    for(auto& p : results) {
        std::cout << p.first << ", " << p.second << "\n";
    }

    std::cerr << N << ", ";
    std::cerr << T << ", ";
    std::cerr.precision(8);
    std::cerr << time << std::endl;
}