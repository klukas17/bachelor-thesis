#include <stdlib.h>
#include <string>
#include <tuple>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "Unit.h"
#include "Crossover.h"
#include "Mutation.h"

class Container {
    public:
        int value;
        float coef;
        int index;
        Unit* unit1;
        Unit* unit2;

        Container(int v, int c, int i, Unit* u1, Unit* u2) {
            value = v;
            coef = c;
            index = i;
            unit1 = u1;
            unit2 = u2;
        }
};

float A = 1.0f;
float B = 10.0f;

int main(int argc, char* argv[]) {
    int population_count = std::stoi(argv[1]);
    int codon_count = std::stoi(argv[2]);
    float mutation_rate = 1 / (float) std::stoi(argv[3]);

    Crossover* crossover = new Crossover();
    Mutation* mutation = new Mutation(mutation_rate);

    srand(time(NULL));

    std::vector<Container*> units;

    for (int i = 0; i < population_count; i++) {
        std::stringstream ss;
        ss << i;
        
        std::string file_name; 
        file_name += "solutions/";
        file_name += ss.str();
        file_name += ".txt";

        Unit* unit1 = new Unit(codon_count);
        Unit* unit2 = new Unit(codon_count);

        std::ifstream input(file_name);
        std::string line;

        std::vector<unsigned char> v1, v2;

        std::istringstream iss;
        std::string s;

        getline(input, line);
        iss = std::istringstream(line);
        while (getline(iss, s, ' ')) v1.push_back(std::stoi(s));
        getline(input, line);
        iss = std::istringstream(line);
        while (getline(iss, s, ' ')) v2.push_back(std::stoi(s));

        unit1->genome = v1;
        unit2->genome = v2;

        ss.str("");
        file_name = "";
        file_name += "results/";
        ss << i;
        file_name += ss.str();
        file_name += ".txt";

        int result;

        std::ifstream in(file_name);
        line = "";
        getline(in, line);
        result = std::stoi(line);

        Container* t = new Container(result, 0, i, unit1, unit2);

        units.push_back(t);
    }

    std::sort(units.begin(), units.end(), 
    [](Container* a, Container* b) {
        if (a->value != b->value) return a->value < b->value;
        else return a->index < b->index;
    });

    float min, max;
    max = units[0]->value;
    min = units.rbegin()[0]->value;

    std::cout << "\t" << "Biggest fitness: " << max << std::endl;

    float range = 0;

    if (max != min) {

        for (Container* c : units)
            c->coef = A + (B - A) * (c->value - min) / (max - min);

        for (Container* c : units) {
            float x = c->coef;
            c->coef += range;
            range += x;
        }
    }

    else {

        for (Container* c : units) {
            range++;
            c->coef = range;
        }
    }

    std::vector<std::pair<Unit*, Unit*>> pairs;

    pairs.push_back({units[0]->unit1, units[0]->unit2});
    pairs.push_back({units[1]->unit1, units[1]->unit2});

    while (pairs.size() < population_count) {
        float r1, r2;

        r1 = (rand() / (float) RAND_MAX) * range;
        r2 = (rand() / (float) RAND_MAX) * range;

        int i1 = 0, i2 = 0;

        while (r1 > units[i1]->coef) i1++;
        while (r2 > units[i2]->coef) i2++;

        Unit* u1 = crossover->perform(units[i1]->unit1, units[i2]->unit1);
        Unit* u2 = crossover->perform(units[i1]->unit2, units[i2]->unit2);

        u1 = mutation->perform(u1);
        u2 = mutation->perform(u2);

        pairs.push_back({u1, u2});
    }

    for (int i = 0; i < pairs.size(); i++) {

        Unit* unit1 = pairs[i].first;
        Unit* unit2 = pairs[i].second;

        std::stringstream ss;
        ss << i;
        
        std::string file_name; 
        file_name += "solutions/";
        file_name += ss.str();
        file_name += ".txt";

        std::remove(file_name.c_str());
        
        std::ofstream f;
        f.open(file_name);

        for (int i = 0; i < codon_count; i++) f << (int) unit1->genome[i] << " ";
        f << std::endl;
        for (int i = 0; i < codon_count; i++) f << (int) unit2->genome[i] << " ";
        f << std::endl;
        f.close();
    }
}