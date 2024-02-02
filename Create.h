#include <bits/stdc++.h>

namespace Create {
std::vector<int> createIntVector(size_t length, bool sorted, bool revSorted, int lowerBound, int upperBound) {
    assert(length != std::string::npos);
    assert(lowerBound < upperBound);
    assert(sorted != revSorted || (sorted == false && revSorted == false));

    // Generate random numbers within the specified range

    std::vector<int> result;
    for (size_t i = 0; i < length; i++) {
        result.push_back(rand() % (upperBound - lowerBound + 1) + lowerBound);
    }

    // Sort the array if required
    if (sorted == true) {
        std::sort(result.begin(), result.end());
    } else if (revSorted == true) {
        std::sort(result.rbegin(), result.rend());
    }

    return result;
}

std::pair<int, int> createInterval(int lowerBound, int upperBound) {
    assert(lowerBound < upperBound);
    std::pair<int, int> result;
    result.first = rand() % (upperBound - lowerBound + 1) + lowerBound;
    result.second = rand() % (upperBound - lowerBound + 1) + lowerBound;
    if (result.first > result.second) {
        std::swap(result.first, result.second);
    }
    return result;
}

std::vector<std::pair<int, int>> createIntervalVector(size_t length, int lowerBound, int upperBound) {
    assert(length != std::string::npos);
    assert(lowerBound < upperBound);
    std::vector<std::pair<int, int>> result;
    for (size_t i = 0; i < length; i++) {
        result.push_back(createInterval(lowerBound, upperBound));
    }

    return result;
}

std::vector<std::vector<int>> createIntMatrix(size_t rows, size_t columns, bool rowsSorted, bool rowsRevSorted, int cellLowerBound, int cellUpperBound) {
    assert(rows != std::string::npos);
    assert(columns != std::string::npos);
    assert(cellLowerBound < cellUpperBound);
    assert(rowsSorted != rowsRevSorted || (rowsSorted == false && rowsRevSorted == false));

    std::vector<std::vector<int>> result;
    for (size_t i = 0; i < rows; i++) {
        result.push_back(createIntVector(columns, rowsSorted, rowsRevSorted, cellLowerBound, cellUpperBound));
    }

    return result;
}

std::string createString(size_t length, bool hasLowAlpha, bool hasUpAlpha, bool hasNums, bool hasSpecials, bool sorted) {
    assert(length != std::string::npos);

    std::vector<int> choices;
    if (hasLowAlpha == true) {
        choices.push_back(0);
    }
    if (hasUpAlpha == true) {
        choices.push_back(1);
    }
    if (hasNums == true) {
        choices.push_back(2);
    }
    if (hasSpecials == true) {
        choices.push_back(3);
    }

    std::string lowAlpha = "abcdefghijklmnopqrstuvwxyz";
    std::string upAlpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string specials = "!\"#$%&`()*+'-./:;<=>?@[\\]^_`{|}~";

    std::string result;
    for (size_t i = 0; i < length; i++) {
        int choice = choices[rand() % choices.size()];
        switch (choice) {
            case 0:
                result.push_back(lowAlpha[rand() % lowAlpha.size()]);
                break;

            case 1:
                result.push_back(upAlpha[rand() % upAlpha.size()]);
                break;

            case 2:
                result.push_back(rand() % 10 + '0');
                break;

            case 3:
                result.push_back(specials[rand() % specials.size()]);
                break;

            default:
                break;
        }
    }

    if (sorted == true) {
        std::sort(result.begin(), result.end());
    }

    return result;
}

};  // namespace Create
