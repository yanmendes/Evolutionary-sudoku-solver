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
    int fitness;
    static Helper h;
public:
    //Constructors
    Individual();
    Individual(Individual*);
    
    //Auxiliary methods
    Individual * fillWithRandom(void);
    
    //Getters
    int getFitness(void);
    
    //Destructor
    ~Individual(void) {};
};

#endif /* Individual_hpp */
