#ifndef __KMEANS_HPP_INCLUDED__
#define __KMEANS_HPP_INCLUDED__

#include <string>
#include <map>
#include "../api/point.hpp"

class kmeans {
private:
    std::vector<point> choose_k_random_centers(int , std::vector<point>);
    double get_distance(point , point );
    int assign_to_center(point , std::vector<point> );

public:
    std::vector<cluster> run(int , std::vector<point> );

};

#endif