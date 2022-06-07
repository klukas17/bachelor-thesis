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
    int selection = std::stoi(argv[5]);

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

    if (selection == 1) {

        float range = 0;
        std::vector<Unit*> new_units;

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

        for (int i = 0; i < elitism_count; i++) {
            new_units.push_back(units[i]->unit);
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

        for (int i = 0; i < new_units.size(); i++) {

            Unit* unit = new_units[i];

            std::stringstream ss;
            ss << i;
            
            std::string file_name; 
            file_name += "solutions/";
            file_name += ss.str();
            file_name += ".txt";
            
            std::ofstream f;
            f.open(file_name);

            for (int i = 0; i < codon_count; i++) f << (int) unit->genome[i] << " ";
            f << std::endl;
            f.close();
        }
    }

    else if (selection == 2) {
        int i1, i2, i3;
        i1 = rand() % population_count;
        do {
            i2 = rand() % population_count;
        } while (i2 != i1);
        do {
            i3 = rand() % population_count;
        } while (i3 != i1 && i3 != i2);

        int best = i1, worst = i1, other;
        if (units[i2]->value > units[i1]->value) best = i2;
        if (units[i2]->value < units[i1]->value) worst = i2;
        if (units[i3]->value > units[i1]->value && units[i3]->value > units[i2]->value) best = i3;
        if (units[i3]->value < units[i1]->value && units[i3]->value < units[i2]->value) worst = i3;
        if (best != i1 && worst != i1) other = i1;
        if (best != i2 && worst != i2) other = i2;
        if (best != i3 && worst != i3) other = i3;

        Unit* u = crossover->perform(units[i1]->unit, units[i2]->unit);
        u = mutation->perform(u);

        std::stringstream ss;
        ss << worst;
        
        std::string file_name; 
        file_name += "solutions/";
        file_name += ss.str();
        file_name += ".txt";
        
        std::ofstream f;
        f.open(file_name);

        for (int i = 0; i < codon_count; i++) f << (int) u->genome[i] << " ";
        f << std::endl;
        f.close();

        std::cout << worst << std::endl;

    }
}