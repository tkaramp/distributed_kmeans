#ifndef __CMDOPTS_HPP_INCLUDED__
#define __CMDOPTS_HPP_INCLUDED__

#include <string>
#include <map>
#include "../api/point.hpp"

namespace cmdopts {

    void show_executable_usage();

    std::map<std::string, std::string> init_system_parameters(int, const char **);

    std::vector<point> parse_points(std::string file_path, int dimensions);
}
#endif