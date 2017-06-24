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

bool dev = false;
int populationSize = 2000, generations = 500;
double mutationFrequency = 40, preservedPopulationPercentage = 20;
string
    inputFile = "/Users/yanmendes/Documents/Faculdades/Ufjf/Computação\ Evolucionista/i.in",
    outputFolder = "/Users/yanmendes/Documents/Faculdades/Ufjf/Computação\ Evolucionista/Output/";
vector<int> crossoverMethods, mutationMethods, fitnessMethods;
Helper h;

static void usage(){
    cout << "Usage:\n" <<
    "    ./Trabalho CE [options] -i $input/file/path$ -o $output/folder/path$ -c CrossoverMethods -m MutationMethods -f FitnessMethods\n\n" <<
    "Options:\n" <<
    "    -h     Show this help\n" <<
    "    -s     Population size\n" <<
    "    -g     Number of generations\n" <<
    "    -mf    Mutation frequency\n" <<
    "    -p     Preserved population percentage\n" <<
    "Crossover methods:\n" <<
    "    1      Combine solved squares\n" <<
    "    2      Combine solved rows\n" <<
    "    3      Combine solved columns\n" <<
    "    all    All methods\n"
    "Mutation methods:\n" <<
    "    1      Shuffle random square|row|column\n" <<
    "    2      Shuffle random positions in square|row|column\n" <<
    "    all    All methods\n"
    "Fitness methods:\n" <<
    "    1      Number of wrong numbers\n" <<
    "    2      Mantere and Koljen optmization function\n" <<
    "    all    All methods\n";
}

int processArgs(int argc, const char * argv[]){
    if(argc < 2){
        usage();
        return 2;
    }
    
    int argInd;
    
    for(argInd = 1; argInd < argc; ++argInd) {
        if (!strcmp(argv[argInd], "-c") || !strcmp(argv[argInd], "-m") || !strcmp(argv[argInd], "-f"))
            break;
        else if (!strcmp(argv[argInd], "-h")) {
            usage();
            return 2;
        } else if (!strcmp(argv[argInd], "-i"))
            inputFile = argv[++argInd];
        else if (!strcmp(argv[argInd], "-o"))
            outputFolder = argv[++argInd];
        else if (!strcmp(argv[argInd], "-s"))
            populationSize = atoi(argv[++argInd]);
        else if (!strcmp(argv[argInd], "-g"))
            generations = atoi(argv[++argInd]);
        else if (!strcmp(argv[argInd], "-mf"))
            generations = atof(argv[++argInd]);
        else if (!strcmp(argv[argInd], "-p"))
            preservedPopulationPercentage = atof(argv[++argInd]);
    }
    
    if(!strcmp(argv[argInd], "-c")){
        ++argInd;
        if(!strcmp (argv[argInd], "all")) {
            crossoverMethods.push_back(1);
            crossoverMethods.push_back(2);
            crossoverMethods.push_back(3);
        } else
            for(argInd = argInd; argInd < argc; ++argInd)
                crossoverMethods.push_back(atoi(argv[argInd]));
    }
    
    if(!strcmp(argv[argInd], "-m")){
        ++argInd;
        if(!strcmp (argv[argInd], "all")) {
            mutationMethods.push_back(1);
            mutationMethods.push_back(2);
        } else
            for(argInd = argInd; argInd < argc; ++argInd)
                mutationMethods.push_back(atoi(argv[argInd]));
    }
    
    if(!strcmp(argv[argInd], "-f")){
        ++argInd;
        if(!strcmp (argv[argInd], "all")) {
            fitnessMethods.push_back(1);
            fitnessMethods.push_back(2);
        } else
            for(argInd = argInd; argInd < argc; ++argInd)
                fitnessMethods.push_back(atoi(argv[argInd]));
    }
    
    if(crossoverMethods.empty() || mutationMethods.empty() || fitnessMethods.empty()){
        cout << "No crossover|mutation|fitness methods selected";
        usage();
        return 2;
    }
    
    if(mutationFrequency < 1)
        mutationFrequency *= 100;
    
    if(preservedPopulationPercentage < 1)
        preservedPopulationPercentage *= 100;
    
    return 0;
}

int main(int argc, const char * argv[]) {
    int errors;
    
    srand((unsigned int) time(0));
    
    if(dev){
        crossoverMethods.push_back(1);
        crossoverMethods.push_back(2);
        crossoverMethods.push_back(3);
        
        mutationMethods.push_back(1);
        mutationMethods.push_back(2);
        
        fitnessMethods.push_back(1);
        fitnessMethods.push_back(2);
    }else if((errors = processArgs(argc, argv)))
        return errors;
    
    Parameters::GENERATIONS = generations;
    Parameters::MUTATION_FREQUENCY = mutationFrequency;
    Parameters::PRESERVED_POPULATION_PERCENTAGE = preservedPopulationPercentage;
    Parameters::POPULATION_SIZE = populationSize;
    Parameters::OUTPUT_FOLDER = outputFolder;
    Helper::generateExecutionId();
    
    cout << "- - - - - - Processing the input - - - - - - " << endl;
    vector<Individual*> boards = (new Reader())->parseSudokus(inputFile);
    cout << "- - - - - - Done processing the input - - - - - - " << endl << endl;
    
    for(int crossoverMethod : crossoverMethods){
        for(int mutationMethod : mutationMethods){
            for(int fitnessMethod : fitnessMethods){
                GeneticAlgorithm * g = new GeneticAlgorithm(crossoverMethod, mutationMethod, fitnessMethod, populationSize, generations, mutationFrequency, preservedPopulationPercentage);
                cout << "- - - - - - Selected Crossover Method: " << g->getCrossoverMethod() << " - - - - - - " << endl;
                cout << "- - - - - - Selected Mutation Method: " << g->getMutationMethod() << " - - - - - - " << endl;
                cout << "- - - - - - Selected Fitness Method: " << Individual::getCurrentFitnessMethodName() << " - - - - - - "
                     << endl;
                
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
                    
                    w->writeResults((float) (afterSolve - beforeSolve) / CLOCKS_PER_SEC);
                    
                    g->clearPopulation();
                }
                
                delete g;
            }
        }
    }
    
    Writer::writeStatistcs(Helper::executionId + "statistics.csv");
    
    return 0;
}
