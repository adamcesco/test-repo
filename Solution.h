#ifndef THINKCELLASSIGNMENT_SOLUTION_H
#define THINKCELLASSIGNMENT_SOLUTION_H
#include <bits/stdc++.h>

#include "Stuff3.h"

namespace SOLUTION {

// pair<bool, Stuff3> countMajority(vector<Stuff3> &vec, int low, int high, pair<bool, Stuff3> left, pair<bool, Stuff3> right) {
//     int counterLeft = 0;
//     int counterRight = 0;

//     for (int i = low; i <= high; i++) {
//         Stuff3 currStuff = vec.at(i);
//         if (left.first == true && currStuff == left.second) {
//             counterLeft++;
//         } else if (right.first == true && currStuff == right.second) {
//             counterRight++;
//         }
//     }

//     int currMajority = ((high - low + 1) / 2) + 1;

//     if (counterLeft >= currMajority) {
//         return make_pair(true, left.second);
//     } else if (counterRight >= currMajority) {
//         return make_pair(true, right.second);
//     }
// }

int countOf(vector<Stuff3> &vec, int low, int high, Stuff3 &left) {
    int count = 0;

    for (int i = low; i <= high; i++) {
        if (vec.at(i) == left) {
            count++;
        }
    }

    return count;
}

// you should modify the code for this one
// you can also change the parameters.
// If you do that. make sure you change that for the call from Decision1()
pair<bool, Stuff3> DecisionRecur1(vector<Stuff3> &vec, int low, int high) {
    if (high - low <= 0) {
        return make_pair(true, vec.at(low));
    }

    int mid = low + (high - low) / 2;

    pair<bool, Stuff3> left = DecisionRecur1(vec, low, mid);
    pair<bool, Stuff3> right = DecisionRecur1(vec, mid + 1, high);

    if (left.first == true && right.first == true && left.second == right.second) {
        return make_pair(true, left.second);
    }

    // check if left or right is a majority and return it
    int countLeft = countOf(vec, low, high, left.second);
    int countRight = countOf(vec, low, high, right.second);

    if (countLeft > countRight && countLeft > (high - low + 1) / 2) {
        return make_pair(true, left.second);
    } else if (countRight > countLeft && countRight > (high - low + 1) / 2) {
        return make_pair(true, right.second);
    } else {
        return make_pair(false, Stuff3());
    }
}

pair<bool, Stuff3> Decision1(vector<Stuff3> &vec) {
    // TODO - check if vector is empty

    // you can change this line if you decide to change the parameters for DecisionRecur1
    return DecisionRecur1(vec, 0, vec.size() - 1);
}

int getCountOfFromRes(vector<pair<int, Stuff3>> &res, Stuff3 &stuff) {
    for (size_t i = 1; i < res.size(); i++) {
        if (res[i].second == stuff) {
            return res[i].first;
        }
    }

    return 0;
}

// --------------------------------------------------------------------------------

pair<int, Stuff3> oldDecisionRecur2(vector<Stuff3> &arr, int left, int right, int count, Stuff3 candidate) {
    if (right == left) {
        if (count == 0 || arr[left] == candidate) {
            return {count + 1, arr[left]};
        }
        return {count - 1, candidate};
    }
    if (right - left == 1) {
        if (count == 0) {
            if (arr[left] == arr[right]) {
                return {2, arr[left]};
            }
            return {0, arr[right]};
        }
        if (count == 1) {
            if (arr[left] == candidate) {
                return {2 + (arr[right] == candidate ? 1 : -1), candidate};
            }
            return {1, arr[right]};
        }

        count += (arr[left] == candidate ? 1 : -1);
        count += (arr[right] == candidate ? 1 : -1);
        return {count, candidate};
    }

    int mid = left + (right - left) / 2;
    auto leftRes = oldDecisionRecur2(arr, left, mid, count, candidate);
    auto rightRes = oldDecisionRecur2(arr, mid + 1, right, leftRes.first, leftRes.second);

    if (left == 0 && right == arr.size() - 1) {
        int count = countOf(arr, left, right, rightRes.second);
        return {count > arr.size() / 2, rightRes.second};
    }

    return rightRes;
}

pair<bool, Stuff3> oldDecision2(vector<Stuff3> &vec) {
    return oldDecisionRecur2(vec, 0, vec.size() - 1, 0, Stuff3());
}

// --------------------------------------------------------------------------------

pair<bool, Stuff3> DecisionRecur2(vector<Stuff3> &arr, int left, int right, int count, Stuff3 candidate, int& returnedCount) {
    if (right == left) {
        if (count == 0 || arr[left] == candidate) {
            returnedCount = count + 1;
            return {false, arr[left]};
        }
        returnedCount = count - 1;
        return {false, candidate};
    }
    if (right - left == 1) {
        if (count == 0) {
            if (arr[left] == arr[right]) {
                returnedCount = 2;
                return {false, arr[left]};
            }
            returnedCount = 0;
            return {false, arr[right]};
        }
        if (count == 1) {
            if (arr[left] == candidate) {
                returnedCount = 2 + (arr[right] == candidate ? 1 : -1);
                return {false, candidate};
            }
            returnedCount = 1;
            return {false, arr[right]};
        }

        count += (arr[left] == candidate ? 1 : -1);
        count += (arr[right] == candidate ? 1 : -1);
        returnedCount = count;
        return {false, candidate};
    }

    int mid = left + (right - left) / 2;
    auto leftRes = DecisionRecur2(arr, left, mid, count, candidate, returnedCount);
    auto rightRes = DecisionRecur2(arr, mid + 1, right, returnedCount, leftRes.second, returnedCount);

    if (left == 0 && right == arr.size() - 1) {
        int count = countOf(arr, left, right, rightRes.second);
        return {count > arr.size() / 2, rightRes.second};
    }

    return rightRes;
}

pair<bool, Stuff3> Decision2(vector<Stuff3> &vec) {
    int count = 0;
    return DecisionRecur2(vec, 0, vec.size() - 1, 0, Stuff3(), count);
}

};  // namespace SOLUTION

#endif