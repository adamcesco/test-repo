#ifndef THINKCELLASSIGNMENT_SOLUTION_H
#define THINKCELLASSIGNMENT_SOLUTION_H
#include <bits/stdc++.h>

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

// This is code is contributed by rathbhupendra

// ------- SECTION FOR OPTIMIZED SOLUTION -------
int optimizedSolution(std::string S) {
    // count the amount of unique consonants
    std::unordered_set<char> consonants;
    std::unordered_set<char> vowels;
    std::unordered_map<int, int> factorials = {
        {1, 1},
        {2, 2},
        {3, 6},
        {4, 24},
        {5, 120},
        {6, 720},
        {7, 5040},
        {8, 40320},
        {9, 362880},
        {10, 3628800},
        {11, 39916800},
        {12, 479001600},
        {13, 6227020800},
        {14, 87178291200},
        {15, 1307674368000},
        {16, 20922789888000}};
    int totalConsonants = 0;
    int totalVowels = 0;
    for (char c : S) {
        if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            vowels.insert(c);
            ++totalVowels;
        } else {
            consonants.insert(c);
            ++totalConsonants;
        }
    }

    if (totalVowels > totalConsonants || totalConsonants > totalVowels + 1) {
        return 0;
    }

    if (totalConsonants == consonants.size()) {
        return factorials[consonants.size()] * factorials[vowels.size()];
    }

    return totalConsonants * totalVowels;
    // return factorials[consonants.size()] * totalVowels;
}

#define ll long long
#define mod 1000000007
#define N 1000001
using namespace std;

// Function to compute factorials till N
void Precomputefact(unordered_map<ll, ll>& fac) {
    ll ans = 1;

    // Iterate in the range [1, N]
    for (ll i = 1; i <= N; i++) {
        // Update ans to ans*i
        ans = (ans * i) % mod;

        // Store the value of ans
        // in fac[i]
        fac[i] = ans;
    }
    return;
}

// Function to check whether the
// current character is a vowel or not
bool isVowel(char a) {
    if (a == 'A' || a == 'E' || a == 'I' || a == 'O' || a == 'U')
        return true;
    else
        return false;
}

// Function to count the number of
// anagrams of S satisfying the
// given condition
int countAnagrams(string s) {
    int n = s.size();
    // Store the factorials upto N
    unordered_map<ll, ll> fac;

    // Function Call to generate
    // all factorials upto n
    Precomputefact(fac);

    // Create a hashmap to store
    // frequencies of all characters
    unordered_map<char, ll> count;

    // Store the count of
    // vowels and consonants
    int vo = 0, co = 0;

    // Iterate through all
    // characters in the string
    for (int i = 0; i < n; i++) {
        // Update the frequency
        // of current character
        count[s[i]]++;

        // Check if the character
        // is vowel or consonant
        if (isVowel(s[i]))
            vo++;
        else
            co++;
    }

    // Check if ?C==?V+1 or ?C==?V
    if ((co == vo + 1) || (co == vo)) {
        // Store the denominator
        ll deno = 1;

        // Calculate the denominator
        // of the expression
        for (auto c : count) {
            // Multiply denominator by factorial
            // of counts of all letters
            deno = (deno * fac[c.second]) % mod;
        }

        // Store the numerator
        ll nume = fac[co] % mod;
        nume = (nume * fac[vo]) % mod;

        // Store the answer by dividing
        // numerator by denominator
        ll ans = nume / deno;

        // Print the answer
        return ans;
    }

    // Otherwise, print 0
    else {
       return 0;
    }
}

};  // namespace SOLUTION

#endif