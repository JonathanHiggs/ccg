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

    std::filesystem::path logDirectory;

    // CMake Information
    std::filesystem::path binaryDirectory;
    std::filesystem::path currentBinaryDirectory;
    
    std::filesystem::path sourceDirectory;
    std::filesystem::path currentSourceDirectory;
};


/**
 * @brief Returns a `qpl::Context` from command line options 
 */
[[nodiscard]] Context MakeContext(int argc, char ** argv);

}  // namespace ccg
