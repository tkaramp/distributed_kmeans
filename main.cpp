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
    std::vector<point> distributed_centroids;
    std::map<int, std::vector<cluster>> total_clusters;
    kmeans alg;
    int total_distributed_points = 0;

    cmdopts::init_system_parameters(argc, argv);
    std::vector<int> points_per_machine(cmdopts::get_int_value_by_system_param("nfiles"));


    #pragma omp parallel
    {
        #pragma omp for private(points) reduction (+:total_distributed_points)
        for (int file_number = 0; file_number < cmdopts::get_int_value_by_system_param("nfiles"); file_number++) {
            std::cout << file_number << " iteration" << std::endl;
            std::string str_file_number = static_cast<std::ostringstream *>( &(std::ostringstream() << file_number) )->str();
            std::string file = cmdopts::get_string_value_by_system_param("file_path") + "/file" + str_file_number + ".txt";

            points = cmdopts::parse_points(file, cmdopts::get_int_value_by_system_param("dimensions"));

            total_distributed_points += points.size();
            points_per_machine[file_number] = points.size();
            total_clusters[file_number] = alg.run(cmdopts::get_int_value_by_system_param("k"), points);
        }
    }

    for(int file_number = 0; file_number < cmdopts::get_int_value_by_system_param("nfiles"); file_number++)
        for (int i = 0; i < total_clusters[file_number].size(); i++)
            total_clusters[file_number][i].print();

    for(int file_number = 0; file_number < cmdopts::get_int_value_by_system_param("nfiles"); file_number++)
        for (int i = 0; i < total_clusters[file_number].size(); i++) {
            centroid c = total_clusters[file_number][i].get_centroid();
            //double weight = (double) total_clusters[file_number][i].points().size() / (double) total_distributed_points;
            double weight = (double) points_per_machine[file_number] / (double) total_distributed_points;

            c.set_weight(weight);
            distributed_centroids.push_back(c);
        }

    std::vector<cluster> centroids_clusters = alg.run(cmdopts::get_int_value_by_system_param("k"),  distributed_centroids);


    std::cout<<"========================================================="<<std::endl;

    for (int i = 0; i < centroids_clusters.size(); i++)
        centroids_clusters[i].print();



    return 0;
}

