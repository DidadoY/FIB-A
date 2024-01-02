#include "diccSortedVector.h"


static vector<string> preprocess(vector<string>& words){
    sort(words.begin(),words.end());
    return words;
}


static bool insideBoard(int i, int j, int n){
    return(i>=0 and j>=0 and i<n and j<n);
}

pair<bool,int> dicotomicSearch(const vector<string>& words,int l, int r, string word){
    if(l>r)return make_pair(false,l);
    if(r==l){
        if(r<0) return make_pair(false,0);
        if(r>=words.size())return make_pair(false,words.size()-1);
        if(words[r]==word)return make_pair(true,r);
        if(words[r]>word)return make_pair(false,r);
        else return make_pair(false,r);
    }
    
    int n =(l+r)/2;
    if(words[n]==word)return make_pair(true,n);
    
    if(words[n]>word)return dicotomicSearch(words,l,n-1,word);
    else return dicotomicSearch(words,n+1,r,word);
}


bool makesSense(VVC& board,int i, int j, string currentWord,const vector<string>& words,int deepness){
    if(board[i][j].second)return false;
    int k = dicotomicSearch(words,0,words.size(),currentWord).second;
    if(words[k][deepness]!=currentWord[deepness] and k<words.size()-1)++k;
    if(words[k][deepness]!=currentWord[deepness])return false;
    return true;
}

void reset(VVC& board){
    for(int i=0;i<board.size();++i){
        for(int j = 0;j<board.size();++j){
            board[i][j].second=false;
        }
    }
}

void diccSortedVectorFind(VVC& board,const vector<string>& words,set<string>& foundWords,int i, int j, string currentWord, int deepness){
    board[i][j].second=true;
    //cout<<currentWord<<endl;
    if(dicotomicSearch(words,0,words.size(),currentWord).first){
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
            if(makesSense(board,i+v,j+h,partialword,words,deepness+1)){
                diccSortedVectorFind(board,words,foundWords,i+v,j+h,partialword,deepness+1);
            }
        }
    }
    board[i][j].second=false;
}


set<string> diccSortedVectorFind(VVC& board, vector<string> words){
    vector<string> sortedWords = preprocess(words); //It may be useful to insert the reverse words too
    
    set<string> foundWords;
    
    for(int i=0;i<board.size();++i){
        for(int j=0;j<board.size();++j){
            string initial ="";
            initial.push_back(board[i][j].first);
            if(makesSense(board,i,j,initial,words,0)){
                diccSortedVectorFind(board,words,foundWords,i,j,initial,0);
            }
            //reset(board);
        }
    }
    
    return foundWords;
}
