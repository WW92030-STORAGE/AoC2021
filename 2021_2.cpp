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
	ll x = 0;
	ll y = 0;
	ll magnitude;
	string direction;
	/*
	while (cin >> direction >> magnitude) {
	    if (direction == "down") y += magnitude;
	    if (direction == "up") y -= magnitude;
	    if (direction == "forward") x += magnitude;
	}
	
	cout << (x * y) << endl;
	*/
	
	x = 0;
	y = 0;
	ll aim = 0;
	while (cin >> direction >> magnitude) {
	    if (direction == "down") aim += magnitude;
	    if (direction == "up") aim -= magnitude;
	    if (direction == "forward") {
	        x += magnitude;
	        y += aim * magnitude;
	    }
	}
   	
   	cout << (x * y) << endl;
   	
   	return 0;
}







