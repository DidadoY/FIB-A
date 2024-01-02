#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int ALPHABET_SIZE = 26;

typedef vector<pair<char,bool>> VC;
typedef vector<VC>VVC;

//Explanation and part of the code for the method
//https://www.geeksforgeeks.org/trie-insert-and-search/

struct TrieNode{
    struct TrieNode *children[ALPHABET_SIZE];
    
    bool isEndOfWord;
};
set<string> diccTrieFind(VVC& board, vector<string> words);
