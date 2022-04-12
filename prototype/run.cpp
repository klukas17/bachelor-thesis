#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Strategy.h"
#include "GEStrategy.h"

int main(int argc, char* argv[]) {
    int population_count = std::stoi(argv[1]);
    std::string requests_path = argv[2];
    int page_count = std::stoi(argv[3]);
    int frame_count = std::stoi(argv[4]);

    std::vector<int> requests;
    std::ifstream in(requests_path);
    std::string line, segment;

    while (getline(in, line)) {
        std::stringstream s(line);
        while (getline(s, segment, ' ')) {
            requests.push_back(stoi(segment));
        }
    }

    for (int i = 0; i < population_count; i++) {
        std::stringstream ss;
        ss << i;
        
        std::string file_name; 
        file_name += "results/";
        file_name += ss.str();
        file_name += ".txt";

        std::ofstream f;
        f.open(file_name);

        Strategy* s = new GEStrategy(requests, page_count, frame_count, i, frame_count);
        s->simulate();

        f << s->hits << std::endl;

        f.close();

        std::cout << "\t" << i + 1 << "/" << population_count << std::endl;
    }
}