//
//  Writer.hpp
//  Trabalho IA
//
//  Created by Yan Mendes on 08/05/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#ifndef Writer_hpp
#define Writer_hpp

#include <stdio.h>

#include "GeneticAlgorithm.hpp"
#include "Result.hpp"

class Writer{
private:
    string outputFile;
    GeneticAlgorithm * g;
    Helper h;
public:
    Writer(Individual*, GeneticAlgorithm*);
    void writeResults(double);
    static void writeStatistcs(string);
};

#endif /* Writer_hpp */
