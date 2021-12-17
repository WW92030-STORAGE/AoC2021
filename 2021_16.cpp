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
#define ll long
#define pii pair<ll, ll>
#define pb push_back

char cc[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

bool DEBUG0 = false; // print out binary hex chars
bool DEBUG1 = false; // print out info in parsing
bool DEBUG2 = false; // print out versions and literals
bool DEBUG3 = true;
bool DEBUG4 = false;

ll conv(char c) {
    for (ll i = 0; i < 16; i++) {
        if (c == cc[i]) return i;
    }
    return 0;
}

vector<ll> prebin(string s) {
    vector<ll> res;
    vector<ll> tempnum;
    for (ll i = 0; i < s.length(); i++) {
        tempnum.clear();
        char c = s[i];
        ll hex = conv(c);
        for (ll i = 8; i > 0; i /= 2) {
            if (hex >= i) {
                res.pb(1);
                tempnum.pb(1);
                hex -= i;
            }
            else {
                res.pb(0);
                tempnum.pb(0);
            }
        }
        if (!DEBUG0) continue;
        cout << c << " = ";
        for (auto i : tempnum) cout << i;
        cout << endl;
    }
    
    return res;
}

vector<ll> subarray(vector<ll> v, ll a, ll b) {
    vector<ll> res;
    for (ll i = a; i < b; i++) res.pb(v[i]);
    return res;
}

ll dec(vector<ll> bin) {
    ll res = 0;
    ll exp = 1;
    for (ll i = bin.size() - 1; i >= 0; i--) {
        res += bin[i] * exp;
        exp *= 2;
    }
    return res;
}

ll query(vector<ll> bin, ll a, ll b) {
    return dec(subarray(bin, a, b));
}

void print(vector<ll> v) {
    for (auto i : v) cout << i;
}

void println(vector<ll> v) {
    print(v);
    cout << endl;
}

void displn(vector<ll> v) {
    for (auto i : v) cout << i << " ";
    cout << endl;
}

vector<ll> versions;
vector<ll> literals;

map<ll, ll> counts;
map<ll, ll> expected;

map<ll, vector<ll>> subps;
map<ll, ll> pvalues;
map<ll, ll> ops;

void spectrum(ll x, ll y) {
    if (subps.find(x) == subps.end()) {
        vector<ll> v;
        subps.insert({x, v});
    }
    ((*subps.find(x)).second).pb(y);
}

ll search(map<ll, ll> m, ll x) {
    if (m.find(x) == m.end()) return 0;
    return (*m.find(x)).second;
}

ll get(ll x) {
    if (counts.find(x) == counts.end()) return 0;
    return (*counts.find(x)).second;
}

void increment(ll x) {
    if (counts.find(x) == counts.end()) counts.insert({x, 0});
    ll prev = get(x);
    counts.erase(counts.find(x));
    counts.insert({x, prev + 1});
}

ll process(vector<ll> bin, ll a, ll b) {
    ll version = query(bin, a, a + 3);
    versions.pb(version);
    
    ll type = query(bin, a + 3, a + 6);
    ops.insert({a, type});
    if (DEBUG1) cout << "INDEX " << a << " = VERSION " << version << " + TYPE " << type << endl;
    if (type == 4) { // read binary numbers
        if (DEBUG1) cout << "READING ... ";
        if (DEBUG1) println(subarray(bin, a, b));
        ll index = a + 6;
        bool keepgoing = true;
        ll sum = 0;
        for (index = a + 6; index < b && keepgoing; index += 5) {
            vector<ll> group = subarray(bin, index, index + 5);
            if (group[0] == 0) keepgoing = false;
            ll number = query(group, 1, 5);
            if (DEBUG1) print(group);
            sum *= 16;
            sum += number;
            if (DEBUG1) cout << " = " << number << " >>> " << sum << endl;
        }
        literals.pb(sum);
        if (DEBUG1) cout << "STOPPED AT " << index << endl;
        pvalues.insert({a, sum});
        return index;
    }
    else { // recursively process a subpacket subarray
        ll index = 0;
        ll protogen = bin[a + 6];
        if (protogen == 0) {
            ll length = query(bin, a + 7, a + 7 + 15);
            if (DEBUG1) cout << a + 7 + 15 << " HAS " << length << " LENGTH" << endl;
            spectrum(a, a + 7 + 15);
            index = process(bin, a + 7 + 15, a + 7 + 15 + length);
            while (index < a + 7 + 15 + length) {
                spectrum(a, index);
                index = process(bin, index, a + 7 + 15 + length);
            }
            if (DEBUG1) cout << "PROCESSED PACKETS " << index << endl;
            if (DEBUG1) println(subarray(bin, index, b));
        }
        else {
            ll freq = query(bin, a + 7, a + 7 + 11);
            if (DEBUG1) cout << a + 7 + 11 << " HAS " << freq << " PACKETS" << endl;
            expected.insert({a + 7 + 11, freq});
            spectrum(a, a + 7 + 11);
            index = process(bin, a + 7 + 11, b);
            increment(a + 7 + 11);
            if (DEBUG1) cout << "PROCESSED PACKET " << get(a + 7 + 11) << " << " << index << endl;
            while (get(a + 7 + 11) < (*expected.find(a + 7 + 11)).second) {
                spectrum(a, index);
                index = process(bin, index, b);
                increment(a + 7 + 11);
                if (DEBUG1) cout << "PROCESSED PACKET " << get(a + 7 + 11) << endl;
            }
        }
        return index;
    }
}

ll eval(ll src) {
    ll res = 0;
    ll type = search(ops, src);
    if (DEBUG3) cout << src << " TYPE " << type << endl;
    if (type == 4) return search(pvalues, src);
    
    vector<ll> subs = (*subps.find(src)).second;
    if (DEBUG3) displn(subs);
    if (type == 0) {
        res = 0;
        for (auto i : subs) res += eval(i);
    }
    if (type == 1) {
        res = 1;
        for (auto i : subs) res *= eval(i);
    }
    if (type == 2) {
        res = LLONG_MAX;
        for (auto i : subs) res = min(res, eval(i));
    }
    if (type == 3) {
        res = LLONG_MIN;
        for (auto i : subs) res = max(res, eval(i));
    }
    if (type == 5) {
        res = 0;
        if (eval(subs[0]) > eval(subs[1])) res = 1;
    }
    if (type == 6) {
        res = 0;
        if (eval(subs[0]) < eval(subs[1])) res = 1;
    }
    if (type == 7) {
        res = 0;
        if (eval(subs[0]) == eval(subs[1])) res = 1;
    }
    return res;
}

int main()
{
	string input;
	cin >> input;
	
	string s = input;
	vector<ll> bin = prebin(s);
	if (DEBUG1) println(bin);
	
	ll n = bin.size();
	
	process(bin, 0, n);
	
	
	if (DEBUG2) displn(versions);
	if (DEBUG2) displn(literals);
	
	ll res = 0;
	for (auto i : versions) res += i;
	cout << "VER SUM " << res << endl;
	
	for (auto i : subps) {
	    if (!DEBUG2) break;
	    cout << i.first << " ";
	    displn(i.second);
	}
	
	if (DEBUG2) {
	    cout << "LITERAL VALUES" << endl;
	for (auto i : pvalues) cout << i.first << " = " << i.second << endl;
	cout << "OPERATIONS" << endl;
	for (auto i : ops) cout << i.first << " = " << i.second << endl;
	}
	
	
	cout << eval(0) << endl;
	
   	return 0;
}

