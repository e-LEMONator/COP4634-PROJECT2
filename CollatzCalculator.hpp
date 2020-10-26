#pragma once
#ifndef __COP_COLLATZ_CALCULATOR__
#define __COP_COLLATZ_CALCULATOR__

#include <utility> // std::pair

class CollatzCalculator {
    public:
        CollatzCalculator() { };
        static std::pair<int,int> collatz(int n) {
            if(n == 0) {
                return std::make_pair(0,0);
            }
            int answer = n;
            int stoppingTime = 0;
            while(answer != 1) {
                answer = (answer % 2) ? ((3 * answer) + 1) : (answer / 2);
                stoppingTime++;
            }
            return std::make_pair(n, stoppingTime);
        };
};

#endif