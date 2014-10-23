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
protected:
    int point_weight;
public:

    inline point(int point_dimensions) {
        assert(point_dimensions > 0);
        point::point_dimensions = point_dimensions;
        coordinates_vector.reserve(point_dimensions);
        double inf = std::numeric_limits<double>::infinity();
        for (int axis = 0; axis < point_dimensions; axis++)
            coordinates_vector.push_back(inf);
        point_size = point::point_dimensions;
        point_weight = 1;

    }

//    inline point(const point& p){
//        point(p.dimensions());
//        coordinates_vector = p.coordinates();
//    }


    inline void set_coordinate(int axis, double coordinate){
        assert(point_size > axis);
        coordinates_vector[axis] = coordinate;
    }

    inline double coordinate(int axis) const{
        double inf = std::numeric_limits<double>::infinity();
        assert(point_size > 0);
        assert(axis < point_size && axis >= 0);
        assert(coordinates_vector[axis] != inf);
        return coordinates_vector[axis];
    }


    inline std::vector<double>  coordinates() const{
        return coordinates_vector;
    }



    inline int size() const{
        return point_size;
    }

    inline int dimensions() const{
        return point_dimensions;
    }

    inline double weight() const{
        return point_weight;
    }

    inline virtual void print() const{
        std::cout<<"point<";
        for(int axis = 0; axis < size() - 1; axis++)
            std::cout<<coordinate(axis)<<", ";

        std::cout<<coordinate(size() - 1)<<">"<<std::endl;
    }

};

#endif