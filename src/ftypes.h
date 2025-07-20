#pragma once

#include <cstdlib>
#include <vector>
#include <filesystem>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>

#ifdef WIN32
#define PATH_SEPARATOR ";"
#else
#define PATH_SEPARATOR ":"
#endif

namespace fs = std::filesystem;
namespace po = boost::program_options;

enum class LibStatus {
    UNKNOW = 0x0,
    FONDED = 0x1,
    NOT_FOUND = 0x2,
    UNRESOLVED = 0x3
};

#pragma pack(push,1)
using LibInf = struct  _lib_inf_s{
    fs::path path;
    std::string name;
    LibStatus status;
};
#pragma pack(pop)

using VecLib = std::vector<LibInf>;

#pragma pack(push,1)
using params_t = struct  _params_t_{
    std::vector<fs::path> includePaths;
    std::vector<fs::path> excludePaths;

    bool noSystemPaths;
    bool verbose;

    bool inited;
    _params_t_() : inited(false), verbose(false), noSystemPaths(false) {}
};
#pragma pack(pop)

#if defined(DEBUG)
    #include <iostream>

    inline void debug_log(const std::string& message) {
        std::cerr << "[DEBUG] " << message << std::endl;
    }

    inline void debug_log(const params_t& params) {
        std::cerr << "[DEBUG] Params:" << std::endl;
        std::cerr << "  Include Paths: ";
        for (const auto& path : params.includePaths) {
            std::cerr << path << " ";
        }
        std::cerr << std::endl;

        std::cerr << "  Exclude Paths: ";
        for (const auto& path : params.excludePaths) {
            std::cerr << path << " ";
        }
        std::cerr << std::endl;

        std::cerr << "  No System Paths: " << (params.noSystemPaths ? "true" : "false") << std::endl;
        std::cerr << "  Verbose: " << (params.verbose ? "true" : "false") << std::endl;
    }

#else
    inline void debug_log(const params_t& params) {}
    inline void debug_log(const std::string& message) {}
#endif