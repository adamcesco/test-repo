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

// you should modify the code for this one
// you can also change the parameters.
// If you do that. make sure you change that for the call from Decision2()
vector<pair<int, Stuff3>> DecisionRecur2(vector<Stuff3> &vec, int low, int high) {
    int currSize = high - low + 1;
    if (currSize <= 0) {
        return {make_pair(false, Stuff3()), make_pair(0, Stuff3()), make_pair(0, Stuff3())};
    } else if (currSize == 1) {
        return {make_pair(true, vec.at(low)), make_pair(1, vec.at(low))};
    } else if (currSize == 2) {
        if (vec.at(low) == vec.at(low + 1)) {
            return {make_pair(true, vec.at(low)), make_pair(2, vec.at(low))};
        } else {
            return {make_pair(false, Stuff3()), make_pair(1, vec.at(low)), make_pair(1, vec.at(low + 1))};
        }
    } else if (currSize == 3) {
        // get the majority of the 3 elements
        if (vec.at(low) == vec.at(low + 1) && vec.at(low + 1) == vec.at(low + 2)) {
            return {make_pair(true, vec.at(low)), make_pair(3, vec.at(low))};
        } else if (vec.at(low) == vec.at(low + 1)) {
            return {make_pair(true, vec.at(low)), make_pair(2, vec.at(low)), make_pair(1, vec.at(low + 2))};
        } else if (vec.at(low) == vec.at(low + 2)) {
            return {make_pair(true, vec.at(low)), make_pair(2, vec.at(low)), make_pair(1, vec.at(low + 1))};
        } else if (vec.at(low + 1) == vec.at(low + 2)) {
            return {make_pair(true, vec.at(low + 1)), make_pair(2, vec.at(low + 1)), make_pair(1, vec.at(low))};
        } else {
            return {make_pair(false, Stuff3()), make_pair(1, vec.at(low)), make_pair(1, vec.at(low + 1)), make_pair(1, vec.at(low + 2))};
        }
    }

    int mid = low + (high - low) / 2;

    vector<pair<int, Stuff3>> resLeft = DecisionRecur2(vec, low, mid);
    vector<pair<int, Stuff3>> resRight = DecisionRecur2(vec, mid + 1, high);
    pair<bool, Stuff3> left = {resLeft[0].first, resLeft[0].second};
    pair<bool, Stuff3> right = {resRight[0].first, resRight[0].second};
    if (low == 0 && high == vec.size() - 1) {
        int countLeft = (left.first == false) ? 0 : countOf(vec, low, high, left.second);
        int countRight = (right.first == false) ? 0 : countOf(vec, low, high, right.second);

        if (countLeft > currSize / 2) {
            return {make_pair(true, left.second)};
        } else if (countRight > currSize / 2) {
            return {make_pair(true, right.second)};
        } else {
            return {make_pair(false, Stuff3()), make_pair(0, Stuff3()), make_pair(0, Stuff3())};
        }
    }

    int countLeft = (left.first == false) ? 0 : (getCountOfFromRes(resLeft, left.second) + getCountOfFromRes(resRight, left.second));
    int countRight = (right.first == false) ? 0 : (getCountOfFromRes(resLeft, right.second) + getCountOfFromRes(resRight, right.second));

    if (left.first ^ right.first) {
        if (left.first) {
            return {make_pair(true, left.second), make_pair(countLeft, left.second)};
        } else {
            return {make_pair(true, right.second), make_pair(countRight, right.second)};
        }
    } else if (left.first == false && right.first == false) {
        return {make_pair(false, Stuff3())};
    }

    if (left.second == right.second) {
        return {make_pair(true, left.second), make_pair(countLeft, left.second)};
    }

    if (countLeft > countRight) {
        return {make_pair(true, left.second), make_pair(countLeft, left.second), make_pair(countRight, right.second)};
    } else if (countRight > countLeft) {
        return {make_pair(true, right.second), make_pair(countRight, right.second), make_pair(countLeft, left.second)};
    } else {
        return {make_pair(false, Stuff3()), make_pair(countLeft, left.second), make_pair(countRight, right.second)};
    }
}

pair<bool, Stuff3> Decision2(vector<Stuff3> &vec) {
    auto res = DecisionRecur2(vec, 0, vec.size() - 1);
    return {res[0].first, res[0].second};
}

//---------------------------------------------------------------------------------

pair<bool, Stuff3> DecisionRecur3(vector<Stuff3> &vec) {
    Stuff3 candidate;
    int count = 0;
    for (size_t i = 0; i < vec.size(); i++) {
        if (count == 0) {
            candidate = vec.at(i);
            count = 1;
        } else if (candidate == vec.at(i)) {
            count++;
        } else {
            count--;
        }
    }

    int candidateCount = countOf(vec, 0, vec.size() - 1, candidate);
    return {candidateCount > vec.size() / 2, candidate};
}

pair<bool, Stuff3> Decision3(vector<Stuff3> &vec) {
    return DecisionRecur3(vec);
}

// --------------------------------------------------------------------------------

pair<int, Stuff3> DecisionRecur4(vector<Stuff3> &arr, int left, int right, int count, Stuff3 candidate) {
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
    auto leftRes = DecisionRecur4(arr, left, mid, count, candidate);
    auto rightRes = DecisionRecur4(arr, mid + 1, right, leftRes.first, leftRes.second);

    if (left == 0 && right == arr.size() - 1) {
        int count = countOf(arr, left, right, rightRes.second);
        return {count > arr.size() / 2, rightRes.second};
    }

    return rightRes;
}

pair<bool, Stuff3> Decision4(vector<Stuff3> &vec) {
    return DecisionRecur4(vec, 0, vec.size() - 1, 0, Stuff3());
}

// --------------------------------------------------------------------------------

pair<int, Stuff3> DecisionRecur5(vector<Stuff3> &arr, Stuff3 candidate, int count, int index) {
    if (index == arr.size()) {
        return {true, candidate};
    }

    if (count == 0) {
        candidate = arr[index];
        count = 1;
    } else if (arr[index] == candidate) {
        count++;
    } else {
        count--;
    }

    return DecisionRecur5(arr, candidate, count, index + 1);
}

bool validateCandidate(const vector<Stuff3> &arr, Stuff3 candidate) {
    int count = 0;
    for (auto& num : arr) {
        if (num == candidate) {
            count++;
        }
    }
    return count > arr.size() / 2;
}

pair<bool, Stuff3> Decision5(vector<Stuff3> &arr) {
    auto candidate = DecisionRecur5(arr, Stuff3(), 0, 0);
    return {validateCandidate(arr, candidate.second), candidate.second};
}

};  // namespace SOLUTION

#endif