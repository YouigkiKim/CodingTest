#include <string>
#include <vector>
#include <iostream>

using namespace std;
    
int solution(vector<vector<int>> dots) {
    int answer = 0;
    vector<pair<pair<int,int>,pair<int,int>>> vec; 
    // 0 1 | 2 3
    int dx1 = dots[0][0] - dots[1][0];
    int dx2 = dots[2][0] - dots[3][0];
    int dy1 = dots[0][1] - dots[1][1];
    int dy2 = dots[2][1] - dots[3][1];
    if( float(dx1) / float(dx2) == float(dy1) / float(dy2) ) return 1;
    // 0 2 | 1 3
    dx1 = dots[0][0] - dots[2][0];
    dx2 = dots[1][0] - dots[3][0];
    dy1 = dots[0][1] - dots[2][1];
    dy2 = dots[1][1] - dots[3][1];
    if( float(dx1) / float(dx2) == float(dy1) / float(dy2) ) return 1;
    // 0 3 | 1 2
    dx1 = dots[0][0] - dots[3][0];
    dx2 = dots[1][0] - dots[2][0];
    dy1 = dots[0][1] - dots[3][1];
    dy2 = dots[1][1] - dots[2][1];
    if( float(dx1) / float(dx2) == float(dy1) / float(dy2) ) return 1;
    return answer;
}