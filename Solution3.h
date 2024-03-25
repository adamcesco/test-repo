#ifndef THINKCELLASSIGNMENT_SOLUTION2_H
#define THINKCELLASSIGNMENT_SOLUTION2_H
#include <bits/stdc++.h>

// solution for the frog jump problem
namespace SOLUTION3 {

    // string numerical input
    std::string solution(const std::string& num){
        std::list<char> numList(num.begin(), num.end());
        auto prev = numList.end();
        auto iter = numList.begin();

        while(iter != numList.end()) {
            if (prev != numList.end() && *prev == *iter) {
                while(iter != numList.end() && *prev == *iter) {
                    iter++;
                }
                iter = numList.erase(prev, iter);
                prev = std::prev(iter);
            } else {
                prev = iter;
                iter = std::next(iter);
            }
        }

        return std::string(numList.begin(), numList.end());
    }

}

#endif