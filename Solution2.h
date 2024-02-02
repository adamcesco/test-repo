#ifndef THINKCELLASSIGNMENT_SOLUTION2_H
#define THINKCELLASSIGNMENT_SOLUTION2_H
#include <bits/stdc++.h>

namespace SOLUTION2 {

// ------- SECTION FOR BRUTE FORCE SOLUTION -------
int bruteForceSolution(std::vector<int> blocks) {
    int n = blocks.size();
    int result = 0;
    for (int i = 0; i < n; i++) {
        int left = i;
        int right = i;
        while(left > 0) {
            if (blocks[left - 1] >= blocks[left]) {
                left--;
            } else {
                break;
            }
        }
        while(right < n - 1) {
            if (blocks[right + 1] >= blocks[right]){
                right++;
            } else {
                break;
            }
        }
        result = std::max(result, right - left + 1);
    }
    return result;
}

int optimizedSolution(std::vector<int> blocks) {
    int n = blocks.size();
    int ans = 0;
    int currentDistance = 0;
    int prevHeight = blocks[0];
    int equalityCounter = 1;
    bool wasIncreasing = false;
    for (int i = 1; i < n; i++) {
        if (prevHeight == blocks[i]) {
            ++currentDistance;
            ++equalityCounter;
            prevHeight = blocks[i];
            continue;
        }
        
        if (prevHeight < blocks[i]) {
            ++currentDistance;
            wasIncreasing = true;
        } else if (wasIncreasing == true) {
            ans = std::max(ans, currentDistance + 1);
            currentDistance = equalityCounter;
            wasIncreasing = false;
        } else {
            ++currentDistance;
        }

        equalityCounter = 1;
        prevHeight = blocks[i];
    }

    return std::max(ans, currentDistance + 1);
}

}

#endif