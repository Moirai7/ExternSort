//
//  Sort.hpp
//  
//
//  Created by Emma on 12/11/2016.
//
//

#ifndef Sort_hpp
#define Sort_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

//#define NUM_SIZE 50
using namespace std;

//const unsigned long long NUM_SIZE = (unsigned long long)1 << 32;
const unsigned long long NUM_SIZE = 12;
const unsigned long long READ_SIZE = 3;
const unsigned long long MERGE_SIZE = 2;
const unsigned long long MERGE_OUT_SIZE = 10;

class CreatNumber {
private:
    unsigned long long calNum(unsigned long long xn);

public:
    void saveNumToFile(unsigned long long x1);
};

class ExternSort {
private:
    unsigned long long* arrNum;
    ifstream in;
    unsigned int countFile;
    
    void readData(ifstream &in,unsigned long long &arrNum,unsigned int size);
    void memorySort();
    string geneFileName(unsigned int index);
    void saveNumToFile(string fileName,unsigned int size);
    void mergeSort();
    int readBuffers(const int fileLength,ifstream& tempFile,unsigned long long& readBuffer);
    void showAll(int fileLength,ifstream& tempFile);
    static int cmp_int(const void *a, const void *b){
        if(*(unsigned long long*)a > *(unsigned long long*)b) return 1;
        if(*(unsigned long long*)a < *(unsigned long long*)b) return -1;
        return 0;
    }
    
public:
    void sort();
    
};

class Result {
private:
    unsigned long long hash(unsigned long long hn_1,unsigned long long yn);
public:
    void cal();
};

#endif /* Sort_hpp */
