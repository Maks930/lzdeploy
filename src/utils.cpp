#include "utils.h"
#include <filesystem>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>


params_t utils::init_params(int argc, char** argv) {

    params_t out_params;
    try {
        po::options_description desc("Available options");
        desc.add_options()
            ("help,h", "Help menu")
            ("verbose,v", "verbose mode")
            ("no-sys", "exclude system paths")
            ("include,I", po::value<std::string>(), "include paths")
            ("exclude,E", po::value<std::string>(), "exclude paths");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("verbose")) {
            out_params.verbose = true;
        }

        if (vm.count("no-sys")) {
            out_params.noSystemPaths = true;
        }

        if (vm.count("include")) {
            std::string raw_value = vm["include"].as<std::string>();
            std::vector<std::string> tmp;
            boost::split(tmp, raw_value, boost::is_any_of(",;"), boost::token_compress_on);

            tmp.erase(std::remove_if(tmp.begin(), tmp.end(),
                [](const std::string& path) { return path.empty(); }), tmp.end());

            for (const auto& path : tmp) {
                out_params.includePaths.push_back(path);
            }
        }

        if (vm.count("exclude")) {
            std::string raw_value = vm["exclude"].as<std::string>();
            std::vector<std::string> tmp;
            boost::split(tmp, raw_value, boost::is_any_of(",;"), boost::token_compress_on);

            tmp.erase(std::remove_if(tmp.begin(), tmp.end(),
                [](const std::string& path) { return path.empty(); }), tmp.end());

            for (const auto& path : tmp) {
                out_params.excludePaths.push_back(path);
            }
        }



    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return params_t();
    }

    return out_params;
}

std::vector<fs::path> utils::getPath(const params_t& params)
{
    std::vector<fs::path> paths;

    if (!params.noSystemPaths) boost::algorithm::split(paths, std::getenv("PATH"), boost::algorithm::is_any_of(";"));

    paths.insert(paths.end(), params.includePaths.begin(), params.includePaths.end());
    paths.erase(std::remove_if(paths.begin(), paths.end(),
        [&params](const fs::path& p) {
            return std::find(params.excludePaths.begin(), params.excludePaths.end(), p) != params.excludePaths.end();
        }), paths.end());

    return paths;
}