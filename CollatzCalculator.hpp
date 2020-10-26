#pragma once
#ifndef __COP_COLLATZ_CALCULATOR__
#define __COP_COLLATZ_CALCULATOR__

#include <utility> // std::pair
#include <iostream>

class CollatzCalculator {
    public:
        CollatzCalculator() { };
        static std::pair<int,int> collatz(int n) {
            if(n == 0) {
                return std::make_pair(0,0);
            }
            size_t answer = n;
            int stoppingTime = 0;
            // std::cout << "Stepping into Collatz...\n";
            while(answer > 1) { // this does break if the number goes negative, but we would rather have a wrong answer than an infinite loop
                answer = (answer % 2) ? ((3 * answer) + 1) : (answer / 2);
                stoppingTime++;
            }
            // std::cout << "Leaving Collatz...\n";
            return std::make_pair(n, stoppingTime);
        };
};

#endif