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
#define ll unsigned long long
#define pii pair<ll, ll>
#define pb push_back

int main()
{
	vector<int> v;
	string s;
	cin >> s;
	for (int i = 0; i < s.length(); i += 2) {
	    v.pb(s[i] - '0');
	}
	
	vector<int> incoming;
	for (int i = 0; i < 80; i++) {
	    for (int i : v) {
	        if (i == 0) {
	            incoming.pb(6);
	            incoming.pb(8);
	        }
	        else incoming.pb(i - 1);
	    }
	    swap(v, incoming);
	    incoming.erase(incoming.begin(), incoming.end());
	}
	
	cout << v.size() << endl;
	
	ll maxn = 14;
	ll freq[maxn];
	for (ll i = 0; i < maxn; i++) freq[i] = 0;
	for (ll i = 0; i < s.length(); i += 2) freq[s[i] - '0']++;
	
	ll spectral[maxn];
	for (ll i = 0; i < 256; i++) {
//	    for (ll x = 0; x < maxn; x++) cout << freq[x] << " ";
//	    cout << endl;
	    
	    for (ll index = 0; index < maxn; index++) spectral[index] = 0;
	    spectral[8] += freq[0];
	    spectral[6] += freq[0];
	    for (ll index = 1; index < maxn; index++) spectral[index - 1] += freq[index];
	    
//	    for (ll x = 0; x < maxn; x++) cout << spectral[x] << " ";
//	    cout << endl;
	    
	    for (ll index = 0; index < maxn; index++) freq[index] = spectral[index];
	}
	
	ll res = 0;
	for (ll i = 0; i < maxn; i++) res += freq[i];
	cout << res << endl;
	
   	return 0;
}




