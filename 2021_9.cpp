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

ll n, m;
bool inBounds(ll x, ll y) {
    if (x < 0 || x >= n) return false;
    if (y < 0 || y >= m) return false;
    return true;
}

int main()
{
	cin >> n >> m;
	ll board[n][m];
	
	for (ll i = 0; i < n; i++) {
	    string s;
	    cin >> s;
	    for (ll j = 0; j < m; j++) board[i][j] = s[j] - '0';
	}
	
	ll dx[4] = {01, 00, -1, 00};
	ll dy[4] = {00, 01, 00, -1};
	
	for (ll i = 0; i < n; i++) {
//	    for (ll j = 0; j < m; j++) cout << board[i][j];
//	    cout << endl;
	}
	
	vector<pii> extrema;
	
	ll res = 0;
	for (ll i = 0; i < n; i++) {
	    for (ll j = 0; j < m; j++) {
//	        cout << i << " " << j << " -- ";
	        ll minadjacent = LLONG_MAX;
	        for (ll k = 0; k < 4; k++) {
	            ll xp = i + dx[k];
	            ll yp = j + dy[k];
	            if (!inBounds(xp, yp)) continue;
//	            cout << xp << " " << yp << " + ";
	            minadjacent = min(minadjacent, board[xp][yp]);
	        }
	        if (minadjacent > board[i][j]) {
	            res += (1 + board[i][j]);
	            extrema.pb({i, j});
	        }
//	        cout << endl;
	    }
	}
	
	cout << res << endl;
	
	pii component[n][m];
	
	pii nil = {-1, -1};
	for (ll i = 0; i < n; i++) {
	    for (ll j = 0; j < m; j++) component[i][j] = nil;
	}
	
	for (auto p : extrema) cout << "[" << p.first << " " << p.second << "] ";
	cout << endl;
	
	vector<ll> sizes;
	for (pii pp : extrema) {
//	    cout << "[" << pp.first << " " << pp.second << "]" << endl;
	    queue<pii> q;
	    q.push(pp);
	    while (q.size() > 0) {
	        pii now = q.front();
//	        cout << "[" << now.first << " " << now.second << "]" << endl;
	        q.pop();
	        component[now.first][now.second] = pp;
	        for (int i = 0; i < 4; i++) {
	            ll xp = now.first + dx[i];
	            ll yp = now.second + dy[i];
	            if (!inBounds(xp, yp)) continue;
	            if (board[xp][yp] == 9) continue;
	            if (component[xp][yp] != nil) continue;
	            q.push({xp, yp});
	        }
	    }
	    
	    ll sum = 0;
	    for (ll i = 0; i < n; i++) {
	        for (ll j = 0; j < m; j++) {
	            if (component[i][j] == pp) sum++;
	        }
	    }
	    cout << "[" << pp.first << " " << pp.second << "] = " << sum << endl;
	    sizes.pb(sum);
	}
	
	for (ll i = 0; i < n; i++) {
	    for (ll j = 0; j < m; j++) cout << "[" << component[i][j].first << " " << component[i][j].second << "] "; 
	    cout << endl;
	}
	
	sort(sizes.begin(), sizes.end());
	ll nn = sizes.size();
	res = sizes[nn - 1] * sizes[nn - 2] * sizes[nn - 3];
	
	cout << res << endl;
	
	
	
   	return 0;
}






