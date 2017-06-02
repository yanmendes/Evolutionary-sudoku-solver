//
//  Individual.cpp
//  Trabalho CE
//
//  Created by Yan Mendes on 24/05/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#include "Individual.hpp"

Individual::currentGetterMethod Individual::currentGetter;
Individual::currentSetterMethod Individual::currentSetter;

Individual::Individual(int limit, int * matrix){
    this->limit = limit;
    this->sudokuBoard = matrix;
    
    for(int i = 0; i < this->limit * this->limit; ++i)
        if(matrix[i])
            this->fixedPositions.push_back(i);
}

Individual::Individual(Individual * templateIndividual){
    this->limit = templateIndividual->limit;
    this->sudokuBoard = new int[this->limit * this->limit];
    this->fitness = -1;
    
    for(int i : templateIndividual->getFixedPositions())
        this->fixedPositions.push_back(i);
    
    for(int i = 0; i < this->limit * this->limit; ++i)
        this->sudokuBoard[i] = templateIndividual->sudokuBoard[i];
}

Individual * Individual::fillWithRandom(){
    vector<int> square;
    int * randomSequence = nullptr;
    
    for(int i = 0; i < this->limit; ++i){
        //Generates a random sequence
        randomSequence = h.generateRandomSequence(this->limit);
        
        (this->*currentSetter)(i, randomSequence);
    }
    
    return this;
}

vector<int> Individual::getSquare(int squareNumber){
    int sqrtLimit = sqrt(this->limit);
    int offset = (squareNumber/sqrtLimit) * this->limit * sqrtLimit + (squareNumber % sqrtLimit) * sqrtLimit;
    vector<int> square;
    
    for(int j = 0; j < this->limit; ++j){
        if(j && !(j % sqrtLimit))
             offset += (this->limit - sqrtLimit);
        
        square.push_back(this->sudokuBoard[j + offset]);
    }
    
    return square;
}

vector<int> Individual::getRow(int rowNumber){
    return h.toVector(h.slice(sudokuBoard, rowNumber * limit, rowNumber * limit + limit - 1), limit);
}

vector<int> Individual::getColumn(int colNumber){
    return h.toVector(h.slice(sudokuBoard, colNumber, limit * limit - (limit - colNumber), limit), limit);
}

Individual * Individual::setSquare(int squareNumber, int * values){
    int sqrtLimit = sqrt(this->limit);
    int offset = (squareNumber/sqrtLimit) * this->limit * sqrtLimit + (squareNumber % sqrtLimit) * sqrtLimit;
    
    //Corrects the square with the fixed values from the board
    for(int j = 0; j < this->limit; ++j){
        if(j && !(j % sqrtLimit))
            offset += this->limit - sqrtLimit;
        
        int matrixPosition = j + offset;
    
        if(binary_search(this->fixedPositions.begin(), this->fixedPositions.end(), matrixPosition)
                              && this->sudokuBoard[matrixPosition] != values[j])
            swap(values[j], values[h.find(values, limit, this->sudokuBoard[matrixPosition])]);
    }
    
    offset = (squareNumber/sqrtLimit) * this->limit * sqrtLimit + (squareNumber % sqrtLimit) * sqrtLimit;
    for(int j = 0; j < this->limit; ++j){
        if(j && !(j % sqrtLimit))
            offset += this->limit - sqrtLimit;
        
        this->sudokuBoard[j + offset] = values[j];
    }
    
    return this;
}

Individual * Individual::setRow(int rowNumber, int * values){
    //Corrects the row with the fixed values from the board
    for(int j = 0; j < this->limit; ++j){
        int matrixPosition = rowNumber * this->limit + j;
        
        if(binary_search(this->fixedPositions.begin(), this->fixedPositions.end(), matrixPosition)
           && this->sudokuBoard[matrixPosition] != values[j])
            swap(values[j], values[h.find(values, limit, this->sudokuBoard[matrixPosition])]);
    }
    
    for(int j = 0; j < this->limit; ++j)
        this->sudokuBoard[rowNumber * this->limit + j] = values[j];
    
    return this;
}

Individual * Individual::setColumn(int colNumber, int * values){
    for(int j = 0; j < this->limit; ++j){
        int matrixPosition = j * this->limit + colNumber;
        
        if(binary_search(this->fixedPositions.begin(), this->fixedPositions.end(), matrixPosition)
           && this->sudokuBoard[matrixPosition] != values[j])
            swap(values[j], values[h.find(values, limit, this->sudokuBoard[matrixPosition])]);
    }
    
    for(int j = 0; j < this->limit; ++j)
        this->sudokuBoard[j * this->limit + colNumber] = values[j];

    return this;
}

int Individual::getFitness(){
    if(this->fitness != -1)
        return this->fitness;
    
    int wrongNumbers = this->limit * this->limit;
    
    for(int i = 0; i < this->limit; ++i){
        //Checks for duplicates in each row
        wrongNumbers -= h.getNumberOfDuplicates(h.toArray(this->getRow(i)), this->limit);
        
        //Checks for duplicates in each column
        wrongNumbers -= h.getNumberOfDuplicates(h.toArray(this->getColumn(i)), this->limit);
        
        //Checks for duplicates in each square
        wrongNumbers -= h.getNumberOfDuplicates(h.toArray(this->getSquare(i)), this->limit);
    }
    
    this->fitness = wrongNumbers;

    return wrongNumbers;
}
