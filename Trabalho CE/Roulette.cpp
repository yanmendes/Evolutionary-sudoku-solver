//
//  Roulette.cpp
//  Trabalho CE
//
//  Created by Yan Mendes on 26/05/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#include "Roulette.hpp"

Roulette::Roulette(vector<Individual*> population){
    this->population = population;
    this->totalFitness = 0;
    
    for(Individual * i : population)
        this->totalFitness += i->getFitness();
}

pair<Individual*, Individual*> Roulette::spin(){
    Individual *p1 = NULL, *p2 = NULL;
    unsigned int r1, r2, currentSum = 0;
    
    r1 = h.generateRandomNumber(0, this->totalFitness);
    r2 = h.generateRandomNumber(0, this->totalFitness);
    
    for(int i = 0; i < this->population.size(); ++i){
        currentSum += population.at(i)->getFitness();
        if(r1 < currentSum && p1 == NULL)
            p1 = population.at(i);
        if(r2 < currentSum && p2 == NULL)
            p2 = population.at(i);
        if(p1 != NULL && p2 != NULL)
            break;
    }
    
    return pair<Individual*, Individual*>(p1, p2);
}

vector<pair<Individual*, Individual*>> Roulette::stochasticUniversalSampling(){
    double distanceBetweenPointers = (double) this->totalFitness / this->population.size();
    double currentSum = h.generateRandomNumber(0, floor(distanceBetweenPointers)); //Offset
    int i = 0;
    unsigned int populationSum = this->population.at(0)->getFitness();
    vector<Individual*> selectedIndividuals;
    vector<pair<Individual*, Individual*>> parents;
    
    while(currentSum <= this->totalFitness){
        while(populationSum < currentSum){
            ++i;
            populationSum += population.at(i)->getFitness();
        }
        
        selectedIndividuals.push_back(population.at(i));
        currentSum += distanceBetweenPointers;
    }
    
    int size = (int) selectedIndividuals.size();
    
    for(i = 0; i < size; ++i)
        parents.push_back(pair<Individual*, Individual*>(selectedIndividuals.at(i), selectedIndividuals.at(size - 1 - i)));
    
    return parents;
}
