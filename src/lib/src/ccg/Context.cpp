#include "ccg/Context.hpp"

#include <string_view>


namespace ccg
{
namespace
{

    [[nodiscard]] std::filesystem::path GetPathFromArgs(int argi, char ** argv)
    {
        return std::filesystem::absolute(std::filesystem::path(argv[argi]).make_preferred());
    }

}  // namespace


Context MakeContext(int argc, char ** argv)
{
    if (argc != 7ul)
    {
        // ToDo: show usage
        throw std::runtime_error("ccg missing arguments");
    }

    // auto const exePath = GetPathFromArgs(0, argv);
    auto const inputFile = GetPathFromArgs(1, argv);
    auto const configFile = GetPathFromArgs(2, argv);

    auto const binaryDirectory = GetPathFromArgs(3, argv);
    auto const currentBinaryDirectory = GetPathFromArgs(4, argv);

    auto const sourceDirectory = GetPathFromArgs(5, argv);
    auto const currentSourceDirectory = GetPathFromArgs(6, argv);

    auto const logDirectory = currentBinaryDirectory / "ccg";

    // ToDo: fixup paths (& apply macros?)

    return Context{ inputFile,
                    configFile,
                    logDirectory,
                    binaryDirectory,
                    currentBinaryDirectory,
                    sourceDirectory,
                    currentSourceDirectory };
}

}  // namespace ccg
