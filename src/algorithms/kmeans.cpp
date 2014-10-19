#include <math.h>
#include <bits/stl_algo.h>
#include "../api/cluster.hpp"
#include "kmeans.hpp"

std::vector<point> kmeans::choose_k_random_centers(int k, std::vector<point> points){
    std::vector<point> centers;
    std::random_shuffle(points.begin(), points.end());

    for (int i = 0; i < k; i++)
        centers.push_back(points[i]);

    return centers;
}


double  kmeans::get_distance(point p1, point p2) {
    double sum = 0;

    for (int i = 0; i < p1.size(); i++)
        sum += pow(p1.coordinate(i) - p2.coordinate(i), 2.0);
    return sqrt(sum);
}

int  kmeans::assign_to_center(point p, std::vector<point> centers) {
    int center_id = 0;
    double min_distance = get_distance(p, centers[0]), distance;

    for(int i = 1; i < centers.size(); i++) {
        distance = get_distance(p, centers[i]);
        if (distance <= min_distance){
            min_distance = distance;
            center_id = i;
        }
    }
    return center_id;
}

std::vector<cluster>  kmeans::run(int k, std::vector<point> points){
    std::vector<point> centers;
    std::vector<cluster> clusters;

    // choose initial centers. Note that they can be the same
    centers = choose_k_random_centers(k, points);

    // initialize the structure with the center's values
    for (int center_id = 0; center_id < points.size(); center_id++){
        cluster c(centers[center_id]);
        clusters.push_back(c);
    }

    // assign each point to the nearest center
    for (int i = 0; i < points.size(); i++){
        int center_id = assign_to_center(points[i], centers);
        clusters[center_id].add_cluster_point(points[i]);
    }

}
