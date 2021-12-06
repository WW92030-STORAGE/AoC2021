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

bool isInLine(pair<pii, pii> aaline, ll x, ll y) {
    ll x1 = aaline.first.first;
    ll x2 = aaline.second.first;
    ll y1 = aaline.first.second;
    ll y2 = aaline.second.second;
    if (x1 == x2) {
        if (y1 > y2) swap(y1, y2);
        return (x == x1 && y1 <= y && y <= y2);
    }
    else if (y1 == y2) {
        if (x1 > x2) swap(x1, x2);
        return (y == y1 && x1 <= x && x <= x2);
    }
    
    // diagonal time
    else if (x1 + y1 == x2 + y2) {
        ll minx = min(x1, x2);
        ll maxx = max(x1, x2);
        ll miny = min(y1, y1);
        ll maxy = max(y1, y2);
        if (minx <= x && x <= maxx && miny <= y && y <= maxy) {
            return (x1 + y1 == x + y);
        }
    }
    
    else if (x1 - y1 == x2 - y2) {
        ll minx = min(x1, x2);
        ll maxx = max(x1, x2);
        ll miny = min(y1, y1);
        ll maxy = max(y1, y2);
        if (minx <= x && x <= maxx && miny <= y && y <= maxy) {
            return (x1 - y1 == x - y);
        }
    }
    
    return false;
}

set<pii> points(pair<pii, pii> line) {
    ll x1 = line.first.first;
    ll x2 = line.second.first;
    ll y1 = line.first.second;
    ll y2 = line.second.second;
    ll minx = min(x1, x2);
    ll maxx = max(x1, x2);
    ll miny = min(y1, y2);
    ll maxy = max(y1, y2);
//    cout << minx << " " << maxx << " | " << miny << " " << maxy << endl;
    set<pii> res;
    if (x1 == x2) {
//        cout << "V - ";
        for (ll i = miny; i <= maxy; i++) res.insert({x1, i});
    }
    else if (y1 == y2) {
//        cout << "H - ";
        for (ll i = minx; i <= maxx; i++) res.insert({i, y1});
    }
    else if (x1 + y1 == x2 + y2) {
//        cout << "+ - ";
        for (ll i = miny; i <= maxy; i++) res.insert({maxx - (i - miny), i});
    }
    else if (x1 - y1 == x2 - y2) {
//        cout << "- - ";
        for (int i = miny; i <= maxy; i++) res.insert({minx + (i - miny), i});
    }
//    for (auto i : res) cout << "[" << i.first << " " << i.second << "] ";
//    cout << endl;
    return res;
}

ll insideBounds(pii p, pii r, pii q) {
    ll x1 = p.first;
    ll x2 = q.first;
    ll y1 = p.second;
    ll y2 = q.second;
    ll minx = min(x1, x2);
    ll maxx = max(x1, x2);
    ll miny = min(y1, y2);
    ll maxy = max(y1, y2);
    return (minx <= r.first && r.first <= maxx && miny <= r.second && r.second <= maxy);
}

ll orientation(pii p, pii q, pii r) {
    ll val = (q.second - p.second) * (r.first - q.first) - (q.first - p.first) * (r.second - q.second);
    if (val == 0) return 0;
    return (val > 0) ? 1 : -1;
}

bool intersects(pii p1, pii q1, pii p2, pii q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    
    if (o1 != o2 && o3 != o4)
        return true;
 
    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && insideBounds(p1, p2, q1)) return true;
 
    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && insideBounds(p1, q2, q1)) return true;
 
    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && insideBounds(p2, p1, q2)) return true;
 
     // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && insideBounds(p2, q1, q2)) return true;
 
    return false;
}

int main()
{
    vector<pair<pii, pii>> lines;
    vector<pair<pii, pii>> aligned;
    
    
    ll n;
    cin >> n;
    
    ll fc, sc;
    ll x1, y1, x2, y2;
    ll minx, miny, maxx, maxy;
    for (ll i = 0; i < n; i++) {
        string s1, s2, s3;
        cin >> s1 >> s2 >> s3;
        
        for (ll in = 0; in < s1.length(); in++) {
            if (s1[in] == ',') fc = in;
        }
        
        for (ll in = 0; in < s3.length(); in++) {
            if (s3[in] == ',') sc = in;
        }
        
        string a1 = s1.substr(0, fc);
        string a2 = s1.substr(fc + 1, s1.length() - (fc + 1));
        string a3 = s3.substr(0, sc);
        string a4 = s3.substr(sc + 1, s3.length() - (sc + 1));
//        cout << a1 << " " << a2 << " = " << a3 << " " << a4 << endl;
        
        x1 = atoi(a1.c_str());
        y1 = atoi(a2.c_str());
        x2 = atoi(a3.c_str());
        y2 = atoi(a4.c_str());
//        cout << x1 << " " << y1 << " = " << x2 << " " << y2 << endl;
        lines.pb({{x1, y1}, {x2, y2}});
        if (x1 == x2 || y1 == y2) aligned.pb({{x1, y1}, {x2, y2}});
    }
    
    set<pii> sss;
    ll np = 0;
    for (auto i : lines) {
//        cout << i.first.first << " " << i.first.second << " | " << i.second.first << " " << i.second.second << " = " << points(i).size() << " | ";
//        for (auto p : points(i)) cout << "[" << p.first << " " << p.second << "] ";
//        cout << endl;
    }
    
    vector<set<pii>> pts;
    for (int i = 0; i < n; i++) pts.pb(points(aligned[i]));
    
    for (int i = 0; i < aligned.size(); i++) {
        for (int j = i + 1; j < aligned.size(); j++) {
            if (!intersects(aligned[i].first, aligned[i].second, aligned[j].first, aligned[j].second)) continue;
            for (pii p : pts[i]) {
                if (pts[j].find(p) != pts[j].end()) sss.insert(p);
            }
        }
    }
    
//    for (auto i : sss) cout << i.first << " " << i.second << endl;
    
    cout << sss.size() << endl;
    
    pts.erase(pts.begin(), pts.end());
    sss.erase(sss.begin(), sss.end());
    for (int i = 0; i < n; i++) pts.pb(points(lines[i]));
    
    for (int i = 0; i < lines.size(); i++) {
        for (int j = i + 1; j < lines.size(); j++) {
            if (!intersects(lines[i].first, lines[i].second, lines[j].first, lines[j].second)) continue;
            for (pii p : pts[i]) {
                if (pts[j].find(p) != pts[j].end()) sss.insert(p);
            }
        }
    }
    
//    for (auto i : sss) cout << i.first << " " << i.second << endl;
    
    cout << sss.size() << endl;

    return 0;
}



