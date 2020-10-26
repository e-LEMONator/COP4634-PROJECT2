#pragma once
#ifndef __COP_COLLATZ_CALCULATOR__
#define __COP_COLLATZ_CALCULATOR__

#include <utility> // std::pair
#include <iostream>

class CollatzCalculator {
    public:
        // this object has no state; it is basically a pseudo-namespace
        CollatzCalculator() { };
        
        // calculate the Collatz sequence for the given value; return the given value and the stopping time
        static std::pair<int,int> collatz(int n) {
            if(n == 0) {
                return std::make_pair(0,0);
            }
            size_t answer = n;
            int stoppingTime = 0;
            while(answer > 1) { // this does break if the number goes negative, but we would rather have a wrong answer than an infinite loop
                answer = (answer % 2) 
                    ? ((3 * answer) + 1)    // number is odd; 3 * n + 1
                    : (answer / 2);         // number is even; n / 2
                stoppingTime++;
            }
            return std::make_pair(n, stoppingTime);
        };
};

#endif