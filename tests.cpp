#define CATCH_CONFIG_MAIN
#include "Create.h"
#include "Solution.h"
#include "catch2/catch.hpp"

TEST_CASE("Check automatic edge cases", "[solution]") {
    SECTION("auto test case generating") {
        unsigned int seed = 0;
        // unsigned int seed = rand();
        std::cout << "seed = " << seed << std::endl;
        srand(seed);

        size_t correctCount = 0;

        while (true) {
            size_t len = rand() % 100 + 10;
            size_t varientsCount = rand() % 5 + 3;

            auto vec = Create::createStuff3Vector(len, varientsCount);

            if (correctCount == 37306) {
                std::cout << "RED FLAG" << std::endl;
            }

            auto res1 = SOLUTION::Decision1(vec);
            auto res2 = SOLUTION::Decision4(vec);
            if (res1.first == res2.first) {
                if (res1.first == false || (res1.first == true && res1.second == res2.second)) {
                    correctCount++;
                    continue;
                }
            }

            std::cout << "correctCount = " << correctCount << std::endl;
            std::cout << "len = " << len << std::endl;
            std::cout << "varientsCount = " << varientsCount << std::endl;
            for (auto& v : vec) {
                std::cout << v << " ";
            }
            std::cout << std::endl;
            if (res1.first) {
                std::cout << "SOLUTION::solution1 = " << res1.second << std::endl;
            } else {
                std::cout << "SOLUTION::solution1 = no majority found" << std::endl;
            }
            if (res2.first) {
                std::cout << "SOLUTION::solution2 = " << res2.second << std::endl;
            } else {
                std::cout << "SOLUTION::solution2 = no majority found" << std::endl;
            }

            break;
        }
    }
}