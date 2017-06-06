//
//  GeneticAlgorithm.hpp
//  Trabalho CE
//
//  Created by Yan Mendes on 24/05/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#ifndef GeneticAlgorithm_hpp
#define GeneticAlgorithm_hpp

#include "Individual.hpp"
#include "Helper.hpp"
#include "Roulette.hpp"

using namespace std;

class GeneticAlgorithm{
private:
    //Defining new data types
    typedef Individual * (GeneticAlgorithm::*crossoverMethod)(Individual*, Individual*);
    typedef void (GeneticAlgorithm::*mutationMethod)(Individual*);
    typedef string (GeneticAlgorithm::*getMethodName)(void);
    
    //Attributes
    vector<Individual*> population;
    int generations, generationsPassed;
    double mutationFrequency;
    static Helper h;
    vector<double> averageFitness;
    
    //Population operations
    static bool compFunction(Individual * a, Individual * b) {return a->getFitness() > b->getFitness();};
    void sortPopulation(void) {sort(this->population.begin(), this->population.end(), this->compFunction);};
    vector<pair<Individual*, Individual*>> getParents();
    
    //Domain dependable methods
    void generatePopulation(void) {};
    
    //Crossover method(s)
    crossoverMethod currentCrossoverMethod;
    getMethodName getCurrentCrossoverMethodName;
    Individual * crossover(Individual*, Individual*);
    
        //Combine solved squares
        string combineSquaresName(void) {return "Combine solved squares";};
    
        //Combine solved rows
        string combineRowsName(void) {return "Combine solved rows";};

        //Combine solved columns
        string combineColumnsName(void) {return "Combine solved columns";};
    
    //Mutation method(s)
    mutationMethod currentMutationMethod;
    getMethodName getCurrentMutationMethodName;
    
        //Shuffles a random square
        void shuffleRandomSquare(Individual*);
        string shuffleRandoSquaresName(void) {return "Shuffle random square";};
public:
    //Constructor
    GeneticAlgorithm(int, int, int, int, double);
    
    //Solver
    void solve(void);
    
    //Domain dependable methods
    void generatePopulation(Individual*);
    
    //Auxiliary methods
    void clearPopulation(void);
    Individual * getFittest(void) {this->sortPopulation(); return this->population.at(0);};
    bool foundSolution();
    
    //Analytical data
    string getCrossoverMethod(void) {return (this->*getCurrentCrossoverMethodName)();};
    string getMutationMethod(void) {return (this->*getCurrentMutationMethodName)();};
    int getPopulationSize() {return (int) this->population.size();};
    int getGenerations() {return this->generations;};
    double getMutationFrequency() {return this->mutationFrequency;};
    int getGenerationsPassed() {return this->generationsPassed;};
    vector<double> getAverageFitness() {return this->averageFitness;};
    
    //Destructor
    ~GeneticAlgorithm(){this->population.clear(); this->averageFitness.clear();};
};

#endif /* GeneticAlgorithm_hpp */
