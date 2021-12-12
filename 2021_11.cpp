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

ll n = 10;
ll x = 100;

bool inBounds(ll x, ll y) {
    if (x < 0 || x >= n) return false;
    if (y < 0 || y >= n) return false;
    return true;
}

int main()
{
    ll arr[n][n];
	ll board[n][n];
	for (ll i = 0; i < n; i++) {
	    string s;
	    cin >> s;
	    for (int j = 0; j < n; j++) arr[i][j] = (int)(s[j] - '0');
	}
	
	ll dx[8] = {01, 01, 00, -1, -1, -1, 00, 01};
	ll dy[8] = {00, 01, 01, 01, 00, -1, -1, -1};
	
	for (ll i = 0; i < n * n; i++) board[i / n][i % n] = arr[i / n][i % n];
	
	ll count = 0;
	bool flash[n][n];
	for (ll sk = 0; sk < x; sk++) {
	    for (ll i = 0; i < n * n; i++) flash[i / n][i % n] = false;
	    for (ll i = 0; i < n * n; i++) board[i / n][i % n]++;
	    bool update = false;
	    while (true) {
	        update = false;
	        for (ll i = 0; i < n; i++) {
	            for (ll j = 0; j < n; j++) {
	                if (board[i][j] > 9 && !flash[i][j]) {
	                    flash[i][j] = true;
	                    update = true;
	                    for (ll k = 0; k < 8; k++) {
	                        ll xp = i + dx[k];
	                        ll yp = j + dy[k];
	                        if (!inBounds(xp, yp)) continue;
	                        board[xp][yp]++;
	                    }
	                } 
	            }
	        }
	        if (!update) break;
	    }
	    
	    for (ll i = 0; i < n; i++) {
	        for (ll j = 0; j < n; j++) {
	            if (flash[i][j]) {
	                board[i][j] = 0;
	                count++;
	            }
	        }
	    }
	    
	    for (ll i = 0; i < n; i++) {
	        for (ll j = 0; j < n; j++) cout << board[i][j];
	        cout << endl;
	    }
	    cout << "----------" << endl;
	}
	
	cout << count << endl;
	
	// reset
	
	for (ll i = 0; i < n * n; i++) board[i / n][i % n] = arr[i / n][i % n];
	
	for (ll sk = 0; ; sk++) {
	    count = 0;
	    for (ll i = 0; i < n * n; i++) flash[i / n][i % n] = false;
	    for (ll i = 0; i < n * n; i++) board[i / n][i % n]++;
	    bool update = false;
	    while (true) {
	        update = false;
	        for (ll i = 0; i < n; i++) {
	            for (ll j = 0; j < n; j++) {
	                if (board[i][j] > 9 && !flash[i][j]) {
	                    flash[i][j] = true;
	                    update = true;
	                    for (ll k = 0; k < 8; k++) {
	                        ll xp = i + dx[k];
	                        ll yp = j + dy[k];
	                        if (!inBounds(xp, yp)) continue;
	                        board[xp][yp]++;
	                    }
	                } 
	            }
	        }
	        if (!update) break;
	    }
	    
	    for (ll i = 0; i < n; i++) {
	        for (ll j = 0; j < n; j++) {
	            if (flash[i][j]) {
	                board[i][j] = 0;
	                count++;
	            }
	        }
	    }
	    if (count == n * n) {
	        cout << sk + 1 << endl;
	        break;
	    }
	}
	
   	return 0;
}






