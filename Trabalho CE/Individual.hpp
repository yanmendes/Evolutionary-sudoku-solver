//
//  Individual.hpp
//  Trabalho CE
//
//  Created by Yan Mendes on 24/05/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#ifndef Individual_hpp
#define Individual_hpp

#include "Helper.hpp"

class Individual{
private:
    //Attributes
    int limit;
    long long int fitness;
    vector<int> sudokuBoard, fixedPositions;
    static Helper h;
public:
    //Defining new data types
    typedef vector<int> (Individual::*currentGetterMethod)(int);
    typedef Individual * (Individual::*currentSetterMethod)(int, vector<int>);
    typedef long long int (Individual::*fitnessMethod)(void);
    typedef string (*getMethodName)(void);
    
    static currentGetterMethod currentGetter;
    static currentSetterMethod currentSetter;
    static fitnessMethod currentFitnessMethod;
    static getMethodName currentFitnessMethodName;
    
    //Constructors
    Individual(int, vector<int>);
    Individual(Individual*);
    
    //Auxiliary methods
    Individual * fillWithRandom(void);
    Individual * resetFitness(void) {this->fitness = -1; this->getFitness(); return this;};
    static string getCurrentFitnessMethodName();
    
    //Getters
    long long int getFitness(void);
    int getLimit(void) {return this->limit;};
    vector<int> getSudokuBoard(void) {return this->sudokuBoard;};
    vector<int> getFixedPositions(void) {return this->fixedPositions;};
    
        //Element getters
        vector<int> getSquare(int);
        vector<int> getRow(int);
        vector<int> getColumn(int);
    
    //Setters
    Individual * setSquare(int, vector<int>);
    Individual * setRow(int, vector<int>);
    Individual * setColumn(int, vector<int>);
    Individual * setFitness(long long int);
    
    //Fitness method(s)
        long long int numberOfWrongNumbers(void);
        static string numberOfWrongNumbersName(void) {return "Number of wrong numbers";};
        static int maxFitnessWrongNumbers(void);
        long long int mantereKoljonenOptimizationFunction(void);
        static string mantereKoljonenOptimizationFunctionName(void) {return "Mantere and Koljen optmization function";};
        static int maxFitnessKoljonenOptimizationFunction(void);
    
    //Destructor
    ~Individual(void) {this->sudokuBoard.clear(); this->sudokuBoard.shrink_to_fit();
                       this->fixedPositions.clear(); this->fixedPositions.shrink_to_fit();};
};

#endif /* Individual_hpp */
