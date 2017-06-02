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
    int fitness;
    int limit;
    int * sudokuBoard;
    vector<int> fixedPositions;
    static Helper h;
public:
    //Defining new data types
    typedef vector<int> (Individual::*currentGetterMethod)(int);
    typedef Individual * (Individual::*currentSetterMethod)(int, int*);
    
    static currentGetterMethod currentGetter;
    static currentSetterMethod currentSetter;
    
    Individual(int, int*);
    Individual(Individual*);
    
    int getFitness();
    Individual * fillWithRandom(void);
    
    ~Individual() {delete [] this->sudokuBoard; fixedPositions.clear();};
    
    //Getters
    int getLimit() {return this->limit;};
    int * getSudokuBoard() {return this->sudokuBoard;};
    vector<int> getFixedPositions() {return this->fixedPositions;};
    
        //Element getters
        vector<int> getSquare(int);
        vector<int> getRow(int);
        vector<int> getColumn(int);
    
    //Setters
    Individual * setSquare(int, int*);
    Individual * setRow(int, int*);
    Individual * setColumn(int, int*);
};

#endif /* Individual_hpp */
