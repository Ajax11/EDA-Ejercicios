#include <iostream>
#include "BKT.h"

using namespace std;

int main(int argc, char const *argv[]){


	std::vector<string> vec;
	vec.push_back("love");
	vec.push_back("good");
	vec.push_back("poor");
	vec.push_back("door");
	vec.push_back("hood");
	vec.push_back("live");

	BKT tree(vec);
	tree.print();
	return 0;
}