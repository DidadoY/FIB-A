#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

typedef vector<pair<char,bool>> VC;
typedef vector<VC>VVC;

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

set<string> diccSortedVectorFind(VVC& board, vector<string> words);
