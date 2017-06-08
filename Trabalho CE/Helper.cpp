 //
//  Helper.cpp
//  Trabalho IA
//
//  Created by Yan Mendes on 27/04/17.
//  Copyright © 2017 Yan Mendes. All rights reserved.
//

#include "Helper.hpp"

string Helper::executionId;

long int seed = SEED;
mt19937 mt_rand((unsigned int) seed);

using namespace std;

/**
 * Method that returns the greatest absolute value in the array
 *
 * @param A (int*) Shuffled array
 * @param n (int)  Number of elements of said array
 *
 * @return   int
 */
int Helper::getMax(int * A, int n)
{
    int max = abs(A[0]);

    for (int i = 1; i < n; i++){
        if(abs(A[i]) > max)
            max = abs(A[i]);
    }

    return max;
}

list<string> Helper::getFilesInDirectory(string directory)
{
    list<string> files;

    DIR * dir;
    struct dirent * entry;

    if((dir = opendir(directory.c_str()))){
        while((entry = readdir(dir))){
            if (strstr( entry->d_name, ".in" ))
                files.push_front(directory + "/" + entry->d_name);
        }
        closedir(dir);
    }

    return files;
}

vector<string> Helper::explode(std::string const & s, char delim) {
    std::vector<std::string> result;
    std::istringstream iss(s);
    
    for (std::string token; std::getline(iss, token, delim); )
        result.push_back(std::move(token));
    
    return result;
}

string Helper::getCurrentTimeStamp(){
    stringstream ss;
    
    time_t t = time(0);
    struct tm * now = localtime(&t);
    ss << now->tm_mday << '/' << now->tm_mon + 1 << '/' <<  now->tm_year + 1900 << ' '
    << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec;
    
    return ss.str();
}

string Helper::getNormalizedCurrentTimeStamp(){
    string ts = Helper::getCurrentTimeStamp();
    
    replace(ts.begin(), ts.end(), '/', '_');
    replace(ts.begin(), ts.end(), ':', '_');
    replace(ts.begin(), ts.end(), ' ', '_');
    
    return ts;
}

int Helper::find(vector<int> A, int n, int val){
    int i;
    
    for(i = 0; i < n; ++i)
        if(A.at(i) == val)
            break;
    
    return i;
}

vector<int> Helper::generateRandomSequence(int limit){
    vector<int> data;
    
    for(int i = 1; i <= limit; ++i)
        data.push_back(i);
    
    std::random_shuffle(data.begin(), data.end());
    
    return data;
}

int* Helper::toArray(vector<int> vec){
    int * r = new int[(int) vec.size()];
    int i = 0;
    
    for(int val : vec)
        r[i++] = val;
    
    return r;
}

vector<int> Helper::toVector(int * array, int size){
    vector<int> r (array, array + size);
    
    return r;
}

string Helper::getMatrix(vector<int> vec, int limit){
    stringstream result;
    
    for(int i = 0; i < limit; ++i){
        for(int j = 0; j < limit; ++j)
            result << vec.at(i * limit + j) << '\t';
        result << '\n';
    }
    
    return result.str();
}

void Helper::printMatrix(vector<int> vec, int limit){
    cout << Helper::getMatrix(vec, limit);
}

unsigned int Helper::generateRandomNumber(int inferiorRange, int superiorRange){
    return mt_rand() % superiorRange + inferiorRange;
}

string Helper::createOutputFileName(string crossoverMethod, string mutationMethod, vector<int> matrix, int limit){
    string output;
    unsigned long long int sum = 0;
    for(int i = 0; i < limit * limit; ++i)
        sum += (matrix.at(i) * i);
    
    string instanceIdentifier = crossoverMethod + "_" + mutationMethod + "_" + to_string(sum) + ".out";
    
    replace(instanceIdentifier.begin(), instanceIdentifier.end(), ' ', '_');
    
    output = Helper::executionId + instanceIdentifier;
    
    return output;
}

int Helper::getNumberOfDuplicates(vector<int> vec, int limit){
    int c = 0;
    
    for(int i = 0; i < limit - 1; ++i)
        for(int j = i + 1; j < limit; ++j)
            c += vec.at(i) == vec.at(j);
    
    return c;
}

vector<int> Helper::slice(vector<int> vec, int inferiorRange, int superiorRange, int jump){
    vector<int> r;
    
    for(int i = inferiorRange; i <= superiorRange; i += jump)
        r.push_back(vec.at(i));
    
    return r;
}

vector<int> Helper::slice(vector<int> vec, int inferiorRange, int superiorRange){
    return Helper::slice(vec, inferiorRange, superiorRange, 1);
}

void Helper::generateExecutionId(){
    Helper::executionId =
    Parameters::OUTPUT_FOLDER +
    to_string(Parameters::GENERATIONS) + "_" +
    to_string(Parameters::POPULATION_SIZE) + "_" +
    (to_string(Parameters::MUTATION_FREQUENCY)).substr(0, 5) + "_" +
    (to_string(Parameters::PRESERVED_POPULATION_PERCENTAGE)).substr(0, 5) + "_" +
    Helper::getNormalizedCurrentTimeStamp() + "_";
    
    Helper::executionId.erase(remove(Helper::executionId.begin(), Helper::executionId.end(), '.'), Helper::executionId.end());
}
