#include "iostream"
#include "vector"
#include "point.hpp"


class cluster{

private:
    point cluster_center;
    std::vector<point> cluster_points;
public:

    inline cluster(point cluster_center) : cluster_center(cluster_center) {
    }

    inline point center(){
        return cluster_center;
    }

    inline point set_center(point center){
        cluster_center = center;
    }

    inline std::vector<point> points(){
        return cluster_points;
    }

    inline point add_cluster_point(point cluster_point){
        cluster_points.push_back(cluster_point);
    }


    inline point set_cluster_point(std::vector<point> points){
        cluster_points = points;
    }

};