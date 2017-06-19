//
//  Helper.hpp
//  Trabalho IA
//
//  Created by Yan Mendes on 27/04/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#ifndef Helper_hpp
#define Helper_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <list>
#include <stdlib.h>
#include <cstdlib>
#include <dirent.h>
#include <cwchar>
#include <time.h>
#include <cstring>
#include <sstream>
#include <ctime>
#include <vector>
#include <utility>
#include <queue>
#include <stack>
#include <map>
#include <climits>
#include <locale>
#include <random>
#include "Parameters.hpp"

#define SEED time(0);

using namespace std;

class Helper{
public:
    static string executionId;
    int getMax(int *, int);
    list<string> getFilesInDirectory(string);
    vector<string> explode(string const &, char);
    static string getCurrentTimeStamp();
    static string getNormalizedCurrentTimeStamp();
    static int find(vector<int>, int, int);
    static vector<int> generateRandomSequence(int);
    static int* toArray(vector<int>);
    static vector<int> toVector(int*, int);
    static string getMatrix(vector<int>, int);
    static void printMatrix(vector<int>, int);
    static long long int generateRandomNumber(long long int, long long int);
    static unsigned long long int createMatrixHash(vector<int> matrix, int limit);
    static string createOutputFileName(string, string, string, vector<int>, int);
    static int getNumberOfDuplicates(vector<int>, int);
    static vector<int> slice(vector<int>, int, int, int);
    static vector<int> slice(vector<int>, int, int);
    static void generateExecutionId(void);
    static int apSum(int);
    static long long int factorial(int);
    static long long int multiply(vector<int>);
    
    static long long int LIMIT_FACTORIAL, LIMIT_SUM;
    static int LIMIT;
};

#endif /* Helper_hpp */
