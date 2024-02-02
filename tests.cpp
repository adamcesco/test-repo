#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "Solution.h"
#include "Create.h"

TEST_CASE("Check example cases", "[solution]")
{
    SECTION("example case 1"){
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
        // auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        auto seed = 0;
        std::cout << "seed = " << seed << std::endl;
        srand(seed);



        int64_t i = 0;
        while (i < INT64_MAX){
            int keyBegin = rand() % 100;
            int keyEnd = keyBegin + 1 + rand() % 100;
            size_t len = rand() % 100;
            
            // if (/* SOME ERROR CONDITION */) {
            //     std::cout << "redflag" << std::endl;
            // }

            std::vector<int> vec = Create::createVector(len, false, false, keyBegin, keyEnd);
            size_t randVal = rand() % 100;
            // do something with vec
        }
    }
}