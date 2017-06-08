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
    int fitness, limit;
    vector<int> sudokuBoard, fixedPositions;
    static Helper h;
public:
    //Defining new data types
    typedef vector<int> (Individual::*currentGetterMethod)(int);
    typedef Individual * (Individual::*currentSetterMethod)(int, vector<int>);
    
    static currentGetterMethod currentGetter;
    static currentSetterMethod currentSetter;
    
    //Constructors
    Individual(int, vector<int>);
    Individual(Individual*);
    
    //Auxiliary methods
    Individual * fillWithRandom(void);
    
    //Getters
    int getFitness(void);
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
    
    //Destructor
    ~Individual(void) {this->sudokuBoard.clear(); this->sudokuBoard.shrink_to_fit();
                       this->fixedPositions.clear(); this->fixedPositions.shrink_to_fit();};
};

#endif /* Individual_hpp */
