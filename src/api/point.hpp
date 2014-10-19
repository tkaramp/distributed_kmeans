#include "iostream"
#include "vector"

class point{

private:
    std::vector<double> coordinates_vector;
    int dimensions;
public:

    inline point(int dimensions) {
        coordinates_vector.reserve(dimensions);
        point::dimensions = dimensions;
    }

    inline double set_coordinate(int axis, double coordinate){
        return coordinates_vector[axis] = coordinate;
    }

    inline double coordinate(int axis){
        return coordinates_vector[axis];
    }

    inline int size(){
        return dimensions;
    }

};