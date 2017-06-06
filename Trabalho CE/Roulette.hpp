//
//  Roulette.hpp
//  Trabalho CE
//
//  Created by Yan Mendes on 26/05/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#ifndef Roulette_hpp
#define Roulette_hpp

#include <stdio.h>
#include "Individual.hpp"

using namespace std;

class Roulette{
private:
    vector<Individual*> population;
    unsigned int totalFitness;
    Helper h;
public:
    Roulette(vector<Individual*>);
    pair<Individual*, Individual*> spin();
    vector<pair<Individual*, Individual*>> stochasticUniversalSampling();
    unsigned int getTotalFitness() {return this->totalFitness;};
    ~Roulette(){this->population.clear();};
};

#endif /* Roulette_hpp */
