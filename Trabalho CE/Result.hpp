//
//  Result.hpp
//  Trabalho IA
//
//  Created by Yan Mendes on 17/05/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#ifndef Result_hpp
#define Result_hpp

#include "Helper.hpp"
#include "GeneticAlgorithm.hpp"

class Result{
public:
    int generationsPassed;
    long long int fittestIndividualFitness;
    vector<double> averageFitness;
    double elapsedTime;
    string crossoverMethod, mutationMethod;
    
    Result(GeneticAlgorithm * g, double elapsedTime){
        this->crossoverMethod = g->getCrossoverMethod();
        this->mutationMethod = g->getMutationMethod();
        this->fittestIndividualFitness = g->getFittest()->getFitness();
        this->generationsPassed = g->getGenerationsPassed();
        this->averageFitness = g->getAverageFitness();
        this->elapsedTime = elapsedTime;
    };
};

#endif /* Result_hpp */
