//
//  Reader.cpp
//  Trabalho IA
//
//  Created by Yan Mendes on 27/04/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#include "Reader.hpp"

vector<Individual*> Reader::parseInput(string file){
    vector<Individual*> individuals;
    
    fstream inputFile;
    inputFile.open(file);
    
    string line;

    inputFile.close();
    
    cout << "- - - - - - Done parsing input file " << file << " - - - - - - " << endl;
    
    return individuals;
}
