//
//  Reader.cpp
//  Trabalho IA
//
//  Created by Yan Mendes on 27/04/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#include "Reader.hpp"

vector<Individual*> Reader::parseSudokus(string file){
    vector<Individual*> boards;
    
    fstream inputFile;
    inputFile.open(file);
    
    string line;
    int instances, limit;
    
    inputFile >> instances >> limit;
    
    Helper::LIMIT = limit;
    Helper::LIMIT_FACTORIAL = Helper::factorial(limit);
    Helper::LIMIT_SUM = Helper::apSum(limit);
    
    for(int k = 0; k < instances; ++k){
        vector<int> sudokuBoard (limit * limit);
        for(int i = 0; i < limit; ++i)
            for(int j = 0; j < limit; ++j)
                inputFile >> sudokuBoard.at(i * limit + j);
        
        boards.push_back(new Individual(limit, sudokuBoard));
    }
    
    inputFile.close();
    
    cout << "- - - - - - Done parsing input file " << file << " - - - - - - " << endl;
    
    return boards;
}
