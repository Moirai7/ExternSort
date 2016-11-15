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

const unsigned long long NUM_SIZE = (unsigned long long)1 << 31;
const unsigned long long READ_SIZE = (unsigned long long)1 << 28;
const unsigned long long MERGE_SIZE = (unsigned long long)1 << 27;
const unsigned long long MERGE_OUT_SIZE = (unsigned long long)1 << 27;
//const unsigned long long NUM_SIZE = 113;
//const unsigned long long READ_SIZE = 3;
//const unsigned long long MERGE_SIZE = 2;
//const unsigned long long MERGE_OUT_SIZE = 10;

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
    unsigned long long countFile;
    
    void readData(ifstream &in,unsigned long long &arrNum,unsigned long long size);
    void memorySort();
    string geneFileName(unsigned long long index);
    void saveNumToFile(string fileName,unsigned long long size);
    void mergeSort();
    unsigned long long readBuffers(const unsigned long long fileLength,ifstream& tempFile,unsigned long long& readBuffer);
    void showAll(unsigned long long fileLength,ifstream& tempFile);
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
