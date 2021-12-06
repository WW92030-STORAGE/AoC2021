#include <bits/stdc++.h> 
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
#include <set>
#include <string>
#include <queue>
#include <stack>
#include <functional>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
#define ll long long
#define pii pair<ll, ll>
#define pb push_back

bool check(bool b[5][5]) {
    bool res = true;
    for (int i = 0; i < 5; i++) {
        res = true;
        for (int j = 0; j < 5; j++) res = res && b[i][j];
        if (res) return true;
    }
    
    for (int i = 0; i < 5; i++) {
        res = true;
        for (int j = 0; j < 5; j++) res = res && b[j][i];
        if (res) return true;
    }
    return false;
}

vector<int> v;

pii solve(int b[5][5]) {
    bool spaces[5][5];
    for (int i = 0; i < 25; i++) spaces[i / 5][i % 5] = false;
    for (int index = 0; index < v.size(); index++) {
        int now = v[index];
        for (int i = 0; i < 25; i++) {
            if (b[i / 5][i % 5] == now && !spaces[i / 5][i % 5]) {
                spaces[i / 5][i % 5] = true;
                break;
            }
        }
        
        int count = 0;
        for (int i = 0; i < 25; i++) count += (spaces[i / 5][i % 5]) ? 1 : 0;
//        cout << count << endl;
        
        if (check(spaces)) {
            int t = index + 1;
            int score = 0;
            for (int i = 0; i < 25; i++) {
                if (!spaces[i / 5][i % 5]) score += b[i / 5][i % 5];
            }
            return {t, score};
        }
    }
    
    return {-1, -1};
}

int main()
{
    
    string s;
    cin >> s;
    cout << s << endl;
    
    for (int i = 0; i < s.length(); i += 3) {
        int d1 = s[i] - '0';
        int d2 = s[i + 1] - '0';
        v.pb(10 * d1 + d2);
    }
    
//    for (auto i : v) cout << i << " ";
    cout << endl;
    
//	freopen("boards.in", "r", stdin);
	
	int nboards;
	cin >> nboards;
	int boards[nboards][5][5];
    
    for (int i = 0; i < nboards; i++) {
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) cin >> boards[i][x][y];
        }
    }
    
    vector<pii> res;
    for (int i = 0; i < nboards; i++) {
        pii sc = solve(boards[i]);
        res.pb(sc);
    }
    
    sort(res.begin(), res.end());
    for (auto i : res) cout << v[i.first - 1] << " " << i.second << endl;
    // The first number in each pair represents the number that was last called ... the 2nd is the unmarked score.
	
   	return 0;
}




