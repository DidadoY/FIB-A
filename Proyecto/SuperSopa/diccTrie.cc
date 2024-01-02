#include "diccTrie.h"
enum direction{
    Up,
    Down,
    Left,
    Right,
    UpRight,
    UpLeft,
    DownRight,
    DownLeft
};


struct TrieNode *getNode()
{
    struct TrieNode *pNode =  new TrieNode;
  
    pNode->isEndOfWord = false;
  
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
  
    return pNode;
}

static bool insideBoard(int i, int j, int n){
    return(i>=0 and j>=0 and i<n and j<n);
}


void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
  
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
  
        pCrawl = pCrawl->children[index];
    }
  
    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}

struct TrieNode* preprocess(vector<string>& words){
    struct TrieNode* empty = getNode();
    
    for(int i = 0;i<words.size();++i){
        insert(empty,words[i]);
    }
    
    return empty;
}

pair<bool,int> search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
    
    int count =0;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return make_pair(false,count);
        
        ++count;
        pCrawl = pCrawl->children[index];
    }
  
    return make_pair((pCrawl->isEndOfWord),count);
}

bool makesSense(VVC& board,int i, int j, string currentWord,struct TrieNode* dictionary,int deepness){
    if(board[i][j].second)return false;
    pair<bool,int> k = search(dictionary,currentWord);
    return (k.second==deepness);
}


void diccTrieFind(VVC& board,struct TrieNode* dictionary,set<string>& foundWords,int i, int j, string currentWord, int deepness){
    board[i][j].second=true;
    //cout<<currentWord<<endl;
    if(search(dictionary,currentWord).first){
        foundWords.insert(currentWord);
    }
    vector<direction> allDirections={Down,Up,Left,Right,UpRight,UpLeft,DownRight,DownLeft};
    for(auto dir: allDirections){
        int h=0,v=0;
        if(dir==Down)v=1;
        else if(dir==Up) v=-1;
        else if(dir==Left) h=-1;
        else if(dir==Right)h=1;
        else if(dir==UpRight){
            v = -1;
            h = 1;
        }
        else if(dir==UpLeft){
            v=-1;
            h=-1;
        }
        else if(dir==DownRight){
            v=1;
            h=1;
        }
        else{
            v=1;
            h=-1;
        }
        
        if(insideBoard(i+v,j+h,board.size())){
            string partialword = currentWord;
            partialword.push_back(board[i+v][j+h].first);
            //cout<<partialword<<endl;
            if(makesSense(board,i+v,j+h,partialword,dictionary,deepness+1)){
                diccTrieFind(board,dictionary,foundWords,i+v,j+h,partialword,deepness+1);
            }
        }
    }
    board[i][j].second=false;
}



set<string> diccTrieFind(VVC& board, vector<string> words){
    struct TrieNode *dictionary = preprocess(words);
    
    set<string> foundWords;
    
    for(int i=0;i<board.size();++i){
        for(int j=0;j<board.size();++j){
            string initial ="";
            initial.push_back(board[i][j].first);
            if(makesSense(board,i,j,initial,dictionary,1)){
                diccTrieFind(board,dictionary,foundWords,i,j,initial,1);
            }
            //reset(board);
        }
    }
    
    return foundWords;
}
