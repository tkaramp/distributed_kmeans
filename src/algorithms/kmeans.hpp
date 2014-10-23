#ifndef __KMEANS_HPP_INCLUDED__
#define __KMEANS_HPP_INCLUDED__

#include <string>
#include <map>
#include "../api/point.hpp"

class kmeans {
private:
    std::vector<centroid> choose_k_random_centroids(int , std::vector<point>);
    double get_distance(point , centroid );
    int assign_to_centroid(point , std::vector<centroid> );
    centroid calculate_new_centroid(std::vector<point> );
    std::vector<centroid> update_centroids(std::vector<cluster> );
    std::vector<cluster> update_clusters(std::vector<cluster> , std::vector<centroid> , bool &);

public:
    std::vector<cluster> run(int , std::vector<point> );

};

#endif