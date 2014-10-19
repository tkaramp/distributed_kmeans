#include "iostream"
#include "vector"
#include "point.hpp"


class cluster{

private:
    point cluster_centroid;
    std::vector<point> cluster_points;
public:

    inline cluster(point cluster_centroid) : cluster_centroid(cluster_centroid) {
    }

    inline point centroid(){
        return cluster_centroid;
    }

    inline point set_centroid(point centroid){
        cluster_centroid = centroid;
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