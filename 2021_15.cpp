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

string pad(ll x) {
    string s = "" + to_string(x);
    while (s.length() < 4) s = "0" + s;
    return s;
}

const ll maxn = 512 * 512;
const ll undetermined = LONG_MAX;
vector<ll> graph[maxn];
ll dist[maxn];

map<pii, ll> edges;

bool inBounds(ll x, ll y, ll n, ll m) {
    if (x < 0 || x >= n) return false;
    if (y < 0 || y >= m) return false;
    return true;
}

ll conv(ll x, ll y, ll n, ll m) {
    return x * m + y;
}

void dijkstra(ll start) {
    set<pii> s; // distance for each vertex
    s.insert({0, start});
    dist[start] = 0;
    while (s.size() > 0) {
        pii smol = *s.begin();
        s.erase(s.begin());
//        cout << smol.first << " " << smol.second << " = ";
//        for (auto i : graph[smol.second]) cout << i << " ";
//        cout << endl;
        
        ll now = smol.second;
        for (auto i : graph[now]) {
            ll weight = (*edges.find({now, i})).second;
            if (dist[now] + weight < dist[i]) {
                if (dist[i] != undetermined) s.erase(s.find({dist[i], i}));
                
                dist[i] = dist[now] + weight;
                s.insert({dist[i], i});
            }
        }
    }
}

int main()
{
	ll n, m; // number of lines ... line length
	cin >> n >> m;
	ll grid[n][m];
	for (ll i = 0; i < n; i++) {
	    string s;
	    cin >> s;
	    for (ll j = 0; j < m; j++) grid[i][j] = s[j] - '0';
	}
	
	ll dp[n + 1][m + 1];
	for (ll i = 0; i <= n; i++) {
	    for (ll j = 0; j <= m; j++) dp[i][j] = LLONG_MAX;
	}
	
	dp[1][1] = 0;
	for (ll i = 0; i < n; i++) {
	    for (ll j = 0; j < m; j++) {
	        if (i == 0 && j == 0) continue;
	        ll left = dp[i][j + 1];
	        ll up = dp[i + 1][j];
	        dp[i + 1][j + 1] = min(left, up) + grid[i][j];
	    }
	}
	
	cout << dp[n][m] << endl; // somehow the dp solution worked here ... it does not for the next part.
	// Honestly I recommend using a pathfinding algorithm for both parts but what's done is done i guess ...
	
	ll scale = 5;
	ll protogen[scale * n][scale * m];
	for (ll i = 0; i < n; i++) {
	    for (ll j = 0; j < m; j++) {
	        for (ll x = 0; x < scale; x++) {
	            for (ll y = 0; y < scale; y++) {
	                ll num = (grid[i][j] + x + y);
	                while (num > 9) num -= 9;
	                protogen[i + x * n][j + y * m] = num;
	            }
	        }
	    }
	}
	
	n *= scale;
	m *= scale;
	
	ll dx[4] = {01, 00, -1, 00};
	ll dy[4] = {00, 01, 00, -1};
	// protogen[a][b] = vertex numbered a * m + b
	for (ll i = 0; i < n; i++) {
	    for (ll j = 0; j < m; j++) {
	        int now = conv(i, j, n, m);
	        for (ll in = 0; in < 4; in++) {
	            ll xp = i + dx[in];
	            ll yp = j + dy[in];
	            if (!inBounds(xp, yp, n, m)) continue;
	            ll next = conv(xp, yp, n, m);
//	            cout << i << " " << j << " + " << xp << " " << yp << " = " << now << " + " << next << endl;
	            graph[now].pb(next);
	            edges.insert({{now, next}, protogen[xp][yp]});
	        }
	    }
	}
	
	for (ll i = 0; i < maxn; i++) dist[i] = undetermined;
	dijkstra(0);
	
	cout << dist[n * m - 1] << endl;
	
   	return 0;
}
