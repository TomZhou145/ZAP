#include <sstream>
#include <string>
#include <cassert>
#include <iostream>
#include <fstream>
#include "phaseOne.h"
#include "HuffmanTreeNode.h"
#include "ZapUtil.h"
#include "HuffmanCoder.h"
using namespace std;

//regular sentence diff 
void test_Reg_Encode() {
    HuffmanCoder coder;   
    coder.encoder("sentene.txt", "sentenceOut.zap");
    coder.decoder("sentenceOut.zap", "sentenceOut.txt"); 
    ifstream decodedFile("sentenceOut.txt");
    ifstream decoded2File("sentene.txt");
    string decode;
    string in; 
    getline(decodedFile, decode);
    getline(decoded2File, in);
    cout << "Decode: " << decode << endl; 
    cout << "In: " << in << endl; 
    assert(decode == in); 
}

//single char diff test
void test_sing_Encode() {
    HuffmanCoder coder;   
    coder.encoder("singleChar.txt", "singleChar.zap");
    coder.decoder("singleChar.zap", "singleCharOut.txt"); 
    ifstream decodedFile("singleCharOut.txt");
    ifstream decoded2File("singleChar.txt");
    string decode;
    string in; 
    getline(decodedFile, decode);
    getline(decoded2File, in);
    cout << "Decode: " << decode << endl; 
    cout << "In: " << in << endl; 
    assert(decode == in); 
}

//empty file diff test
void test_none_Encode() {
    HuffmanCoder coder;   
    coder.encoder("empty.txt", "empty.zap");
    coder.decoder("empty.zap", "emptyOut.txt"); 
    ifstream decodedFile("empty.txt");
    ifstream decoded2File("emptyOut.txt");
    string decode;
    string in; 
    getline(decodedFile, decode);
    getline(decoded2File, in);
    cout << "Decode: " << decode << endl; 
    cout << "In: " << in << endl; 
    assert(decode == in); 
}