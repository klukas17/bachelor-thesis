#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>

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

    std::set<int> blacklisted;
    std::ifstream blacklisted_file("solutions/blacklisted.txt");
    std::string l;
    std::vector<int> vec;
    std::istringstream iss;
    std::string s;
    getline(blacklisted_file, l);
    iss = std::istringstream(l);
    while (getline(iss, s, ' ')) blacklisted.insert(std::stoi(s));

    for (int i = 0; i < population_count; i++) {
        std::stringstream ss;
        ss << i;
        
        std::string file_name; 
        file_name += "results/";
        file_name += ss.str();
        file_name += ".txt";

        std::ofstream f;
        f.open(file_name);

        int hits;

        if (blacklisted.find(i) == blacklisted.end()) {
            Strategy* s = new GEStrategy(requests, page_count, frame_count, i, frame_count);
            s->simulate();
            f << s->hits << std::endl;
            hits = s->hits;
        }
        else {
            f << 0 << std::endl;
            hits = 0;
        }

        f.close();

        std::cout << "\t" << i + 1 << "/" << population_count << "\t\t\t" << hits << std::endl;
    }
}