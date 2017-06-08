//
//  GeneticAlgorithm.cpp
//  Trabalho CE
//
//  Created by Yan Mendes on 24/05/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#include "GeneticAlgorithm.hpp"

/*************NO NEED TO REWRITE THE FOLLOWING METHODS*************/

void GeneticAlgorithm::clearPopulation(void){
    int populationSize = (int) this->population.size();
    
    for(Individual * i : this->population)
        delete (i);

    this->population.clear();
    this->population.shrink_to_fit();
    
    this->population.resize(populationSize);
}

vector<pair<Individual*, Individual*>> GeneticAlgorithm::getParents(void){
    Roulette * roulette = new Roulette(this->population);
    
    vector<pair<Individual*, Individual*>> parents = roulette->stochasticUniversalSampling();
    
    this->averageFitness.push_back((double) roulette->getTotalFitness() / this->population.size());
    
    delete roulette;
    
    return parents;
}

void GeneticAlgorithm::solve(void){
    vector<pair<Individual*, Individual*>> parentsVector;
    vector<Individual*> children;
    int i;
    
    for(i = 0; i < generations; ++i){
        if(this->foundSolution())
            break;
        
        parentsVector = this->getParents();
        
        for(auto const parents : parentsVector)
            children.push_back((this->*currentCrossoverMethod)(parents.first, parents.second));
    
        for(Individual * i : children)
            if(h.generateRandomNumber(0, 100) < this->mutationFrequency * 100)
                (this->*currentMutationMethod)(i);
        
        this->clearPopulation();
        
        this->population = children;
        
        children.clear();
    }
    
    this->generationsPassed = i;
}

GeneticAlgorithm::~GeneticAlgorithm(void){
    for(Individual * i : this->population)
        delete (i);
    
    this->population.clear();
    this->population.shrink_to_fit();
    
    this->averageFitness.clear();
    this->averageFitness.shrink_to_fit();
}

/*************DOMAIN DEPENDABLE METHODS*************/

/**
 * Change the function pointers to match your solution
 *
 * @param crossoverMethod int Crossover method to be applied
 * @param mutationMethod int Mutation method to be applied
 * @param populationSize int The population size
 * @param generations int Number of generations
 * @param mutationFrequency int Mutation frequency
 */
GeneticAlgorithm::GeneticAlgorithm(int crossoverMethod, int mutationMethod, int populationSize, int generations,
                                   double mutationFrequency){
    vector<Individual*> population(populationSize, NULL);
    this->generations = generations; this->population = population; this->mutationFrequency = mutationFrequency;
    
    switch (crossoverMethod) {
        case 1:
//            this->currentCrossoverMethod = &GeneticAlgorithm::crossoverMethod1;
//            this->getCurrentCrossoverMethodName = &GeneticAlgorithm::crossoverMethod1Name;
            break;
        default:
            cout << "Invalid input crossover method" << endl;
            exit(3);
    }
    
    switch (mutationMethod) {
        case 1:
//            this->currentMutationMethod = &GeneticAlgorithm::mutationMethod1;
//            this->getCurrentMutationMethodName = &GeneticAlgorithm::mutationMethod1Name;
            break;
        default:
            cout << "Invalid input mutation method" << endl;
            exit(4);
    }
    
    this->generatePopulation();
}

/*
 * Optional method to be implemented - depends heavily on the domain you're working with
 * e.g. Found a sudoku board solution
 *
 * @return bool Solution has been found?
 */
bool GeneticAlgorithm::foundSolution(void){
    Individual * fittest = this->getFittest();

    return true;
//    return isSolution(fittest);
}

/*
 * Optional method to be implemented - depends heavily on the domain you're working with;
 * Use it when you need a template individual to generate the population
 * e.g. Sudoku board with the dfixed values
 */
void GeneticAlgorithm::generatePopulation(Individual * templateIndividual){
    for(int i = 0; i < this->population.size(); ++i)
        population.at(i) = (new Individual(templateIndividual))->fillWithRandom();
}

/*************CROSSOVER METHODS*************/

Individual * GeneticAlgorithm::crossover(Individual * p1, Individual * p2){
    Individual * ind = new Individual(p1);
    
    for(int i = 0; i < p2->getLimit(); ++i){
        if(i % 2)
            continue;
        else
            (ind->*Individual::currentSetter)(i, (p2->*Individual::currentGetter)(i));
    }
        
    return ind;
}

/*************MUTATION METHODS*************/

