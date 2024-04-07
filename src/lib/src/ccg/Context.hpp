#pragma once

#include <filesystem>
#include <optional>


namespace ccg
{

/**
 * @brief Generation context information
 */
struct Context final
{
    // ccg Generate Parameters
    std::filesystem::path inputFile;
    std::filesystem::path configFile;

    // CMake Information
    std::filesystem::path binaryDir;
    std::filesystem::path currentBinaryDir;
    
    std::filesystem::path sourceDir;
    std::filesystem::path currentSourceDir;
};


/**
 * @brief Returns a `qpl::Context` from command line options 
 */
[[nodiscard]] Context MakeContext(int argc, char ** argv);

}  // namespace ccg
