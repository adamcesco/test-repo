#include <vector>
#include <random>
#include <algorithm>
#include <cassert>

namespace Create{
    std::vector<int> createVector(size_t length, bool sorted, int lowerBound, int upperBound) {
        assert(length != std::string::npos);
        assert(lowerBound < upperBound);
        
        // Generate random numbers within the specified range

        std::vector<int> result;
        for (size_t i = 0; i < length; i++) {
            result.push_back(rand() % (upperBound - lowerBound + 1) + lowerBound);
        }
        
        // Sort the array if required
        if (sorted == true) {
            std::sort(result.begin(), result.end());
        }
        
        return result;
    }
}; // namespace Create
