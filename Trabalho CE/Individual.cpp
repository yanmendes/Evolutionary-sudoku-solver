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

Individual::Individual(int limit, vector<int> matrix){
    this->limit = limit;
    
    for(int i = 0; i < this->limit * this->limit; ++i){
        this->sudokuBoard.push_back(matrix.at(i));
        if(matrix.at(i))
            this->fixedPositions.push_back(i);
    }
}

Individual::Individual(Individual * templateIndividual){
    this->limit = templateIndividual->limit;
    this->fitness = -1;
    
    for(int number : templateIndividual->fixedPositions)
        this->fixedPositions.push_back(number);
    
    for(int number : templateIndividual->sudokuBoard)
        this->sudokuBoard.push_back(number);
}

Individual * Individual::fillWithRandom(){
    for(int i = 0; i < this->limit; ++i)
        (this->*currentSetter)(i, h.generateRandomSequence(this->limit));
    
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
    return h.slice(sudokuBoard, rowNumber * limit, rowNumber * limit + limit - 1);
}

vector<int> Individual::getColumn(int colNumber){
    return h.slice(sudokuBoard, colNumber, limit * limit - (limit - colNumber), limit);
}

Individual * Individual::setSquare(int squareNumber, vector<int> values){
    int sqrtLimit = sqrt(this->limit);
    int offset = (squareNumber/sqrtLimit) * this->limit * sqrtLimit + (squareNumber % sqrtLimit) * sqrtLimit;
    
    //Corrects the square with the fixed values from the board
    for(int j = 0; j < this->limit; ++j){
        if(j && !(j % sqrtLimit))
            offset += this->limit - sqrtLimit;
        
        int matrixPosition = j + offset;
    
        if(binary_search(this->fixedPositions.begin(), this->fixedPositions.end(), matrixPosition)
                              && this->sudokuBoard.at(matrixPosition) != values.at(j))
            swap(values.at(j), values.at(h.find(values, limit, this->sudokuBoard.at(matrixPosition))));
    }
    
    offset = (squareNumber/sqrtLimit) * this->limit * sqrtLimit + (squareNumber % sqrtLimit) * sqrtLimit;
    for(int j = 0; j < this->limit; ++j){
        if(j && !(j % sqrtLimit))
            offset += this->limit - sqrtLimit;
        
        this->sudokuBoard.at(j + offset) = values.at(j);
    }
    
    return this;
}

Individual * Individual::setRow(int rowNumber, vector<int> values){
    //Corrects the row with the fixed values from the board
    for(int j = 0; j < this->limit; ++j){
        int matrixPosition = rowNumber * this->limit + j;
        
        if(binary_search(this->fixedPositions.begin(), this->fixedPositions.end(), matrixPosition)
           && this->sudokuBoard.at(matrixPosition) != values.at(j))
            swap(values.at(j), values.at(h.find(values, limit, this->sudokuBoard.at(matrixPosition))));
    }
    
    for(int j = 0; j < this->limit; ++j)
        this->sudokuBoard.at(rowNumber * this->limit + j) = values.at(j);
    
    return this;
}

Individual * Individual::setColumn(int colNumber, vector<int> values){
    //Corrects the column with the fixed values from the board
    for(int j = 0; j < this->limit; ++j){
        int matrixPosition = j * this->limit + colNumber;
        
        if(binary_search(this->fixedPositions.begin(), this->fixedPositions.end(), matrixPosition)
           && this->sudokuBoard.at(matrixPosition) != values.at(j))
            swap(values.at(j), values.at(h.find(values, limit, this->sudokuBoard.at(matrixPosition))));
    }
    
    for(int j = 0; j < this->limit; ++j)
        this->sudokuBoard.at(j * this->limit + colNumber) = values.at(j);

    return this;
}

int Individual::getFitness(){
    if(this->fitness != -1)
        return this->fitness;
    
    int wrongNumbers = this->limit * this->limit;
    
    for(int i = 0; i < this->limit; ++i){
        //Checks for duplicates in each row
        wrongNumbers -= h.getNumberOfDuplicates(this->getRow(i), this->limit);
        
        //Checks for duplicates in each column
        wrongNumbers -= h.getNumberOfDuplicates(this->getColumn(i), this->limit);
        
        //Checks for duplicates in each square
        wrongNumbers -= h.getNumberOfDuplicates(this->getSquare(i), this->limit);
    }
    
    this->fitness = wrongNumbers;

    return wrongNumbers;
}
