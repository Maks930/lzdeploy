#define DEBUG

#include <iostream>
#include <ftypes.h>
#include <utils.h>



int main(int argc, char *argv[])
{
    params_t params = utils::init_params(argc, argv);

    std::vector<fs::path> paths = utils::getPath(params);

    debug_log(params);

    for (const auto& path : paths) {
        std::cout << path << std::endl;
    }

    return 0;
}