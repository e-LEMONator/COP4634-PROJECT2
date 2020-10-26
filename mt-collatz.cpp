#include "CollatzSpawner.hpp"

#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define MIN_ARGS 3
#define MAX_ARGS 4
#define BILLION 1e9

int argToInt(char* arg) { // credit: https://stackoverflow.com/questions/2797813/how-to-convert-a-command-line-argument-to-int
    int r;
    std::istringstream ss(arg);   
    if (!(ss >> r || ss.eof())) {
        throw "Bad argument: " + std::string(arg);
    }
    return r;
}

void printUsage() {
    std::cout << "Usage message goes here.\n";
}

int main(int argc, char** args) {
    if (argc < MIN_ARGS || argc > MAX_ARGS) {
        std::cout << "ERROR: Incorrect # of arguments.\n";
        printUsage();
        exit(3);
    }
    int N;
    int T;
    bool noLock = argc >= 3 && args[3] == "-nolock";
    try {
        N = argToInt(args[1]);
        T = argToInt(args[2]);
    } catch (const char* err) {
        std::cout << err << std::endl;
        exit(2);
    }
    CollatzSpawner spawner(N, T, noLock);
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    auto results = spawner.run();
    clock_gettime(CLOCK_REALTIME, &end);
    double timeSec = (end.tv_sec - start.tv_sec);
    double timeNan = (end.tv_nsec - start.tv_nsec);
    double time = timeSec + (timeNan / (1 * BILLION));
    for(auto& p : results) {
        std::cout << p.first << ", " << p.second << "\n";
    }
    std::cerr << N << ", ";
    std::cerr << T << ", ";
    std::cerr.precision(8);
    std::cerr << time << std::endl;
}