//
//  Sort.cpp
//  
//
//  Created by Emma on 12/11/2016.
//
//

#include "Sort.hpp"

//CreatNumber
unsigned long long CreatNumber::calNum(unsigned long long xn) {
    return (3*xn+5) % (unsigned long long)1125899906842679;
    //return (3*xn+5) % 100;
}

void CreatNumber::saveNumToFile(unsigned long long x1) {
    ofstream out;
    //ofstream out2;
    
    out.open("/Users/emma/Work/Sort/ExternSort/ExternSort/numbers",ios::out|ios::binary|ios::trunc);
    //out2.open("/Users/emma/Work/Sort/ExternSort/ExternSort/numbers_show",ios::out|ios::binary|ios::trunc);
    if (out.fail()) cout<<"error!"<<endl;
    for (unsigned long long i=0; i<NUM_SIZE; ++i) {
        out.write((char*)&x1, sizeof(unsigned long long));
        //out2<<x1<<endl;//TODO delete
        
        x1 = calNum(x1);
    }
    //cout<<endl;//TODO delete
    out.close();
    //out2.close();
}

//ExternSort
void ExternSort::readData(ifstream &in,unsigned long long &arrNum,unsigned long long size) {
    in.read(reinterpret_cast<char*>(&arrNum),sizeof(unsigned long long)*size);
}

void ExternSort::memorySort() {
    in.open("/Users/emma/Work/Sort/ExternSort/ExternSort/numbers",ios::in|ios::binary);
    arrNum = new unsigned long long[READ_SIZE];
    
    unsigned long long  index;
    for (index=0; index<NUM_SIZE/READ_SIZE+1; ++index){
        if (NUM_SIZE%READ_SIZE==0 && index == NUM_SIZE/READ_SIZE) break;
        unsigned long long size = READ_SIZE;
        if (index == NUM_SIZE/READ_SIZE)
            size = NUM_SIZE-index*READ_SIZE;
        
        readData(in,*arrNum,size);
        
        qsort(arrNum, size , sizeof(unsigned long long), cmp_int);
        string fn = geneFileName(index);
        saveNumToFile(fn,size);
        cout<<"small file "<<index<< " save"<<endl;
    }
    delete[] arrNum;
    in.close();
    countFile = index;
    return;
}

string ExternSort::geneFileName(unsigned long long index) {
    std::stringstream sstm;
    sstm <<"/Users/emma/Work/Sort/ExternSort/ExternSort/temp/temp" << index;
    return sstm.str();
}

void ExternSort::saveNumToFile(string fileName,unsigned long long size) {
    ofstream out;
    out.open(fileName,ios::out|ios::binary|ios::trunc);
    if (out.fail()) cout<<"error!"<<endl;
    out.write(reinterpret_cast<char*>(arrNum), sizeof(unsigned long long)*size);
    out.close();
}

unsigned long long ExternSort::readBuffers(const unsigned long long fileLength,ifstream& tempFile,unsigned long long& readBuffer){
    //if (tempFile.eof()) return -1;
    unsigned long long len = fileLength-(unsigned long long)tempFile.tellg()/sizeof(unsigned long long);
    if (len==0)
        return 0;
    if (MERGE_SIZE<len){
        readData(tempFile,readBuffer,MERGE_SIZE);
        return MERGE_SIZE;
    } else {
        readData(tempFile,readBuffer,len);
        return len;
    }
}

void ExternSort::showAll(unsigned long long fileLength,ifstream& tempFile){
    //if (tempFile.eof()) return -1;
    arrNum = new unsigned long long[fileLength];
    readData(tempFile,*arrNum,fileLength);
    cout<<fileLength<<" ";
    for (unsigned long long i=0; i<fileLength; ++i)
        cout<<arrNum[i]<<" ";
    delete [] arrNum;
    cout<<endl;
    
}

