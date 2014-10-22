#ifndef __CMDOPTS_HPP_INCLUDED__
#define __CMDOPTS_HPP_INCLUDED__

#include <string>
#include <map>
#include "../api/point.hpp"

namespace cmdopts {

    static std::map<std::string, std::string> system_params;

    void show_executable_usage();

    void init_system_parameters(int, const char **);

    std::vector<point> parse_points(std::string file_path, int dimensions);

    int get_int_value_by_system_param(char const *system_param);

    std::string get_string_value_by_system_param(char const *system_param);

}
#endif