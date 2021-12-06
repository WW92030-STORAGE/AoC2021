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

int main()
{
	vector<ll> v;
	ll n;
	while (cin >> n) v.pb(n);
	
	n = v.size();
	ll res = 0;
	for (ll i = 1; i < n; i++) {
	    if (v[i] > v[i - 1]) res++;
	}
	
	cout << res << endl;
   	
   	res = 0;
   	for (ll i = 3; i < n; i++) {
   	    ll sum1 = v[i - 3] + v[i - 2] + v[i - 1];
   	    ll sum2 = v[i - 2] + v[i - 1] + v[i];
   	    if (sum2 > sum1) res++;
   	}
   	
   	cout << res << endl;
   	
   	return 0;
}