void ExternSort::mergeSort() {
    if(countFile<=0) return;
    
    unsigned long long* outBuffer = new unsigned long long[MERGE_OUT_SIZE];
    unsigned long long** readBuffer = new unsigned long long*[countFile];
    unsigned long long outKey = -1;
    unsigned long long* readKey = new unsigned long long[countFile];
    for(unsigned long long i=0; i<countFile; ++i) readKey[i]=0;
    
    ifstream* tempFiles = new ifstream[countFile];
    unsigned long long* fileLength = new unsigned long long[countFile];
    unsigned long long* hasNext = new unsigned long long[countFile];
    for (unsigned long long i=0; i<countFile; ++i) {
        readBuffer[i]=new unsigned long long[MERGE_SIZE];
        tempFiles[i].open(geneFileName(i),ios::in|ios::binary|ios::ate);
        fileLength[i] = (unsigned long long)tempFiles[i].tellg()/sizeof(unsigned long long);
        
        //tempFiles[i].seekg(0);//TODO delete
        //showAll(fileLength[i], tempFiles[i]);
       
        tempFiles[i].seekg(0);
        hasNext[i] = readBuffers(fileLength[i],tempFiles[i],*readBuffer[i]);
        
        //cout<<i<<","<<hasNext[i]<<","<<fileLength[i]<<","<<readBuffer[i][0]<<","<<readBuffer[i][1]<<endl;//TODO delete
    }
    
    ofstream out;
    out.open("/Users/emma/Work/Sort/ExternSort/ExternSort/result",ios::out|ios::binary|ios::trunc);
    //ofstream out2;
    //out2.open("/Users/emma/Work/Sort/ExternSort/ExternSort/result_show",ios::out|ios::binary|ios::trunc);
    unsigned long long minkey = 0;
    bool checkout = false;
    while(true) {
        unsigned long long min = readBuffer[minkey][readKey[minkey]];
        for (unsigned long long i=0; i<countFile; ++i) {
            if(hasNext[i]>readKey[i] && readBuffer[i][readKey[i]]<min) {
                min = readBuffer[i][readKey[i]];
                minkey = i;
            }
        }
        outBuffer[++outKey] = min;
        ++readKey[minkey];
        if (readKey[minkey] >= hasNext[minkey]) {
            hasNext[minkey] = readBuffers(fileLength[minkey],tempFiles[minkey],*readBuffer[minkey]);
            readKey[minkey] = 0;
            //cout<<minkey<<","<<hasNext[minkey]<<","<<fileLength[minkey]<<","<<readBuffer[minkey][readKey[minkey]]<<endl;//TODO delete
            if(hasNext[minkey]==0) {
                minkey = 0;
                while (hasNext[minkey]==0) {
                    ++minkey;
                    if (minkey >= countFile){
                        checkout = true;
                        break;
                    }
                }
            }
        }
        if (outKey >= MERGE_OUT_SIZE) {
            out.write(reinterpret_cast<char*>(outBuffer), sizeof(unsigned long long)*(outKey+1));
            //cout<<"start";
            //for (unsigned long long i=0; i<=outKey; ++i) {
            //    out2<<outBuffer[i]<<endl;
                //cout<<outBuffer[i]<<endl;
            //}
            outKey = -1;
        }
        if (checkout== true) {
            out.write(reinterpret_cast<char*>(outBuffer), sizeof(unsigned long long)*(outKey+1));
            //for (unsigned long long i=0; i<=outKey; ++i) {
            //    out2<<outBuffer[i]<<endl;
            //    //cout<<outBuffer[i]<<endl;
            //}
            break;
        }
    }
    for (unsigned long long i=0; i<countFile; ++i) {
        tempFiles[i].close();
        delete[] readBuffer[i];
    }
    delete[] readBuffer;
    delete[] outBuffer;
    delete[] readKey;
    delete[] tempFiles;
    delete[] fileLength;
    delete[] hasNext;
    out.close();
    //out2.close();
}

void ExternSort::sort() {
    memorySort();
    cout<<"memory sort done!"<<endl;
    mergeSort();
}

unsigned long long Result::hash(unsigned long long hn_1,unsigned long long yn){
    return (hn_1*3+yn)%(unsigned long long)1125899906842679;
}

void Result::cal() {
    ifstream tempFiles;
    //tempFiles.open("/Users/emma/Work/Sort/ExternSort/ExternSort/result",ios::in|ios::binary|ios::ate);
    tempFiles.open("/Users/emma/Work/Sort/ExternSort/ExternSort/result",ios::in|ios::binary);
    //unsigned long long fileLength = (unsigned long long)tempFiles.tellg()/sizeof(unsigned long long);
    //cout<<(unsigned long long)tempFiles.tellg()<<endl;
    //cout<<sizeof(unsigned long long)<<endl;
    //cout<<fileLength;
    //return;
    tempFiles.seekg(0);
    //ofstream out;
    //out.open("/Users/emma/Work/Sort/ExternSort/ExternSort/result_hash",ios::out|ios::trunc);
    
    unsigned long long h1;
    tempFiles.read((char*)&h1,sizeof(unsigned long long));
    unsigned long long yn;
    for (unsigned long long i=1; i<NUM_SIZE; ++i) {
        tempFiles.read((char*)&yn,sizeof(unsigned long long));
        //out<<h1<<endl;
        h1=hash(h1, yn);
    }
    //out<<h1;
    cout<<h1<<endl;
    //out.close();
}

int main(){
    CreatNumber cn;
    cn.saveNumToFile(2016213633);
    cout<<"step1!"<<endl;
    ExternSort es;
    es.sort();
    cout<<"step2!"<<endl;
    Result res;
    res.cal();
    cout<<"step3!"<<endl;
    return 1;
}
