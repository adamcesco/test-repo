#include <bits/stdc++.h>

namespace Create {
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
