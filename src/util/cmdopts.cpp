#include <iostream>
#include <fstream>
#include <sstream>

#include "cmdopts.hpp"
using namespace cmdopts;

// print system executable's usage
void show_executable_usage() {
    std::cout << "Usage: ./<executable> <flag1> <parameter1> ... <flagn> <parametern>" << std::endl << std::endl;
    std::cout << "PARAMETERS" << std::endl << "\tAll the following parameters are optional. If a parameter is not " //
            "provided the system will try to load it from the configuration file" << std::endl << std::endl;

    // all available parameters
    std::cout << "\t-d, --dimensions" << std::endl << "\t\tShows usage and type of parameters" << std::endl << std::endl;
    std::cout << "\t-f, --file" << std::endl << "\t\tPath to the points containing file" << std::endl << std::endl;
    std::cout << "\t-h, --help" << std::endl << "\t\tShows usage and type of parameters" << std::endl << std::endl;
    std::cout << "\t-k" << std::endl << "\t\tNumber of cluster centroids" << std::endl << std::endl;
}


std::map<std::string, std::string> init_system_parameters(int argc, char const **argv) {
    std::map<std::string, std::string> system_params;

    for (int i = 1; i < argc; i = i + 2) {
        std::string flag = argv[i];

        if (!flag.compare("--dimensions") || !flag.compare("-d")) {
            // check if there is no file parameter after the flag
            if (i + 1 == argc) {
                std::cout << "No file parameter after flag: " << flag << std::endl;
                show_executable_usage();
                exit(EXIT_FAILURE);
            }
            system_params["dimensions"] = argv[i + 1];

        }
        else if (!flag.compare("--file") || !flag.compare("-f")) {
            // check if there is no file parameter after the flag
            if (i + 1 == argc) {
                std::cout << "No file parameter after flag: " << flag << std::endl;
                show_executable_usage();
                exit(EXIT_FAILURE);
            }

            system_params["file"] = argv[i + 1];
        }
        else if (!flag.compare("--help") || !flag.compare("-h")) {
            show_executable_usage();
            exit(EXIT_SUCCESS);
        }
        else if (!flag.compare("-k")) {
            // check if there is no file parameter after the flag
            if (i + 1 == argc) {
                std::cout << "No file parameter after flag: " << flag << std::endl;
                show_executable_usage();
                exit(EXIT_FAILURE);
            }

            system_params["k"] = argv[i + 1];
        }
        else {
            std::cout << "Unknown flag: " << flag << std::endl;
            show_executable_usage();
            exit(EXIT_FAILURE);
        }
    }

    return system_params;
    //TODO: check if all vital parameters have been initialized

}

std::vector<point> parse_points(std::string file_path, int dimensions) {
    std::ifstream points_file(file_path.c_str());
    std::string line;
    std::vector<point> points;

    if (!points_file.good()) {
        std::cout << "Error in reading config file: " << file_path << std::endl;
        exit(EXIT_FAILURE);
    }

    while (std::getline(points_file, line)) {
        // skip comments
        if (line[0] == '#') continue;

        //skip empty lines
        if (line.length() == 0) continue;

        std::istringstream coord_line(line);
        point p(dimensions);

        for (int axis = 0; axis < dimensions; axis++) {
            std::string coordinate;
            if (std::getline(coord_line, coordinate, ' '))
                p.set_coordinate(axis, atof(coordinate.c_str()));
        }

        points.push_back(p);
    }
}
