//Tom Zhou
//10/20/24
//HuffmanCoder.cpp
#include <string>
#include <istream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector> 
#include <queue>
#include <unordered_map>
#include "HuffmanTreeNode.h"
#include "HuffmanCoder.h"
#include "ZapUtil.h" 
#include "phaseOne.h"
#include <utility>
using namespace std; 
HuffmanCoder::HuffmanCoder(){}; 

//*encoder
//function: main functions that encodes a message into a zap file
//input: address of name of input file
//output: addres of name of output file
void HuffmanCoder::encoder(const std::string &inputFile, 
const std::string &outputFile)
{
    vector<int>c_list(256,0); 
    priority_queue<HuffmanTreeNode *, std::vector<HuffmanTreeNode *>,
    NodeComparator> my_pq; 
    ifstream infile(inputFile);
    if (infile.fail())
    {
        string filename = inputFile; 
        throw runtime_error ("Unable to open file " + filename); 
        exit(EXIT_FAILURE); 
    }
    string file = ""; 
    string full_file; 
    vector <char> bin_char_list = count_freqs(infile, c_list, &my_pq); 
    HuffmanTreeNode* root = build_tree(my_pq);
    
    infile.close(); 
    string binaryMessage = generate_code(root,inputFile); 
    string serializedTree = serialize_tree(root); 
    writeZapFile(outputFile,serializedTree,binaryMessage); 
    deleteTree(root); 
    int N = binaryMessage.size(); 
    cout << "Success! Encoded given text using " <<  N  << " bits.\n"; 
    return; 
};

//count_freqs
//function: counts frequency of all characters and update it in my_pq
//input: istream of the text, the vector characterlist, priority_queue for. 
//output: a char vector that is not in use. 
vector<char> HuffmanCoder::count_freqs(std::istream &text, vector<int> c_list, 
priority_queue<HuffmanTreeNode *, std::vector<HuffmanTreeNode *>,
    NodeComparator> *my_pq)
{
    vector<char>list; 
    char c; 
    while(text.get(c)) {
        c_list[c]++;        
    } 
    for (char i = 0; i < c_list.size(); i ++)
    {
        if (c_list[i] != 0)
        {
        HuffmanTreeNode *node = new HuffmanTreeNode(i,c_list[i]); 
        my_pq->push(node); 
        list.push_back(node->get_val()); 
        }
    }
    return list; 
}

//build_tree
//function: builds a huffman tree 
//input: priority queue my_pq
//output: the root node of the tree
HuffmanTreeNode* HuffmanCoder::build_tree(priority_queue<HuffmanTreeNode *, 
std::vector<HuffmanTreeNode *>, NodeComparator> my_pq)
{
    if (my_pq.empty()) 
    {
        return nullptr; 
    }
    
    while (my_pq.size() > 1)
    {
        HuffmanTreeNode *left = my_pq.top(); 
        my_pq.pop();
        HuffmanTreeNode *right = my_pq.top();
        my_pq.pop();
        int num = left->get_freq() + right->get_freq(); 

        HuffmanTreeNode *root = new HuffmanTreeNode('\0',num, left,right); 
        my_pq.push(root); 
    }
    return my_pq.top(); 
} 

//generate_code
//function: hosts functions that generates the binary code for the message
//input: root node of the huffman tree, and name of the input file
//output: binary string of the message
string HuffmanCoder::generate_code(HuffmanTreeNode *root,
const std::string &inputFile )
{
    string char_code = ""; 
    string direction; 
    vector<char>CharIndex;  
    vector<string>CharBinary(CharIndex.size(), ""); 
    node_traverse(root,CharBinary,CharIndex,char_code); 
    return BinaryString(inputFile, CharBinary,CharIndex); ; 
    
}

//Node_traverse
//function: traverse the tree and update two vectors: one for letter index,
// the other to store its perspective code
//input: root node of the tree, binary code vector, character index vector,
// the string code
//output: none
void HuffmanCoder:: node_traverse(HuffmanTreeNode *root, 
vector<string> &list, vector<char> &Indexlist,string code)
{
    if (root == nullptr)
    {   
        return;
    }
    if (root->is_leaf())
    {
        if (code.size() == 0)
        {
            list.push_back("0"); 
            Indexlist.push_back(root->get_val()); 
        }
        else
        {
        list.push_back(code); 
        Indexlist.push_back(root->get_val()); 
        }
    }
    else 
    { 
        node_traverse(root->get_left(),list,Indexlist,code + "0"); 
        node_traverse(root->get_right(),list,Indexlist,code + "1"); 
    }
    return; 
}

//BinaryString
//function: turns a string into a binary code
//input: address of name of input file, binary code vector, index vector
//output: binary code of the string
string HuffmanCoder:: BinaryString(const std::string &inputFile, 
vector<string> &list, vector<char> &Indexlist)
{ 
    ifstream infile(inputFile);
    if (infile.fail())
    {
        cerr << "fail\n";
        exit(EXIT_FAILURE); 
    }
    string BinaryMessage = ""; 
    char c; 
    while (infile.get(c))
    {
        for (int i = 0; i < Indexlist.size(); i++) 
        {
            if (c == Indexlist[i])
            {
                BinaryMessage += list[i]; 
            }
        }
    }
    infile.close(); 
    return BinaryMessage; 
}



//decoder
//function: masterfunction that decodes and decompress zap file
//inout: input/output string file
//output: nothing
void HuffmanCoder::decoder(const std::string &inputFile, 
const std::string &outputFile)
{
    pair<string,string> decode = readZapFile(inputFile); 
    string tree = decode.first; 
    string code = decode.second; 
    HuffmanTreeNode *root = deserialize_tree(tree); 
    string decodedMsg = ""; 
    string MSG = decode_message(code,root); 
    ofstream ofile(outputFile);
    if (ofile.fail())
    {
        exit(EXIT_FAILURE);
    }
    ofile << MSG; 
    ofile.close(); 
    deleteTree(root); 
    return;
}

//decode_message
//function: traverse through the tree with the code to decode the message 
//input: binary string, HuffmanTree
//output: uncoded string
string HuffmanCoder::decode_message(string codedMSG, HuffmanTreeNode *root)
{
    HuffmanTreeNode *OG_root = root;
    string DecodedString = "";
    for (int i = 0; i < codedMSG.size(); i++) 
    {
        
        if (codedMSG[i] == '1')
        {
            root = root->get_right(); 
            
        }
        else if (codedMSG[i] == '0')
        {
            if (codedMSG.size() == 1)
            {
                return DecodedString + root->get_val(); 
            }
            root = root->get_left(); 
        }
        else
        {
            throw runtime_error ("Encoding did not match Huffman tree.");
        }

        if (root->is_leaf()) {
            DecodedString += root->get_val(); 
            root = OG_root; 
        }
    }

    if (root != OG_root) {
        throw runtime_error ("Encoding did not match Huffman tree."); 
    }
    return DecodedString; 

}



//deleteTree
//free all tree heap memory
//input: huffman tree node
//output: none
void HuffmanCoder::deleteTree(HuffmanTreeNode* root) {
    if (root == nullptr)
    { 
        return;
    }

    deleteTree(root->get_left());
    deleteTree(root->get_right());
    delete root;
}