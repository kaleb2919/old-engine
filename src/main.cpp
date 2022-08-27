#include <iostream>
#define TOML_EXCEPTIONS 0
#include <toml++/toml.h>
#include "render/Device.h"
#include "entt/entt.hpp"

int main()
{
    toml::parse_result global_config = toml::parse_file("data/config/global.toml");
    if (!global_config)
    {
        std::cerr << "Parsing failed:\n" << global_config.error() << std::endl;
        return -1;
    }

    std::string title = global_config["general"]["project_name"].value_or<std::string>("Application");
    int width = global_config["render"]["window"]["width"].value_or<int>(640);
    int height = global_config["render"]["window"]["height"].value_or<int>(480);

    auto window = Device::create(width, height, title);

    if (!window)
    {
        return -1;
    }

    while (window->isRunning())
    {
        window->clear();
        window->swap();
    }

    window->close();
    return 0;
}