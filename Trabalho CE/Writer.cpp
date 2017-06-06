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
//    this->outputFile =
//        h.createOutputFileName(g->getCrossoverMethod(), g->getMutationMethod(), i->getSudokuBoard(), i->getLimit());
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
    file << "Mutation frequency: " << g->getMutationFrequency() * 100 << "%" << endl << endl;

    file << "########TEST RESULTS########" << endl;
    file << "Elapsed time: " << elapsedTime << " ms" << endl;
    file << "Fittest individual fitness: " << g->getFittest()->getFitness() << endl;
//    file << "Fittest individual: \n" << h.getMatrix(g->getFittest()->getSudokuBoard(), g->getFittest()->getLimit()) << endl;
    
    file.close();
    
    results.push_back(new Result(g, elapsedTime));
}

void Writer::writeStatistcs(string outputFile){
    fstream file;
    
    file.open(outputFile, fstream::out);

    file << "Crossover Method;Mutation Method;Fittest individual fitness;Generations passed;Elapsed Time;Generation;Average Fitness\n";
    
    for(Result * r : results){
        string e = to_string(r->elapsedTime);
        replace(e.begin(), e.end(), '.', ',');
        
        file << r->crossoverMethod << ";" << r->mutationMethod << ";" << r->fittestIndividualFitness << ";"
        << r->generationsPassed << ";" << e << '\n';
        
        int generation = 1;
        for(double avg : r->averageFitness){
            string a = to_string(avg);
            replace(a.begin(), a.end(), '.', ',');
            
            file << ";" << ";" << ";" << ";" << ";" << generation++ << ";" << a << '\n';
        }
    }
    
    file.close();
}
