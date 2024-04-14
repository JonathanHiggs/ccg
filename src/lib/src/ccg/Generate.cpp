#include "ccg/Generate.hpp"

#include "ccg/Macros.hpp"

#include <fmt/std.h>

#include <inja/inja.hpp>

#include <filesystem>
#include <map>
#include <string>
#include <vector>


namespace ccg
{

void Generate(Input & input, Config const & config, Context const & context, LoggerPtr const & logger)
{
    auto env = inja::Environment(config.templatesDirectory.string(), input.outDirectory.string());

    // Maybe: set from config
    env.set_trim_blocks(true);
    env.set_lstrip_blocks(false);

    for (auto & item : input.items)
    {
        item.data["name"] = item.name;
        item.data["config"] = config.data;

        for (auto & output : item.outputs)
        {
            logger->trace("Rendering \"{}\" - \"{}\"", item.name, output.templateName);
            logger->trace("Item data: {}", item.data.dump());

            auto outputPath = SubstitutePathMacros(output.outputPath, context, logger);
            if (!outputPath.is_absolute())
            {
                outputPath = (input.outDirectory / outputPath).make_preferred();
            }

            // ToDo: Check output directory exists

            std::ofstream file(outputPath);
            file << env.render_file(output.templateName, item.data);
            file.close();

            logger->info("Rendered \"{}\" with template \"{}\" to {}", item.name, output.templateName, outputPath);
        }
    }
}

}  // namespace ccg
