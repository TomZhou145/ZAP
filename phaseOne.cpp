#include "phaseOne.h"
#include <string>
#include <istream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector> 
#include <queue>
#include "HuffmanTreeNode.h"

using namespace std; 

vector<int>c_list(256,0); 
priority_queue<HuffmanTreeNode *, vector<HuffmanTreeNode *>,
                   NodeComparator> my_pq;

//*count_freqs
//input: address of an istream
//output: none
//function: counts characters for any input string
void count_freq(std::istream &text)
{
    char c; 
    while(text.get(c)) {
        c_list[c] ++;        
    } 
    for (char i = 0; i < c_list.size(); i ++)
    {
        if (c_list[i] != 0)
        {
        cout << i << ": " << c_list[i] << endl; 
        HuffmanTreeNode *node = new HuffmanTreeNode(i,c_list[i]); 
        my_pq.push(node); 
        }
    }
    while (!my_pq.empty())
    {
        delete my_pq.top(); 
        my_pq.pop(); 
    }

}


//*serialize_tree
//input: the root node of a tree
//output: the serialized string of the tree
//function: converts a tree into a serial code that represents the tree
std::string serialize_tree(HuffmanTreeNode *root)
{
    string serial = "";
    serial = serialize(root); 
    return serial; 
};

//*serialize
//input: the root node of a tree
//output: the serialized string of the tree
//function: the helper function that does the recursion to serialzie tree
std::string serialize(HuffmanTreeNode *root)
{
    string serial_tree = ""; 
    if (root == nullptr) {
        return "";
    }
    if (root->is_leaf())
    {
        serial_tree += "L";
        serial_tree += root->get_val();
        return serial_tree; 
    }
    else
    {
        serial_tree += "I"; 
        serial_tree += serialize(root->get_left());
        serial_tree += serialize(root->get_right());
        return serial_tree; 
    }
}


//*deserial_recur
//input: the serial string of a tree, index integer specifed 
//output: the root node of the tree
//function: converts the serrialize tree string back into a functioning tree
// through recurssion
HuffmanTreeNode *deserial_recur(const std::string &s,int &index) 
{
    if (s[index] == 'L') 
    {
        index++; 
        HuffmanTreeNode *Lnode = new HuffmanTreeNode(s[index]); 
        index++;
        return Lnode; 
        
    } else if(s[index] == 'I') 
    {
        index++; 
        HuffmanTreeNode *Inode = new HuffmanTreeNode(
        deserial_recur(s,index),deserial_recur(s,index));
        return Inode;  
    }
    return nullptr; 
}

//*dserialize_tree
//input: the serial string of a tree,
//output: the root node of the tree
//function: converts the serrialize tree string back into a functioning tree
//
HuffmanTreeNode *deserialize_tree(const std::string &s)
{
    if (s.size() == 0) {
        return nullptr; 
    }
    int index = 0; 
   return deserial_recur(s,index); 
}
    

//clear_heap
//input: root node of a tree
//output: none
//function: delete tree/ free heap space
void clear_heap(HuffmanTreeNode *root) 
{
   if (root == nullptr)
   {
        return; 
   } 
   else {
    clear_heap(root->get_left());
    clear_heap(root->get_right());
    delete root; 
   }
}