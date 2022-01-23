//============================================================================
// Name        : Parity.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>


using namespace std;

class UnionFind {
	unordered_map<long long, long long> hashMap;
public:
	UnionFind(long long size){};
	void unio(long long value1, long long value2){
		long long p1 = find(value1);
		long long p2 = find(value2);

		if (p1 > p2) {
			hashMap[p2] = p1;
		}
		else {
			hashMap[p1] = p2;
		}
	};

	long long find(long long value){
		long long currentValue = value;
		while (hashMap.count(currentValue) > 0 && hashMap[currentValue] != currentValue){
			currentValue = hashMap[currentValue];
		}

		hashMap[value] = currentValue;
		return currentValue;
	};
};

int main() {
    long long length;
    while (cin>> length) {
    	if (length < 0) break;

    	UnionFind uf(length);

    	auto getNegative = [&](long long value){
    		return length + 1 + value;
    	};

    	unsigned questions;
    	cin >> questions;

    	bool correct = true;
    	for (unsigned idx = 1; idx <= questions; ++idx) {
    		long long a, b;
    		string parity;
    		cin >> a >> b >> parity;

            if (!correct) continue;

    		if (parity == "even") {
    			uf.unio(a, b + 1);
    			uf.unio(getNegative(a), getNegative(b + 1));
    		}
    		else {
    			uf.unio(a, getNegative(b + 1));
    			uf.unio(b + 1, getNegative(a));
    		}

    		long long gpa = uf.find(a);
    		long long gna = uf.find(getNegative(a));

    		long long gpb = uf.find(b+1);
    		long long gnb = uf.find(getNegative(b+1));

    		if (gpa == gna || gpb == gnb) {
				cout <<  idx - 1 << endl;
				correct = false;
			}
    	}
    	if (correct) cout << questions << endl;
    }

	return 0;
}
