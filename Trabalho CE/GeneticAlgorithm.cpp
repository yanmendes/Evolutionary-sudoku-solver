//
//  GeneticAlgorithm.cpp
//  Trabalho CE
//
//  Created by Yan Mendes on 24/05/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#include "GeneticAlgorithm.hpp"

GeneticAlgorithm::GeneticAlgorithm(int method, int populationSize, int generations, double mutationFrequency){
    vector<Individual*> population(populationSize, NULL);
    this->generations = generations;
    this->population = population;
    this->mutationFrequency = mutationFrequency;
    this->currentMutationMethod = &GeneticAlgorithm::shuffleRandomSquare;
    this->getCurrentMutationMethodName = &GeneticAlgorithm::shuffleRandoSquaresName;
    
    switch (method) {
        case 1:
            Individual::currentGetter = &Individual::getSquare;
            Individual::currentSetter = &Individual::setSquare;
            this->getCurrentCrossoverMethodName = &GeneticAlgorithm::combineSquaresName;
            break;
        case 2:
            Individual::currentGetter = &Individual::getRow;
            Individual::currentSetter = &Individual::setRow;
            this->getCurrentCrossoverMethodName = &GeneticAlgorithm::combineRowsName;
            break;
        case 3:
            Individual::currentGetter = &Individual::getColumn;
            Individual::currentSetter = &Individual::setColumn;
            this->getCurrentCrossoverMethodName = &GeneticAlgorithm::combineColumnsName;
            break;
        default:
            cout << "Invalid input method" << endl;
            exit(3);
    }
    
    this->generatePopulation();
}

void GeneticAlgorithm::generatePopulation(Individual * templateIndividual){
    for(int i = 0; i < this->population.size(); ++i)
        population.at(i) = (new Individual(templateIndividual))->fillWithRandom();
}

void GeneticAlgorithm::clearPopulation(void){
    int populationSize = (int) this->population.size();
    
    this->population.clear();
    
    vector<Individual*> population(populationSize, NULL);
    
    this->population = population;
}

vector<pair<Individual*, Individual*>> GeneticAlgorithm::getParents(void){
    Roulette * roulette = new Roulette(this->population);
    
    vector<pair<Individual*, Individual*>> parents = roulette->stochasticUniversalSampling();
    
    this->averageFitness.push_back((double) roulette->getTotalFitness() / this->population.size());
    
    return parents;
}
    
bool GeneticAlgorithm::foundSolution(void){
    Individual * fittest = this->getFittest();
    
    return fittest->getFitness() == (fittest->getLimit() * fittest->getLimit());
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
            children.push_back(this->crossover(parents.first, parents.second));
    
        for(Individual * i : children)
            if(h.generateRandomNumber(0, 100) < this->mutationFrequency * 100)
                (this->*currentMutationMethod)(i);
        
        this->clearPopulation();
        
        this->population = children;
        
        children.clear();
    }
    
    this->generationsPassed = i;
}

/*
 *
 * ####### CROSSOVER METHODS #######
 *
 */
Individual * GeneticAlgorithm::crossover(Individual * p1, Individual * p2){
    Individual * ind = new Individual(p1);
    
    for(int i = 0; i < p2->getLimit(); ++i){
        if(i % 2)
            continue;
        else
            (ind->*Individual::currentSetter)(i, h.toArray((p2->*Individual::currentGetter)(i)));
    }
        
    return ind;
}

/*
 *
 * ####### MUTATION METHODS #######
 *
 */
void GeneticAlgorithm::shuffleRandomSquare(Individual * i){
    long int seed = SEED;
    mt19937 mt_rand((unsigned int) seed);
    
    (i->*Individual::currentSetter)(mt_rand() % i->getLimit(), h.generateRandomSequence(i->getLimit()));
}
