#include "diccBloomFilter.h"
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

static bool insideBoard(int i, int j, int n){
    return(i>=0 and j>=0 and i<n and j<n);
}

int hash1(string s, int size){
    return s.size()%size;
}

int hash2(string s, int size){
    return s.size()%size;
}

int hash3(string s, int size){
    return s.size()%size;
}

void insert(vector<bool>& filter, int size, string s)
{
    int h1,h2,h3;
    h1 = hash1(s, size);
    h2 = hash2(s, size);
    h3 = hash3(s, size);

    filter[h1] = true;
    filter[h2] = true;
    filter[h3] = true;
}

static vector<bool> preprocess(vector<string>& words, int size){
    vector<bool> filter(size, false);
    for (int i = 0; i < words.size(); ++i) insert(filter, size, words[i]);
    return filter;
}

bool isInside(vector<bool> filter, int size, string s){
    int h1,h2,h3;
    h1 = hash1(s, size);
    h2 = hash2(s, size);
    h3 = hash3(s, size);

	if (filter[h1] && filter[h2] && filter[h3])
		return true;
	else
		return false;
}

bool makesSense(VVC& board,int i, int j, string currentWord,const vector<bool>& bloom,int deepness){
    //falta
}

void diccBloomFilterFind(VVC& board, const vector<bool>& bloom,set<string>& foundWords,int i, int j, string currentWord, int deepness){
    if (isInside(bloom, bloom.size(), currentWord)){
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
            if(makesSense(board,i+v,j+h,partialword,bloom,deepness+1)){
                diccBloomFilterFind(board,bloom,foundWords,i+v,j+h,partialword,deepness+1);
            }
        }
    }
    board[i][j].second=false;
}

set<string> diccBloomFilterFind(VVC& board, vector<string> words){
    int bloomFilterSize = int(words.size())*10;
    vector<bool> bloomFilter = preprocess(words, bloomFilterSize);
    for (int i = 0; i < bloomFilter.size(); ++i) cout << bloomFilter[i];
    set<string> foundWords;
    
    for(int i=0;i<board.size();++i){
        for(int j=0;j<board.size();++j){
            string initial ="";
            initial.push_back(board[i][j].first);
            if(makesSense(board,i,j,initial,bloomFilter,0)){
                diccBloomFilterFind(board,bloomFilter,foundWords,i,j,initial,0);
            }
        }
    }
    return foundWords;
}
