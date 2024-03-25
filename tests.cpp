#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "Sigma_OA.h"
#include "Create.h"
#include <unordered_set>


TEST_CASE("Check example cases", "[solution]")
{
    SECTION("example case 1"){
        std::unordered_set<uint64_t> files;
        FileSystem fs;
        // add 200 new files
        for (int i = 0; i < 200; i++) {
            int newFile = fs.addNewFile(std::to_string(i), "w", 0);
            files.insert(newFile);
        }

        fs.printFiles();
    }
}

// TEST_CASE("Check automatic edge cases", "[both solutions]")
// {
//     SECTION("auto testing"){
//         // unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
//         unsigned int seed = 0;

//         srand(seed);
//         std::cout << "seed = " << seed << std::endl;

//         int64_t i = 0;
//         while (i < INT64_MAX){
//             i++;
//         }
//     }
// }