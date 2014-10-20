#ifndef __CLUSTER_HPP_INCLUDED__
#define __CLUSTER_HPP_INCLUDED__


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

    inline void set_centroid(point centroid){
        cluster_centroid = centroid;
    }

    inline std::vector<point> points(){
        return cluster_points;
    }

    inline void add_cluster_point(point cluster_point){
        cluster_points.push_back(cluster_point);
    }


    inline void set_cluster_point(std::vector<point> points){
        cluster_points = points;
    }

    inline void print(){
        std::cout<<"cluster:\n";
        std::cout<<"\t\tcentroid:\t";
        centroid().print();
        std::cout<<std::endl;
        for(int point_id = 0; point_id < cluster_points.size() - 1; point_id++) {
            std::cout<<"\t\tpoint:\t\t";
            cluster_points[point_id].print();
        }
        std::cout<<"\t\tpoint:\t\t";
        cluster_points[cluster_points.size() - 1].print();

    }

};
#endif