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

vector<pair<Individual*, Individual*>> GeneticAlgorithm::selectParents(void){
    Roulette * roulette = new Roulette(this->population);
    
    vector<pair<Individual*, Individual*>> parents = roulette->stochasticUniversalSampling();
    
    this->averageFitness.push_back((double) roulette->getTotalFitness() / this->population.size());
    
    delete roulette;
    
    return parents;
}

void GeneticAlgorithm::mergePopulation(vector<Individual *> children){
    sort(children.begin(), children.end(), this->reverseCompFunction);
        
    int iterations = (1 - this->preservedPopulationPercentage) * this->population.size();
    for(int i = 0; i < iterations; ++i){
        Individual * ind = this->population.back();
        delete ind;
        this->population.pop_back();
    }
        
    for(int i = 0; i < iterations; ++i){
        this->population.push_back(children.back());
        children.pop_back();
    }
        
    for(Individual * i : children)
        delete i;
        
    children.clear();
    children.shrink_to_fit();
}

void GeneticAlgorithm::solve(void){
    vector<pair<Individual*, Individual*>> parentsVector;
    vector<Individual*> children;
    int i;
    
    for(i = 0; i < generations; ++i){
        if(this->foundSolution())
            break;
        
        //Selection
        parentsVector = this->selectParents();
        
        //Recombination
        for(auto const parents : parentsVector)
            children.push_back((this->*currentCrossoverMethod)(parents.first, parents.second));
    
        //Mutation
        for(Individual * i : children)
            if(h.generateRandomNumber(0, 100) < this->mutationFrequency * 100)
                (this->*currentMutationMethod)(i);
        
        //Generate new population
        this->mergePopulation(children);
        
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
                                   double mutationFrequency, double preservedPopulationPercentage){
    vector<Individual*> population(populationSize, NULL);
    this->generations = generations; this->population = population;
    this->mutationFrequency = mutationFrequency; this->preservedPopulationPercentage = preservedPopulationPercentage;
    
    switch (crossoverMethod) {
        case 1:
            this->currentCrossoverMethod = &GeneticAlgorithm::crossover;
            Individual::currentGetter = &Individual::getSquare;
            Individual::currentSetter = &Individual::setSquare;
            this->getCurrentCrossoverMethodName = &GeneticAlgorithm::combineSquaresName;
            break;
        case 2:
            this->currentCrossoverMethod = &GeneticAlgorithm::crossover;
            Individual::currentGetter = &Individual::getRow;
            Individual::currentSetter = &Individual::setRow;
            this->getCurrentCrossoverMethodName = &GeneticAlgorithm::combineRowsName;
            break;
        case 3:
            this->currentCrossoverMethod = &GeneticAlgorithm::crossover;
            Individual::currentGetter = &Individual::getColumn;
            Individual::currentSetter = &Individual::setColumn;
            this->getCurrentCrossoverMethodName = &GeneticAlgorithm::combineColumnsName;
            break;
        default:
            cout << "Invalid input crossover method" << endl;
            exit(3);
    }
    
    switch (mutationMethod) {
        case 1:
            this->currentMutationMethod = &GeneticAlgorithm::shuffleRandomSquare;
            this->getCurrentMutationMethodName = &GeneticAlgorithm::shuffleRandoSquaresName;
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
    
    return fittest->getFitness() == (fittest->getLimit() * fittest->getLimit());
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

void GeneticAlgorithm::shuffleRandomSquare(Individual * i){
    long int seed = SEED;
    mt19937 mt_rand((unsigned int) seed);
    
    (i->*Individual::currentSetter)(mt_rand() % i->getLimit(), h.generateRandomSequence(i->getLimit()));
}
