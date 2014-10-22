#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

#include "cmdopts.hpp"

// print system executable's usage
void cmdopts::show_executable_usage() {
    std::cout << "Usage: ./<executable> <flag1> <parameter1> ... <flagn> <parametern>" << std::endl << std::endl;
    std::cout << "PARAMETERS" << std::endl << "\tAll the following parameters are optional. If a parameter is not " //
            "provided the system will try to load it from the configuration file" << std::endl << std::endl;

    // all available parameters
    std::cout << "\t-d, --dimensions" << std::endl << "\t\tShows usage and type of parameters" << std::endl << std::endl;
    std::cout << "\t-nf, --nfiles" << std::endl << "\t\tIf a path containing multiple files is given, nfiles is the number of those files" << std::endl << std::endl;
    std::cout << "\t-f, --files_path" << std::endl << "\t\tPath to the directory where several points containing file" \
            "exist. Files names should be of the following format: file<[0-nfiles)>.txt" << std::endl << std::endl;
    std::cout << "\t-h, --help" << std::endl << "\t\tShows usage and type of parameters" << std::endl << std::endl;
    std::cout << "\t-k" << std::endl << "\t\tNumber of cluster centroids" << std::endl << std::endl;
}


void cmdopts::init_system_parameters(int argc, char const **argv) {

    int vital_params_not_given = 4;

    for (int i = 1; i < argc; i = i + 2) {
        std::string flag = argv[i];

        if (!flag.compare("--dimensions") || !flag.compare("-d")) {
            // check if there is no file parameter after the flag
            if (i + 1 == argc) {
                std::cout << "No file parameter after flag: " << flag << std::endl;
                show_executable_usage();
                exit(EXIT_FAILURE);
            }

            assert(atoi(argv[i+1]) > 0);
            cmdopts::system_params["dimensions"] = argv[i + 1];
            vital_params_not_given--;
        }
        else if (!flag.compare("--files_path") || !flag.compare("-fp")) {
            // check if there is no file parameter after the flag
            if (i + 1 == argc) {
                std::cout << "No file parameter after flag: " << flag << std::endl;
                show_executable_usage();
                exit(EXIT_FAILURE);
            }

            cmdopts::system_params["file_path"] = argv[i + 1];
            vital_params_not_given--;
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

            assert(atoi(argv[i+1]) > 0);

            cmdopts::system_params["k"] = argv[i + 1];
            vital_params_not_given--;
        }
        else if (!flag.compare("--nfiles") || !flag.compare("-nf")) {
            // check if there is no file parameter after the flag
            if (i + 1 == argc) {
                std::cout << "No file parameter after flag: " << flag << std::endl;
                show_executable_usage();
                exit(EXIT_FAILURE);
            }

            cmdopts::system_params["nfiles"] = argv[i + 1];
            vital_params_not_given--;
        }
        else {
            std::cout << "Unknown flag: " << flag << std::endl;
            show_executable_usage();
            exit(EXIT_FAILURE);
        }
    }

    // check if all vital parameters have been initialized
    assert(vital_params_not_given == 0);

}

std::vector<point> cmdopts::parse_points(std::string file_path, int dimensions) {
    std::ifstream points_file(file_path.c_str());
    std::string line;
    std::vector<point> points;

    if (!points_file.good()) {
        std::cout << "Error in reading file: " << file_path << std::endl;
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

    return points;
}

int cmdopts::get_int_value_by_system_param(const char * system_param){
    if (cmdopts::system_params.find(system_param) != cmdopts::system_params.end())
        return atoi(cmdopts::system_params[system_param].c_str());

    std::cout<<"Unknow parameter: "<<system_param<<"required"<<std::endl;
    exit(EXIT_FAILURE);
}

std::string cmdopts::get_string_value_by_system_param(const char * system_param){
    if (cmdopts::system_params.find(system_param) != cmdopts::system_params.end())
        return cmdopts::system_params[system_param].c_str();

    std::cout<<"Unknow parameter: "<<system_param<<"required"<<std::endl;
    exit(EXIT_FAILURE);
}
