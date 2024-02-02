#ifndef THINKCELLASSIGNMENT_SOLUTION_H
#define THINKCELLASSIGNMENT_SOLUTION_H
#include <bits/stdc++.h>

// solution for the anagram problem
namespace SOLUTION {

// ------- SECTION FOR BRUTE FORCE SOLUTION -------
void permute(std::vector<std::string>& perms, std::string& a, int l, int r) {
    if (l == r)
        perms.push_back(a);
    else {
        // Permutations made
        for (int i = l; i <= r; i++) {
            // Swapping done
            std::swap(a[l], a[i]);

            // Recursion called
            permute(perms, a, l + 1, r);

            // backtrack
            std::swap(a[l], a[i]);
        }
    }
}

bool isValid(std::string str) {
    std::string vowels = "AEIOU";
    if (vowels.find_first_of(str[0]) != std::string::npos) {
        return false;
    }

    for (size_t i = 1; i < str.size(); i++) {
        if (vowels.find_first_of(str[i]) == std::string::npos && vowels.find_first_of(str[i - 1]) == std::string::npos) {
            return false;
        }

        if (vowels.find_first_of(str[i]) != std::string::npos && vowels.find_first_of(str[i - 1]) != std::string::npos) {
            return false;
        }
    }
    return true;
}

int bruteForceSolution(std::string val) {
    std::vector<std::string> perms;
    permute(perms, val, 0, val.size() - 1);

    // remove duplicate strings from perms
    std::sort(perms.begin(), perms.end());
    perms.erase(std::unique(perms.begin(), perms.end()), perms.end());

    int ans = 0;
    for (std::string& perm : perms) {
        if (isValid(perm)) {
            ans++;
        }
    }
    return ans;
}

int optimizedSolution(std::string s) {
    std::unordered_map<char, int> charMap;
    int vowelCount = 0;
    int consonantCount = 0;

    for (char ch: s) {
        charMap.emplace(ch, 0).first->second++;

        if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') {
            vowelCount++;
        }
        else{
            consonantCount++;
        }
    }
    
    if (consonantCount != vowelCount + 1 && consonantCount != vowelCount) {
        return 0;
    }

    int MOD =  1e9 + 7;
    std::vector<long> factorials = {
        1,
        1,
        2,
        6,
        24,
        120,
        720,
        5040,
        40320,
        362880,
        3628800,
        39916800,
        479001600,
        6227020800,
        87178291200,
        1307674368000,
        20922789888000
    };

    int factorialsOfAllLetters = 1;
    for (auto ch : charMap) {
        factorialsOfAllLetters = (factorialsOfAllLetters * factorials[ch.second]) % MOD;
    }

    int factorialsOfCounts = factorials[consonantCount] % MOD;
    factorialsOfCounts = (factorialsOfCounts * factorials[vowelCount]) % MOD;
    return factorialsOfCounts / factorialsOfAllLetters;
}

};  // namespace SOLUTION

#endif