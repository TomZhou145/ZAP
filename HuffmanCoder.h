#ifndef _HUFFMAN_CODER
#define _HUFFMAN_CODER

#include <string>
#include <istream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector> 
#include <queue>
#include <unordered_map>
#include "HuffmanTreeNode.h"
#include <utility>
using namespace std;

class HuffmanCoder {
    // Feel free to add additional private helper functions as well as a
    // constructor and destructor if necessary
   public:
   //constructor
   HuffmanCoder(); 

   
    void encoder(const std::string &inputFile, const std::string &outputFile);
    void decoder(const std::string &inputFile, const std::string &outputFile);

   private:
   //encoder helper:
    vector<char> count_freqs(std::istream &text, vector<int> c_list, 
    priority_queue<HuffmanTreeNode *, std::vector<HuffmanTreeNode *>,
    NodeComparator> *my_pq); 
    
    HuffmanTreeNode* build_tree(priority_queue<HuffmanTreeNode *, 
    std::vector<HuffmanTreeNode *>, NodeComparator> my_pq); 
    
    string generate_code(HuffmanTreeNode *root, const std::string &inputFile); 


    void node_traverse(HuffmanTreeNode *root, 
    vector<string> &list, vector<char> &Indexlist,
    string code);

    string BinaryString(const std::string &inputFile, 
    vector<string> &list, vector<char> &Indexlist); 

    
    //decoder helper: 

    string decode_message(string codedMSG,HuffmanTreeNode *root); 


    void deleteTree(HuffmanTreeNode* root); 
};

#endif