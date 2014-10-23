#ifndef __CENTROID_HPP_INCLUDED__
#define __CENTROID_HPP_INCLUDED__

#include <iostream>
#include <vector>
#include <limits>
#include <assert.h>
#include "point.hpp"

class centroid : public point{

public:

    inline centroid(int centroid_dimensions) : point(centroid_dimensions){}

    inline centroid(point p) : point(p){}

    inline void set_weight(double weight){
        point::point_weight = weight;
    }
    inline void print(){
        std::cout<<"centroid<";
        for(int axis = 0; axis < size() - 1; axis++)
            std::cout<<point::coordinate(axis)<<", ";

        std::cout<<coordinate(size() - 1)<<">"<<std::endl;
    }

};

#endif