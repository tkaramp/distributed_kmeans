#ifndef __KMEANS_HPP_INCLUDED__
#define __KMEANS_HPP_INCLUDED__

#include <string>
#include <map>
#include "../api/point.hpp"

class kmeans {
private:
    std::vector<point> choose_k_random_centroids(int , std::vector<point>);
    double get_distance(point , point );
    int assign_to_centroid(point , std::vector<point> );
    point calculate_new_centroid(std::vector<point> );
    std::vector<point> update_centroids(std::vector<cluster> );
    std::vector<cluster> update_clusters(std::vector<cluster> , std::vector<point> , bool &);

public:
    std::vector<cluster> run(int , std::vector<point> );

};

#endif