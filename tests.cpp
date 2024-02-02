#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "Solution.h"
#include "Create.h"

TEST_CASE("Check example cases", "[solution]")
{
    SECTION("example case 1"){
        REQUIRE(SOLUTION::bruteForceSolution("BAR") == 2);
        REQUIRE(SOLUTION::bruteForceSolution("AABB") == 1);
        REQUIRE(SOLUTION::bruteForceSolution("AABCY") == 6);
        // REQUIRE(SOLUTION::bruteForceSolution("AAAB") == 0);
        REQUIRE(SOLUTION::bruteForceSolution("ABBCA") == 3);
        REQUIRE(SOLUTION::bruteForceSolution("BABBCAA") == 4);
        
        REQUIRE(SOLUTION::countAnagrams("BAR") == 2);
        REQUIRE(SOLUTION::countAnagrams("AABB") == 1);
        REQUIRE(SOLUTION::countAnagrams("AABCY") == 6);
        REQUIRE(SOLUTION::countAnagrams("AAAB") == 0);
        REQUIRE(SOLUTION::countAnagrams("BABBCAA") == 4);

        std::cout << SOLUTION::bruteForceSolution("BABBCAA") << std::endl;
        std::cout << SOLUTION::countAnagrams("BABBCAA") << std::endl;
    }
    
    SECTION("example case 2"){
    }
    
    SECTION("example case 3"){
    }
}

TEST_CASE("Check custom normal cases", "[solution]")
{
    SECTION("normal case 1"){
    }
}

TEST_CASE("Check custom edge cases", "[solution]")
{
    SECTION("edge case 1"){
    }
}

TEST_CASE("Check automatic edge cases", "[solution]")
{
    SECTION("auto testing"){
        // unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
        unsigned int seed = 0;
        std::cout << "seed = " << seed << std::endl;
        srand(seed);



        int64_t i = 0;
        while (i < INT64_MAX){
            int keyBegin = rand() % -1000000;
            int keyEnd = rand() % 1000000;
            size_t len = rand() % 5 + 3;
            
            std::string input = Create::createString(len, false, true, false, false, false);

            if (Create::hasEvenConsonantsWithMoreVowels(input) == true){
                continue;
            }
            std::cout << input << std::endl;

            int resultBrute = SOLUTION::bruteForceSolution(input);
            int resultOptimized = SOLUTION::countAnagrams(input);
            if (resultBrute != resultOptimized){
                std::cout << "seed = " << seed << std::endl;
                std::cout << "input = " << input << std::endl;
                std::cout << "i = " << i << std::endl;
                REQUIRE(resultBrute == resultOptimized);
            }

            i++;
        }
    }
}