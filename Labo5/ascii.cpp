#include<iostream>
#ifndef ascii_hpp
#define ascii_hpp

using namespace std;

inline void ascii() //funkcja skopiowana na potrzeby tworzenia menu
{

	for (int i = 1; i < 256; i++) {
		cout.width(4);
		cout << (char)(i);
		cout.width(4);
		cout << i;
		if (i % 8 == 0) cout << endl;
	}
}
#endif