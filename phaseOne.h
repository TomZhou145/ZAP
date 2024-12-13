#ifndef __PHASEONE_H
#define __PHASEONE_H

#include <istream>
#include <string>
#include <fstream>
#include <vector> 

#include "HuffmanTreeNode.h"

void count_freq(std::istream &text);
std::string serialize_tree(HuffmanTreeNode *root);
std::string serialize(HuffmanTreeNode *root); 

HuffmanTreeNode *deserialize_tree(const std::string &s);

HuffmanTreeNode *deserial_recur(const std::string &s,int &index); 


void clear_heap(HuffmanTreeNode *root);
#endif