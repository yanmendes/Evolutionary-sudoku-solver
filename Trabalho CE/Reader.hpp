//
//  Reader.hpp
//  Trabalho IA
//
//  Created by Yan Mendes on 27/04/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#ifndef Reader_hpp
#define Reader_hpp

#include "Helper.hpp"
#include "Individual.hpp"

using namespace std;

class Reader{
public:
    vector<Individual*> parseSudokus(string);
};

#endif /* Reader_hpp */
