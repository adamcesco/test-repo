#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "Solution.h"
#include "Solution2.h"
#include "Create.h"

TEST_CASE("Check example cases", "[solution]")
{
    // SECTION("example case 1"){
    //     REQUIRE(SOLUTION::bruteForceSolution("BAR") == 2);
    //     REQUIRE(SOLUTION::bruteForceSolution("AABB") == 1);
    //     REQUIRE(SOLUTION::bruteForceSolution("AABCY") == 6);
    //     REQUIRE(SOLUTION::bruteForceSolution("AAAB") == 0);
    //     REQUIRE(SOLUTION::bruteForceSolution("ABBCA") == 3);
    //     REQUIRE(SOLUTION::bruteForceSolution("BABBCAA") == 4);
        
        // REQUIRE(SOLUTION::optimizedSolution("BAR") == 2);
    //     REQUIRE(SOLUTION::optimizedSolution("AABB") == 1);
    //     REQUIRE(SOLUTION::optimizedSolution("AABCY") == 6);
    //     REQUIRE(SOLUTION::optimizedSolution("AAAB") == 0);
    //     REQUIRE(SOLUTION::optimizedSolution("BABBCAA") == 4);

    //     std::cout << SOLUTION::bruteForceSolution("BABBCAA") << std::endl;
    //     std::cout << SOLUTION::optimizedSolution("BABBCAA") << std::endl;
    // }
    
    SECTION("example case 2"){
    }
    
    SECTION("example case 3"){
    }
}

TEST_CASE("Check custom normal cases", "[solution2]")
{
    SECTION("normal case 1"){
        REQUIRE(SOLUTION2::bruteForceSolution({2, 6, 8, 5}) == 3);
        REQUIRE(SOLUTION2::bruteForceSolution({1, 5, 5, 2, 6}) == 4);
        REQUIRE(SOLUTION2::bruteForceSolution({1, 1}) == 2);
        REQUIRE(SOLUTION2::bruteForceSolution({1, 2, 3, 4, 5}) == 5);
        REQUIRE(SOLUTION2::bruteForceSolution({1, 5, 5, 2, 6}) == 4);
    }
}

TEST_CASE("Check custom edge cases", "[solution2]")
{
    SECTION("edge case 1"){
    }
}

TEST_CASE("Check automatic edge cases", "[both solutions]")
{
    // SECTION("auto testing solution 1"){
    //     unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    //     // unsigned int seed = 0;
    //     std::cout << "seed = " << seed << std::endl;
    //     srand(seed);



    //     int64_t i = 0;
    //     while (i < INT64_MAX){
    //         int keyBegin = rand() % -1000000;
    //         int keyEnd = rand() % 1000000;
    //         size_t len = rand() % 15 + 1;
            
    //         std::string input = Create::createString(len, false, true, false, false, false);

    //         int resultBrute = SOLUTION::bruteForceSolution(input);
    //         int resultOptimized = SOLUTION::optimizedSolution(input);
    //         if (resultBrute != resultOptimized){
    //             std::cout << "seed = " << seed << std::endl;
    //             std::cout << "input = " << input << std::endl;
    //             std::cout << "i = " << i << std::endl;
    //             REQUIRE(resultBrute == resultOptimized);
    //         }

    //         i++;
    //     }
    // }
    
    SECTION("auto testing solution 1"){
        unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
        // unsigned int seed = 0;
        std::cout << "seed = " << seed << std::endl;
        srand(seed);



        int64_t i = 0;
        while (i < INT64_MAX){
            int lowerBound = 0;
            int upperBound = rand() % 500 + 1;
            size_t len = rand() % 300 + 1;
            
            std::vector<int> input = Create::createIntVector(len, false, false, lowerBound, upperBound);

            int resultBrute = SOLUTION2::bruteForceSolution(input);
            int resultOptimized = SOLUTION2::optimizedSolution(input);
            if (resultBrute != resultOptimized){
                std::cout << "seed = " << seed << std::endl;
                std::cout << "input = ";
                for (auto x : input){
                    std::cout << x << " ";
                }
                std::cout << std::endl;
                std::cout << "i = " << i << std::endl;
                REQUIRE(resultBrute == resultOptimized);
            }

            i++;
        }
    }
}