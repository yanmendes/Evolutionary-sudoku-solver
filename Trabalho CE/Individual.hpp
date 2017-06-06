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
    int fitness, limit, *sudokuBoard;
    vector<int> fixedPositions;
    static Helper h;
public:
    //Defining new data types
    typedef vector<int> (Individual::*currentGetterMethod)(int);
    typedef Individual * (Individual::*currentSetterMethod)(int, int*);
    
    static currentGetterMethod currentGetter;
    static currentSetterMethod currentSetter;
    
    //Constructors
    Individual(int, int*);
    Individual(Individual*);
    
    //Auxiliary methods
    Individual * fillWithRandom(void);
    
    //Getters
    int getFitness(void);
    int getLimit(void) {return this->limit;};
    int * getSudokuBoard(void) {return this->sudokuBoard;};
    vector<int> getFixedPositions(void) {return this->fixedPositions;};
    
        //Element getters
        vector<int> getSquare(int);
        vector<int> getRow(int);
        vector<int> getColumn(int);
    
    //Setters
    Individual * setSquare(int, int*);
    Individual * setRow(int, int*);
    Individual * setColumn(int, int*);
    
    //Destructor
    ~Individual(void) {delete [] this->sudokuBoard; fixedPositions.clear();};
};

#endif /* Individual_hpp */
