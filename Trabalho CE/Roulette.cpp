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
    this->totalFitness = this->normalizedFitness = 0;
    long long int offset;
    
    for(Individual * i : population)
        this->totalFitness += i->getFitness();
    
    //In case of minimization functions, normalize the fitness so it can spin on the roullete
    if((offset = population.back()->getFitness()) < 0)
        for(Individual * ind : this->population){
            ind->setFitness(ind->getFitness() + (offset * -1) + 1);
            this->normalizedFitness += ind->getFitness();
        }
    else
        this->normalizedFitness = this->totalFitness;
}

pair<Individual*, Individual*> Roulette::spin(){
    Individual *p1 = NULL, *p2 = NULL;
    long long int r1, r2, currentSum = 0;
    
    r1 = h.generateRandomNumber(0, this->normalizedFitness);
    r2 = h.generateRandomNumber(0, this->normalizedFitness);
    
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
    double distanceBetweenPointers = (double) this->normalizedFitness / this->population.size(),
           currentSum = h.generateRandomNumber(0, floor(distanceBetweenPointers)); //Offset
    int i = 0;
    
    long long int populationSum = this->population.at(0)->getFitness();
    vector<Individual*> selectedIndividuals;
    vector<pair<Individual*, Individual*>> parents;
    
    while(currentSum <= this->normalizedFitness && selectedIndividuals.size() < this->population.size()){
        while(populationSum < currentSum)
            populationSum += population.at(i++)->getFitness();
        
        selectedIndividuals.push_back(population.at(i));
        currentSum += distanceBetweenPointers;
    }
    
    int size = (int) selectedIndividuals.size();
    
    std::random_shuffle(selectedIndividuals.begin(), selectedIndividuals.end());
    
    for(i = 0; i < size - 1; ++i)
        if(selectedIndividuals.at(i) == selectedIndividuals.at(i + 1) && i < size - 2)
            swap(selectedIndividuals.at(i + 1), selectedIndividuals.at(i + 2));
    
    for(i = 0; i < size - 1; ++i)
        parents.push_back(pair<Individual*, Individual*>(selectedIndividuals.at(i), selectedIndividuals.at(i + 1)));
    
    return parents;
}
