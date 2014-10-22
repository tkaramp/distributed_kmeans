#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include "src/util/cmdopts.hpp"
#include "src/api/cluster.hpp"
#include "src/algorithms/kmeans.hpp"


int main(int argc, char const ** argv) {

    std::vector<point> points;
    std::vector<cluster> file_clusters;
    std::map<int, std::vector<cluster>> total_clusters;
    kmeans alg;

    cmdopts::init_system_parameters(argc, argv);

    #pragma omp parallel for private(points)
    for (int file_number = 0; file_number < cmdopts::get_int_value_by_system_param("nfiles"); file_number++){
        std::cout<<file_number<< " iteration" << std::endl;
        std::string str_file_number = static_cast<std::ostringstream*>( &(std::ostringstream() << file_number) )->str();
        std::string file = cmdopts::get_string_value_by_system_param("file_path") + "/file" + str_file_number + ".txt";

        points = cmdopts::parse_points(file, cmdopts::get_int_value_by_system_param("dimensions"));
        total_clusters[file_number] = alg.run(cmdopts::get_int_value_by_system_param("k"), points);
    }

//
//    for(int file_number = 0; file_number < cmdopts::get_int_value_by_system_param("nfiles"); file_number++)
//        for (int i = 0; i < total_clusters[file_number].size(); i++)
//            total_clusters[file_number][i].print();


    return 0;
}

