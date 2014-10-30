#ifndef __CLUSTER_HPP_INCLUDED__
#define __CLUSTER_HPP_INCLUDED__


#include "iostream"
#include "vector"
#include "centroid.hpp"

class cluster{

private:
    centroid cluster_centroid;
    std::vector<point> cluster_points;
public:

    inline cluster(centroid cluster_centroid) : cluster_centroid(cluster_centroid) {
    }

    inline centroid get_centroid(){
        return cluster_centroid;
    }

    inline void set_centroid(centroid c){
        cluster_centroid = c;
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
        std::cout<<"\t";
        get_centroid().print();
        std::cout<<std::endl;

        long bound = cluster_points.size() - 1;

        for(int point_id = 0; point_id < bound; point_id++) {
            std::cout<<"\t\t";
            cluster_points[point_id].print();
        }
        std::cout<<"\t\t";

        if (cluster_points.size() > 0)
            cluster_points[cluster_points.size() - 1].print();

    }

};
#endif