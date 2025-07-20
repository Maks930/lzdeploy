#pragma once
#include <ftypes.h>

namespace utils {
    params_t init_params(int argc, char** argv);
    std::vector<fs::path> getPath(const params_t& params);
};