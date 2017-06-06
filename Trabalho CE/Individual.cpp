//
//  Individual.cpp
//  Trabalho CE
//
//  Created by Yan Mendes on 24/05/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#include "Individual.hpp"

Individual::Individual(){}

Individual::Individual(Individual * templateIndividual){
    this->fitness = -1;
}

Individual * Individual::fillWithRandom(){
    return this;
}

int Individual::getFitness(){
    if(this->fitness != -1)
        return this->fitness;
    
    return 0;
}
