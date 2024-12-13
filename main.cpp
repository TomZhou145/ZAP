#include <iostream>
#include <istream> 
#include <fstream>
#include <string>

#include "HuffmanTreeNode.h"
#include "HuffmanCoder.h"
#include "ZapUtil.h" 

using namespace std;

//main
//main function
int main(int argc, char *argv[])
{
    string zap = argv[1]; 
    string out; 
    HuffmanCoder  hc1;
    if (argc != 4)
    {
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile\n"; 
        exit(EXIT_FAILURE); 
    }
    else {
    if (zap == "zap")
    {
        hc1.encoder(argv[2],argv[3]); 
    }
    else if (zap == "unzap")
    {
        //decode
        hc1.decoder(argv[2],argv[3]); 
        return 0; 
    }
    else 
    {
        //make error message
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile\n"; 
        return 0;
    }
    }
    
    return 0; 
}


