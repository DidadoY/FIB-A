#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include "diccSortedVector.h"
#include "diccBloomFilter.h"
#include "diccTrie.h"
#include "diccDHashing.h"

using namespace std;


bool insideBoard(int i, int j, int n){
    return(i>=0 and j>=0 and i<n and j<n);
}

pair<bool,vector<direction>> enoughRoom(VVC& board, int i, int j, int n){
    if(board[i][j].first!='0')return make_pair(false,vector<direction>());
    
    vector<direction> directions;
    if(n==0)return make_pair(true,vector<direction>());
    
    if(board[i][j].second==false){
        board[i][j].second=true;
        vector<direction> allDirections={Down,Up,Left,Right,UpRight,UpLeft,DownRight,DownLeft};
        random_shuffle(allDirections.begin(),allDirections.end());
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
                pair<bool,vector<direction>> possible=enoughRoom(board,i+v,j+h,n-1);
                if(possible.first){
                    possible.second.push_back(dir);
                    return make_pair(true,possible.second);
                }
            }
            
        }
    }
    return make_pair(false,vector<direction>());
}


void place(VVC& board, string word, int i, int j,vector<direction> directions){
    int k = 0;
    for(int l = directions.size()-1;l>=0;--l){
        direction dir=directions[l];
        board[i][j].first=word[k];
        ++k;
        if(dir==Up)--i;
        else if(dir==Down)++i;
        else if(dir==Left)--j;
        else if(dir==Right)++j;
        else if(dir==UpRight){
            --i;
            ++j;
        }
        else if(dir==UpLeft){
            --i;
            --j;
        }
        else if(dir==DownRight){
            ++i;
            ++j;
        }
        else if(dir==DownLeft){
            ++i;
            --j;
        }
    }
}

void place(VVC& board, string word){
    int i = rand()%board.size();
    int j = rand()%board.size();
    
    pair<bool,vector<direction>> placement = enoughRoom(board,i,j,word.size());
    
    while(!placement.first){
        i = rand()%board.size();
        j = rand()%board.size();
        placement = enoughRoom(board,i,j,word.size());
        
        for(int i=0;i<board.size();++i){
            for(int j=0;j<board.size();++j)
                board[i][j].second=false;
        }
        
    }
    
    place(board,word,i,j,placement.second);
}

int main(){
    srand(3); 
    
    int numberWords,boardSize,plantWords;
    cin>>numberWords>>plantWords;
    
    vector<string> dictionary(numberWords);
    for(int i=0;i<numberWords;++i)
        cin>>dictionary[i];
    
    unordered_set<string> selectedWords;
    
    while(selectedWords.size()!=plantWords){
        int pos = rand()%dictionary.size();
        if(selectedWords.find(dictionary[pos])==selectedWords.end()){
            selectedWords.insert(dictionary[pos]);
        }
    }
    
    for(auto d:selectedWords)
        cout<<d<<endl;
    
    cin>>boardSize;
    VVC board(boardSize,VC(boardSize,make_pair('0',false)));
    
    for(auto word:selectedWords)
        place(board,word);
    
    for(int i=0;i<boardSize;++i){
        for(int j=0;j<boardSize;++j){
            if(board[i][j].first=='0')
                board[i][j].first='a'+rand()%('z'-'a'+1);//'0' (Use 0 for easier debugging);
        }
    }
    
    for(int i=0;i<boardSize;++i){
        for(int j=0;j<boardSize;++j){
            cout<<board[i][j].first;
        }
        cout<<endl;
    }
    
    for(int i=0;i<board.size();++i){
        for(int j=0;j<board.size();++j)
            board[i][j].second=false;
    }
    
    
    cout<<"Select strategy: "<<endl;
    cout<<"1: Sorted vector"<<endl;
    cout<<"2: Trie"<<endl;
    cout<<"3: Bloom filter"<<endl;
    cout<<"4: Double hashing table"<<endl;

    int decision;
    cin>>decision;
    
    
    set<string> found;
    
    if(decision==1){
        found = diccSortedVectorFind(board,dictionary);
    }
    else if(decision == 2){
        found = diccTrieFind(board,dictionary);
    }
    else if(decision==3){
        found = diccBloomFilterFind(board,dictionary);
    }
    
    bool allFound = true;
    string aux;
    for(auto w: selectedWords){
        allFound=allFound and (found.find(w)!=found.end());
        aux = w;
        if(!allFound)break;
    }
    
    
    cout<<(allFound ? "All words were found. Words not selected but that appear in the dictionary may have been found as a result of the placement and searching mechanism ":aux)<<endl;
    cout<<"Found: "<<endl;
    for(auto w: found)
        cout<<w<<endl;
}
