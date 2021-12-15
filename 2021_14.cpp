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
#define pii pair<char, char>
#define pb push_back

bool DEBUG = false;
bool DEBUG2 = false;
bool DEBUG3 = true;

map<pii, char> rules;
map<char, ll> freq;

map<pii, ll> pairs;
map<pii, ll> temp;

void push(char c) {
    if (freq.find(c) == freq.end()) freq.insert({c, 0});
    ll prev = (*freq.find(c)).second;
    freq.erase(freq.find(c));
    freq.insert({c, prev + 1});
}

void push2(char c, ll x) {
    if (freq.find(c) == freq.end()) freq.insert({c, 0});
    ll prev = (*freq.find(c)).second;
    freq.erase(freq.find(c));
    freq.insert({c, prev + x});
}

void inc(pii p) {
    if (pairs.find(p) == pairs.end()) pairs.insert({p, 0});
    ll prev = (*pairs.find(p)).second;
    pairs.erase(pairs.find(p));
    pairs.insert({p, prev + 1});
}

void increment(pii p, ll count) {
    if (temp.find(p) == temp.end()) temp.insert({p, 0});
    ll prev = (*temp.find(p)).second;
    temp.erase(temp.find(p));
    temp.insert({p, prev + count});
}

string protogen(string s) {
    vector<char> v;
    v.pb(s[0]);
    for (ll i = 0; i < s.length() - 1; i++) {
        char c1 = s[i];
        char c2 = s[i + 1];
        pii pair = {c1, c2};
        if (rules.find(pair) != rules.end()) v.pb((*rules.find(pair)).second);
        v.pb(s[i + 1]);
    }
    
    string res = "";
    for (ll i = 0; i < v.size(); i++) res += v[i];
    return res;
}

int main()
{
	string s, input;
	cin >> input;
	s = "" + input;
	
	string a, b, c;
	while (cin >> a >> b >> c) {
	    if (a == "__") break;
	    rules.insert({{a[0], a[1]}, c[0]});
	}
	
	if (DEBUG) {
	    for (auto i : rules) cout << i.first.first << " " << i.first.second << " = " << i.second << endl;
	}
	
	for (ll i = 0; i < 10; i++) {
	    s = protogen(s);
	    if (DEBUG) cout << s << endl;
	}
	
    for (ll i = 0; i < s.length(); i++) push(s[i]);
    if (DEBUG) {
        for (auto p : freq) cout << p.first << " " << p.second << endl;
    }
    
    ll maxx = -1;
    ll minx = LLONG_MAX;
    for (auto p : freq) {
        ll x = p.second;
        maxx = max(maxx, x);
        minx = min(minx, x);
    }
    
    cout << maxx - minx << endl;
    
    // this is where it gets interesting
    // we cannot brute force 40 steps
    // the number of elements roughly doubles each step
    // so how do we do this?
    // how about instead of tracking the string we keep track of pairs
    // each pair {a, b} either remains or becomes 2 new pairs: {a, c} and {c, b} where c is the insertion element
    
    for (ll i = 0; i < input.length() - 1; i++) inc({input[i], input[i + 1]});
    if (DEBUG2) {
        for (auto p : pairs) cout << p.first.first << " " << p.first.second << " = " << p.second << endl;
        cout << endl;
    }
    
    for (ll ii = 0; ii < 40; ii++) {
        temp.clear();
        if (DEBUG2) cout << "ITERATION = " << pairs.size() << endl;
        for (auto p : pairs) {
            pii pair = p.first;
            ll count = p.second;
            if (DEBUG2) cout << pair.first << " " << pair.second << " ";
            if (rules.find(pair) != rules.end()) {
                if (DEBUG2) cout << "XXXXX";
                char c = (*rules.find(pair)).second;
                increment({pair.first, c}, count);
                increment({c, pair.second}, count);
            }
            else increment(pair, count);
            
            if (DEBUG2) cout << endl;
        }
        
        swap(pairs, temp);
    }
    
    if (DEBUG3) {
        for (auto p : pairs) cout << p.first.first << " " << p.first.second << " = " << p.second << endl;
    }
    
    freq.clear();
    for (auto p : pairs) { // remember p.first.first counts the occurrence of the first character in each pair
        // it ignores the last character
        push2(p.first.first, p.second);
    }
    // however the last character is always the same
    push(input[input.length() - 1]);
    
    if (DEBUG3) {
        for (auto p : freq) cout << p.first << " " << p.second << endl;
    }
    
    maxx = -1;
    minx = LLONG_MAX;
    for (auto p : freq) {
        ll x = p.second;
        maxx = max(maxx, x);
        minx = min(minx, x);
    }
    
    cout << maxx - minx << endl;
	
   	return 0;
}


