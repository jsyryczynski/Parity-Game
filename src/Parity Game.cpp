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

template <class T> class UnionFind {
	unordered_map<T, T> hashMap;
public:
	UnionFind(){};
	void unio(T value1, T value2){	// union is a keyword in C++
		T p1 = find(value1);
		T p2 = find(value2);

		if (p1 > p2) {
			hashMap[p2] = p1;
		}
		else {
			hashMap[p1] = p2;
		}
	};

	T find(T value){
		T currentValue = value;
		while (hashMap.count(currentValue) > 0 && hashMap[currentValue] != currentValue){
			currentValue = hashMap[currentValue];
		}

		hashMap[value] = currentValue;
		return currentValue;
	};
};

int main() {
	// redirect in.txt to stdin!
    //std::ifstream in("in.txt");
    //std::cin.rdbuf(in.rdbuf());

    long long length;
    while (cin>> length) {
    	if (length < 0) break;

    	UnionFind<long long> uf;

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

    		if (gpa == gna) {
				cout <<  idx - 1 << endl;
				correct = false;
			}
    	}
    	if (correct) cout << questions << endl;
    }

	return 0;
}
