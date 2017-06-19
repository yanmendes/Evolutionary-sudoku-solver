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
    unsigned long long int matrixHash;
    long long int fittestIndividualFitness;
    vector<double> averageFitness;
    double elapsedTime;
    string crossoverMethod, mutationMethod, fitnessMethod;
    
    Result(GeneticAlgorithm * g, double elapsedTime){
        this->matrixHash = Helper::createMatrixHash(g->getTemplateIndividual()->getSudokuBoard(), g->getTemplateIndividual()->getLimit());
        this->crossoverMethod = g->getCrossoverMethod();
        this->mutationMethod = g->getMutationMethod();
        this->fitnessMethod = Individual::getCurrentFitnessMethodName();
        this->fittestIndividualFitness = g->getFittest()->getFitness();
        this->generationsPassed = g->getGenerationsPassed();
        this->averageFitness = g->getAverageFitness();
        this->elapsedTime = elapsedTime;
    };
};

#endif /* Result_hpp */
