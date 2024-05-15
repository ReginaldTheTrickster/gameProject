#ifndef DEFINES_HPP_INCLUDED
#define DEFINES_HPP_INCLUDED

#define WINDOW_TITLE "This is basically a chess game"

using namespace std;

typedef pair<int,int> Location;

inline pair<int,int> makeLocation(int i,int j){
    return make_pair(i,j);
}

#endif // !DEFINES_HPP_INCLUDED
