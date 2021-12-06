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

vector<string> clone(vector<string> v) {
    vector<string> res;
    for (auto i : v) res.pb(i);
    return res;
}

int main()
{
	vector<string> vec;
	string temp;
	while (cin >> temp) vec.pb(temp);
	sort(vec.begin(), vec.end());
	
	vector<string> v = clone(vec);
	
	ll n = v[0].length();
	ll arr[n];
	ll ray[n];
	
	for (ll i = 0; i < n; i++) {
	    ll zc = 0;
	    ll oc = 0;
	    for (ll j = 0; j < v.size(); j++) {
	        if ((v[j])[i] == '0') zc++;
	        else oc++;
	    }
	    if (zc > oc) arr[i] = 0;
	    else arr[i] = 1;
	    ray[i] = 1 - arr[i];
	}
	
	ll res = 0;
	for (ll i = 0; i < n; i++) res += (arr[i]) * (1LL<<(n - i - 1));
	ll ans = 0;
	for (ll i = 0; i < n; i++) ans += (ray[i]) * (1LL<<(n - i - 1));
	cout << res << " " << ans << endl;
	cout << res * ans << endl;
	
	// here we go into the death zone
	
	v = clone(vec);
	
	vector<string> next;
	char mostcommon = ' ';
	for (int index = 0; index < n; index++) {
	    ll zc = 0;
	    ll oc = 0;
	    for (ll i = 0; i < v.size(); i++) {
	        if ((v[i])[index] == '0') zc++;
	        else oc++;
	    }
	    if (oc >= zc) mostcommon = '1';
	    else mostcommon = '0';
	    // commonalities
	    
	    for (ll i = 0; i < v.size(); i++) {
	        if ((v[i])[index] == mostcommon) next.pb(v[i]);
	    }
	    sort(next.begin(), next.end());
	    
//	    for (auto i : next) cout << i << endl;
//	    cout << "--------" << mostcommon << " " << index << endl;
	    
	    v = clone(next);
	    next.erase(next.begin(), next.end());
	}
	
	cout << "LEVEL " << next[0] << endl;
	
	v = clone(vec);
	next.erase(next.begin(), next.end());
	char leastcommon = ' ';
	for (int index = 0; index < n; index++) {
	    ll zc = 0;
	    ll oc = 0;
	    for (ll i = 0; i < v.size(); i++) {
	        if ((v[i])[index] == '0') zc++;
	        else oc++;
	    }
	    if (zc <= oc) leastcommon = '0';
	    else leastcommon = '1';
	    // commonalities
	    
	    for (ll i = 0; i < v.size(); i++) {
	        if ((v[i])[index] == leastcommon) next.pb(v[i]);
	    }
	    sort(next.begin(), next.end());
	    
//	    for (auto i : next) cout << i << endl;
//	    cout << "--------" << leastcommon << " " << index << endl;
	    
	    v = clone(next);
	    next.erase(next.begin(), next.end());
	}
	
	cout << "LEVEL " << next[0] << endl;
	
   	return 0;
}




