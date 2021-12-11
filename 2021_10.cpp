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

char open[4] = {'(', '[', '{', '<'};
char close[4] = {')', ']', '}', '>'};
ll score[4] = {3, 57, 1197, 25137};
ll points[4] = {1, 2, 3, 4};

ll index(char c) {
    for (int i = 0; i < 4; i++) {
        if (c == open[i]) return i;
    }
    return -1;
}

ll xedni(char c) {
    for (int i = 0; i < 4; i++) {
        if (c == close[i]) return i;
    }
    return -1;
}

int main()
{
	vector<string> v;
	string s;
	while (cin >> s) v.pb(s);
	ll n = v.size();
	
	vector<string> incomplete;
	
	ll res = 0;
	
	for (ll sk = 0; sk < n; sk++) {
	    s = v[sk];
//	    cout << s << endl;
	    stack<char> stac;
	    ll badindex = -1;
	    for (ll i = 0; i < s.length(); i++) {
	        char c = s[i];
	        if (index(c) >= 0) stac.push(c);
	        else {
	            cout << stac.size() << " ";
	            int corresponding = xedni(c);
	            if (open[corresponding] == stac.top()) stac.pop();
	            else {
//	                cout << "BAD INDEX " << i << " " << s[i] << endl;
	                badindex = i;
	                break;
	            }
	        }
	    }
	    if (badindex >= 0) res += score[xedni(s[badindex])];
	    else incomplete.pb(s);
	}
	
	cout << res << endl;
	
	for (string s : incomplete) cout << s << endl;
	
	vector<ll> scores;
	for (string s : incomplete) {
	    stack<char> stac;
	    for (ll i = 0; i < s.length(); i++) {
	        char c = s[i];
	        if (index(c) >= 0) stac.push(c);
	        else {
	            cout << stac.size() << " ";
	            int corresponding = xedni(c);
	            if (open[corresponding] == stac.top()) stac.pop();
	        }
	    }
	    
	    ll sum = 0;
	    while (stac.size() > 0) {
	        char c = stac.top();
	        stac.pop();
	        sum = (5 * sum + points[index(c)]);
	        cout << c << " ";
	    }
	    cout << sum << endl;
	    scores.pb(sum);
	}
	
	sort(scores.begin(), scores.end());
	cout << scores[scores.size() / 2] << endl;
	
   	return 0;
}





