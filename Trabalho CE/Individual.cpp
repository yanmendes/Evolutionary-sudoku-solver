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
Individual::fitnessMethod       Individual::currentFitnessMethod;
Individual::getMethodName       Individual::currentFitnessMethodName;

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
        
        square.push_back(this->sudokuBoard.at(j + offset));
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

long long int Individual::getFitness(){
    if(this->fitness == -1)
        this->fitness = (this->*currentFitnessMethod)();
    
    return this->fitness;
}

Individual * Individual::setFitness(long long int fitness){
    this->fitness = fitness;
    
    return this;
}

string Individual::getCurrentFitnessMethodName(){
    return Individual::currentFitnessMethodName();
}

long long int Individual::numberOfWrongNumbers(){
    int wrongNumbers = this->limit * this->limit;
    
    for(int i = 0; i < this->limit; ++i){
        //Checks for duplicates in each row
        wrongNumbers -= h.getNumberOfDuplicates(this->getRow(i), this->limit);
        
        //Checks for duplicates in each column
        wrongNumbers -= h.getNumberOfDuplicates(this->getColumn(i), this->limit);
        
        //Checks for duplicates in each square
        wrongNumbers -= h.getNumberOfDuplicates(this->getSquare(i), this->limit);
    }
    
    return wrongNumbers;
}

int Individual::maxFitnessWrongNumbers(){
    return Helper::LIMIT * Helper::LIMIT;
}

long long int Individual::mantereKoljonenOptimizationFunction(){
    long long int gi1, gj1, gk1, gi2, gj2, gk2, gi3, gj3, gk3;
    
    gi1 = gj1 = gk1 = gi2 = gj2 = gk2 = gi3 = gj3 = gk3 = 0;
    
    for(int i = 0; i < this->limit; ++i){
        vector<int> row = this->getRow(i);
        vector<int> column = this->getColumn(i);
        vector<int> square = this->getSquare(i);
        
        gi1 += abs(Helper::LIMIT_SUM - std::accumulate(row.begin(), row.end(), 0));
        gj1 += abs(Helper::LIMIT_SUM - std::accumulate(column.begin(), column.end(), 0));
        gk1 += abs(Helper::LIMIT_SUM - std::accumulate(square.begin(), square.end(), 0));
        
        gi2 += sqrt(abs(Helper::LIMIT_FACTORIAL - h.multiply(row)));
        gj2 += sqrt(abs(Helper::LIMIT_FACTORIAL - h.multiply(column)));
        gk2 += sqrt(abs(Helper::LIMIT_FACTORIAL - h.multiply(square)));
        
        gi3 += h.getNumberOfDuplicates(row, this->limit);
        gj3 += h.getNumberOfDuplicates(column, this->limit);
        gk3 += h.getNumberOfDuplicates(square, this->limit);
    }
    
    return (long long int) - (10 * (gi1 + gj1 + gk1) + (gi2 + gj2 + gk2) + 50 * (gi3 + gj3 + gk3));
}

int Individual::maxFitnessKoljonenOptimizationFunction(){
    return 0;
}
