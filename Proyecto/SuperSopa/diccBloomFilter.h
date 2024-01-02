#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

typedef vector<pair<char,bool>> VC;
typedef vector<VC>VVC;

set<string> diccBloomFilterFind(VVC& board, vector<string> words);
