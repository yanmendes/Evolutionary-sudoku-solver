//
//  main.cpp
//  Trabalho CE
//
//  Created by Yan Mendes on 27/04/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#include "Reader.hpp"
#include "Writer.hpp"
#include "GeneticAlgorithm.hpp"

bool dev = true;
int populationSize = 100, generations = 500;
double mutationFrequency = 0.2;
string
    inputFile = "/Users/yanmendes/Documents/Faculdades/Ufjf/Computação\ Evolucionista/i.in",
    outputFolder = "/Users/yanmendes/Documents/Faculdades/Ufjf/Computação\ Evolucionista/Output/";
vector<int> methods;
Helper h;

static void usage(){
    cout << "Usage:\n" <<
    "    ./Trabalho CE [options] -i $input/file/path$ -o $output/folder/path$ CrossoverMethods\n\n" <<
    "Options:\n" <<
    "    -h     Show this help\n" <<
    "    -p     Population size\n" <<
    "    -g     Number of generations\n" <<
    "    -m     Mutation frequency\n" <<
    "Crossover method:\n" <<
    "    1      Combine solved squares\n" <<
    "    2      Combine solved rows\n" <<
    "    3      Combine solved columns\n" <<
    "    all    All methods\n";
}

int processArgs(int argc, const char * argv[]){
    if(argc < 2){
        usage();
        return 2;
    }
    
    int argInd;
    
    for(argInd = 1; argInd < argc; ++argInd) {
        if (argv[argInd][0] != '-')
            break;
        
        if (!strcmp(argv[argInd], "-h")) {
            usage();
            return 2;
        } else if (!strcmp(argv[argInd], "-i"))
            inputFile = argv[++argInd];
        else if (!strcmp(argv[argInd], "-o"))
            outputFolder = argv[++argInd];
        else if (!strcmp(argv[argInd], "-p"))
            populationSize = atoi(argv[++argInd]);
        else if (!strcmp(argv[argInd], "-g"))
            generations = atoi(argv[++argInd]);
        else if (!strcmp(argv[argInd], "-m"))
            generations = atof(argv[++argInd]);
    }
    
    if(!strcmp (argv[argInd], "all")) {
        methods.push_back(1);
        methods.push_back(2);
        methods.push_back(3);
    } else
        for(argInd = argInd; argInd < argc; ++argInd)
            methods.push_back(atoi(argv[argInd]));
    
    return 0;
}

int main(int argc, const char * argv[]) {
    int errors;
    
    srand((unsigned int) time(0));
    
    if(dev){
        methods.push_back(1);
        methods.push_back(2);
        methods.push_back(3);
    }else if((errors = processArgs(argc, argv)))
        return errors;
    
    Parameters::GENERATIONS = generations;
    Parameters::MUTATION_FREQUENCY = mutationFrequency * 100;
    Parameters::POPULATION_SIZE = populationSize;
    Parameters::OUTPUT_FOLDER = outputFolder;
    Helper::generateExecutionId();
    
    cout << "- - - - - - Processing the input - - - - - - " << endl;
    vector<Individual*> boards = (new Reader())->parseSudokus(inputFile);
    cout << "- - - - - - Done processing the input - - - - - - " << endl << endl;
    
    for(int method : methods){
        GeneticAlgorithm * g = new GeneticAlgorithm(method, populationSize, generations, mutationFrequency);
        cout << "- - - - - - Selected Method: " << g->getCrossoverMethod() << " - - - - - - " << endl;
        
        for(Individual * i : boards){
            Writer * w = new Writer(i, g);
            
            cout << "- - - - - - Generating population - - - - - - " << endl;
            g->generatePopulation(i);
            cout << "- - - - - - Done generating population - - - - - - " << endl;
            
            cout << "- - - - - - Starting to solve - - - - - - " << endl;
            clock_t beforeSolve = clock();
            g->solve();
            clock_t afterSolve  = clock();
            cout << "- - - - - - Finished solving - - - - - - " << endl << endl;
            
            w->writeResults(afterSolve - beforeSolve);
            
            g->clearPopulation();
        }
    }
    
    Writer::writeStatistcs(Helper::executionId + "statistics.csv");
    
    return 0;
}
