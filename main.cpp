#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "src/util/cmdopts.hpp"
#include "src/api/cluster.hpp"
#include "src/algorithms/kmeans.hpp"


int main(int argc, char const ** argv) {
    std::map<std::string, std::string> system_params;
    std::vector<point> points;
    std::vector<cluster> clusters;
    kmeans alg;

    system_params = cmdopts::init_system_parameters(argc, argv);
    points = cmdopts::parse_points(system_params["file"], atoi(system_params["dimensions"].c_str()));
    clusters = alg.run(atoi(system_params["k"].c_str()), points);
    return 0;
}

