#ifndef __POINT_HPP_INCLUDED__
#define __POINT_HPP_INCLUDED__

#include <iostream>
#include <vector>
#include <limits>
#include <assert.h>

class point{

private:
    std::vector<double> coordinates_vector;
    int point_size;
    int point_dimensions;
public:

    inline point(int point_dimensions) {
        assert(point_dimensions > 0);
        point::point_dimensions = point_dimensions;
        coordinates_vector.reserve(point_dimensions);
        double inf = std::numeric_limits<double>::infinity();
        for (int axis = 0; axis < point_dimensions; axis++)
            coordinates_vector.push_back(inf);
        point_size = point::point_dimensions;
    }

    inline void set_coordinate(int axis, double coordinate){
        assert(point_size > axis);
        coordinates_vector[axis] = coordinate;

    }

    inline double coordinate(int axis){
        double inf = std::numeric_limits<double>::infinity();
        assert(point_size > 0);
        assert(axis < point_size && axis >= 0);
        assert(coordinates_vector[axis] != inf);
        return coordinates_vector[axis];
    }

    inline int size(){
        return point_size;
    }

    inline int dimensions(){
        return point_dimensions;
    }

    inline void print(){
        std::cout<<"point<";
        for(int axis = 0; axis < size() - 1; axis++)
            std::cout<<coordinate(axis)<<", ";

        std::cout<<coordinate(size() - 1)<<">"<<std::endl;
    }

};

#endif