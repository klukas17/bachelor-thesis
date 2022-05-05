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
        Unit* unit;

        Container(int v, int c, int i, Unit* u) {
            value = v;
            coef = c;
            index = i;
            unit = u;
        }
};

float A = 1.0f;
float B = 10.0f;

int main(int argc, char* argv[]) {
    int population_count = std::stoi(argv[1]);
    int codon_count = std::stoi(argv[2]);
    float mutation_rate = 1 / (float) std::stoi(argv[3]);
    int elitism_count = std::stoi(argv[4]);

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

        Unit* unit = new Unit(codon_count);

        std::ifstream input(file_name);
        std::string line;

        std::vector<unsigned char> v;

        std::istringstream iss;
        std::string s;

        getline(input, line);
        iss = std::istringstream(line);
        while (getline(iss, s, ' ')) v.push_back(std::stoi(s));

        unit->genome = v;

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

        Container* t = new Container(result, 0, i, unit);

        units.push_back(t);
    }

    std::sort(units.begin(), units.end(), 
    [](Container* a, Container* b) {
        if (a->value != b->value) return a->value > b->value;
        else return a->index < b->index;
    });

    float min, max;
    max = units[0]->value;
    min = units.rbegin()[0]->value;

    //std::cout << "MIN: " << min << "\t\tMAX: " << max << std::endl;

    for (auto i : units) std::cout << i->value << " ";
    std::cout << std::endl;

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

    //std::cerr << "CURR GEN:" << std::endl;
    for (int i = 0; i < units.size(); i++) {
        //std::cerr << i + 1 << ":\t\t";
        for (int j = 0; j < units[i]->unit->codon_count; j++) {
            //std::cout << (unsigned int) units[i]->unit->genome[j] << " ";
        }
        //std::cerr << std::endl;
    }

    std::vector<Unit*> new_units;
    for (int i = 0; i < elitism_count; i++) {
        new_units.push_back(units[i]->unit);
        //std::cout << "ELITISM: " << i << " " << units[i]->value << std::endl;
    }

    while (new_units.size() < population_count) {
        float r1, r2;

        r1 = (rand() / (float) RAND_MAX) * range;
        r2 = (rand() / (float) RAND_MAX) * range;

        int i1 = 0, i2 = 0;

        while (r1 > units[i1]->coef) i1++;
        while (r2 > units[i2]->coef) i2++;

        Unit* u = crossover->perform(units[i1]->unit, units[i2]->unit);

        u = mutation->perform(u);

        new_units.push_back(u);
    }

    //std::cerr << "NEXT GEN:" << std::endl;
    for (int i = 0; i < new_units.size(); i++) {
        //std::cerr << i + 1 << ":\t\t";
        for (int j = 0; j < new_units[i]->codon_count; j++) {
            //std::cerr << (unsigned int) new_units[i]->genome[j] << " ";
        }
        //std::cerr << std::endl;
    }

    for (int i = 0; i < new_units.size(); i++) {

        Unit* unit = new_units[i];

        std::stringstream ss;
        ss << i;
        
        std::string file_name; 
        file_name += "solutions/";
        file_name += ss.str();
        file_name += ".txt";

        //std::cout << file_name << std::endl;

        //std::remove(file_name.c_str());
        
        std::ofstream f;
        f.open(file_name);

        for (int i = 0; i < codon_count; i++) f << (int) unit->genome[i] << " ";
        f << std::endl;
        f.close();
    }
}