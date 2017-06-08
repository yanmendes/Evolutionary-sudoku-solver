//
//  Parameters.hpp
//  Trabalho CE
//
//  Created by Yan Mendes on 02/06/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#ifndef Parameters_hpp
#define Parameters_hpp

#include <stdio.h>
#include <string>

using namespace std;

class Parameters{
public:
    static int GENERATIONS, POPULATION_SIZE;
    static double MUTATION_FREQUENCY, PRESERVED_POPULATION_PERCENTAGE;
    static string OUTPUT_FOLDER;
};

#endif /* Parameters_hpp */
