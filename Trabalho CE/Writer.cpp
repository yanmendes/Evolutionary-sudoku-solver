//
//  Writer.cpp
//  Trabalho IA
//
//  Created by Yan Mendes on 08/05/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#include "Writer.hpp"

static vector<Result*> results;

Writer::Writer(Individual * i, GeneticAlgorithm * g){
    this->outputFile =
        h.createOutputFileName(g->getCrossoverMethod(), g->getMutationMethod(), Individual::currentFitnessMethodName(),
                               i->getSudokuBoard(), i->getLimit());
    this->g = g;
}

void Writer::writeResults(double elapsedTime){
    fstream file;
    
    file.open(this->outputFile, fstream::out);
    
    file << "Running solver @ " << h.getCurrentTimeStamp() << endl;
    file << "########TEST PARAMS########" << endl;
    file << "Population size: " << g->getPopulationSize() << endl;
    file << "Number of generations passed: " << g->getGenerationsPassed() << endl;
    file << "Crossover method: " << g->getCrossoverMethod() << endl;
    file << "Mutation method: " << g->getMutationMethod() << endl;
    file << "Mutation frequency: " << g->getMutationFrequency() << "%" << endl;
    file << "Preserved population percentage: " << g->getPreservedPopulationPercentage() << "%" << endl << endl;

    file << "########TEST RESULTS########" << endl;
    file << "Elapsed time: " << elapsedTime << "s" << endl;
    file << "Last generation average fitness: " << g->getAverageFitness().back() << endl;
    file << "Fittest individual fitness: " << g->getFittest()->getFitness() << endl;
    file << "Fittest individual amount of correct numbers: " << g->getFittest()->numberOfWrongNumbers() << endl;
    file << "Fittest individual: \n" << h.getMatrix(g->getFittest()->getSudokuBoard(), g->getFittest()->getLimit()) << endl;
    
    file.close();
    
    results.push_back(new Result(g, elapsedTime));
}

void Writer::writeStatistcs(string outputFile){
    fstream file;
    
    file.open(outputFile, fstream::out);

    file << "Instance;Fitness Method;Crossover Method;Mutation Method;Max Generations;Population Size; Mutation Frequency;Preserved Population Percentage;Fittest individual fitness;First Generation Average Fitness;Last Generation Average Fitness;Fittest Individual Amount of Right Numbers;Generations passed;Elapsed Time(s)\n";
    
    for(Result * r : results){
        string e = to_string(r->elapsedTime);
        replace(e.begin(), e.end(), '.', ',');
        
        file << r->matrixHash << ";" << r->fitnessMethod << ";" << r->crossoverMethod << ";" << r->mutationMethod << ";" <<
        Parameters::GENERATIONS << ";" << Parameters::POPULATION_SIZE << ";" << Parameters::MUTATION_FREQUENCY << ";" <<
        Parameters::PRESERVED_POPULATION_PERCENTAGE << ";" << r->fittestIndividualFitness << ";" << r->averageFitness.front() <<
        ";" << r->averageFitness.back() << ";" << r->fittestIndividualAmountOfRightNumbers << ";" << r->generationsPassed << ";" << e << '\n';
    }
    
    file.close();
}
