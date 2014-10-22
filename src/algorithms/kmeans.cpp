#include <math.h>
#include <algorithm>
#include <assert.h>
#include "../api/cluster.hpp"
#include "kmeans.hpp"
#include <ctime>        // std::time

std::vector<point> kmeans::choose_k_random_centroids(int k, std::vector<point> points){
    std::vector<point> centroids;
    std::srand ( unsigned ( std::time(0) ) );
    std::random_shuffle(points.begin(), points.end());

    for (int i = 0; i < k; i++)
        centroids.push_back(points[i]);

    for (int i = 0; i < k; i++)
        assert(centroids[i].size() >0);

    return centroids;
}

double  kmeans::get_distance(point p1, point p2) {
    double sum = 0;

    for (int i = 0; i < p1.size(); i++)
        sum += pow(p1.coordinate(i) - p2.coordinate(i), 2.0);
    return sqrt(sum);
}

int  kmeans::assign_to_centroid(point p, std::vector<point> centroids) {
    int centroid_id = 0;
    double min_distance = get_distance(p, centroids[0]), distance;

    for(int i = 1; i < centroids.size(); i++) {
        distance = get_distance(p, centroids[i]);
        if (distance <= min_distance){
            min_distance = distance;
            centroid_id = i;
        }
    }
    return centroid_id;
}


point kmeans::calculate_new_centroid(std::vector<point> points) {
    int dimensions = points[0].dimensions();
    int num_of_points = points.size();
    point new_centroid(dimensions);

    for (int axis = 0; axis < dimensions; axis++)
        new_centroid.set_coordinate(axis, points[0].coordinate(axis));


    for (int i = 1; i < num_of_points; i++)
        for (int axis = 0; axis < dimensions; axis++ )
            new_centroid.set_coordinate(axis, new_centroid.coordinate(axis) + points[i].coordinate(axis));

    for (int axis = 0; axis < dimensions; axis++)
        new_centroid.set_coordinate(axis, new_centroid.coordinate(axis) / num_of_points);

    assert(new_centroid.size() >0);
    return new_centroid;
}

std::vector<point> kmeans::update_centroids(std::vector<cluster> clusters) {
    int num_of_centroids = clusters.size();
    std::vector<point> centroids;
    centroids.reserve(num_of_centroids);

    for(int centroid_id = 0; centroid_id < clusters.size(); centroid_id++) {
        std::vector<point> points = clusters[centroid_id].points();

        // TODO: maybe here assert makes more sense i cover that at calculate_new_centroid
        if (points.size() == 0) {
            centroids.push_back(clusters[centroid_id].centroid());
            continue;
        }

        centroids.push_back(calculate_new_centroid(points));

    }

    //for (int i = 0; i < centroids.size(); i++)
    //    centroids[i].print();

    return centroids;
}

std::vector<cluster> kmeans::update_clusters(std::vector<cluster> old_clusters, std::vector<point> new_centroids, bool &converged) {

    int num_of_centroids = old_clusters.size();

    std::vector<cluster> new_clusters;

    new_clusters.reserve(num_of_centroids);

    // initialize new cluster with new centroids
    for (int centroid_id = 0; centroid_id < num_of_centroids; centroid_id++) {
        cluster c(new_centroids[centroid_id]);
        new_clusters.push_back(c);
    }

    for (int centroid_id = 0; centroid_id < num_of_centroids; centroid_id++) {
        std::vector<point> points = old_clusters[centroid_id].points();

        for (int i = 0; i < points.size(); i++) {
            int new_centroid_id = assign_to_centroid(points[i], new_centroids);

            if(new_centroid_id != centroid_id)
                converged = false;

            new_clusters[new_centroid_id].add_cluster_point(points[i]);
        }
    }

    return new_clusters;
}

std::vector<cluster>  kmeans::run(int k, std::vector<point> points){
    std::vector<point> centroids;
    std::vector<cluster> clusters;
    centroids.reserve(k);
    clusters.reserve(k);
    bool converged = true;
    // choose initial centroids. Note that they can be the same
    centroids = choose_k_random_centroids(k, points);

    // initialize the structure with centroid's values
    for (int centroid_id = 0; centroid_id < centroids.size(); centroid_id++) {
        cluster c(centroids[centroid_id]);
        clusters.push_back(c);
    }

    // assign each point to the nearest centroid
    for (int i = 0; i < points.size(); i++) {
        int centroid_id = assign_to_centroid(points[i], centroids);
        clusters[centroid_id].add_cluster_point(points[i]);
    }

    do {
        converged = true;
        clusters = update_clusters(clusters, update_centroids(clusters), converged);
    }while(!converged);

    return clusters;
}

