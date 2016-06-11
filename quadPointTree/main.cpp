#include "quadPointTree.h"
#include <utility>      // std::pair
#include <vector>

#include <iostream>
#include <fstream>
#include <string>

#include <stdio.h>

using namespace std;

//void field(quadPointTree tree){
void fillTree(quadPointTree & tree){
    ifstream stream("test.txt");
    string buf;
    getline(stream, buf , '\n');
    while(stream)
    {
        point tempPoint;
        int space;
        space = buf.find(' ');
        string cad[2];
        int pos = 0;
        for (int i = 0; i < buf.length(); ++i){
            if (buf[i] == ' '){
                pos=1;
                continue;
            }
            cad[pos]+=buf[i];
        }
         std::string::size_type sz;     // alias of size_t
        tempPoint.first = stod(cad[0]);
        tempPoint.second = stod(cad[1]);
        tree.insert(tempPoint);
//        vec.push_back(tempPoint);
        getline(stream, buf , '\n');
    }
    stream.close();

}

int main(int argc, char const *argv[])
{


/*
	std::vector<point> vec;

	field(vec);

	cout<<endl<<"Field"<<endl;

	for (int i = 0; i < vec.size(); ++i)
	{
		cout<<vec[i].first<<" <-> "<<vec[i].second<<endl;
	}

	for (int i = 0; i < vec.size(); ++i){
		cout<< vec[i].first <<" <-> "<< vec[i].second<<endl;
	}

*/

	quadPointTree numberTree;
	fillTree(numberTree);

/*
	point A;

	A.first = 0;
	A.second = 0;
	B.insert(A);

	A.first = 10;
	A.second = 10;
	B.insert(A);

	A.first = 20;
	A.second = 20;
	B.insert(A);
	A.first = 30;
	A.second = 30;
	B.insert(A);

	A.first = -10;
	A.second = 10;
	B.insert(A);

*/
	numberTree.print();
/*

	cout<<endl<<B.findElement(1,3)<<endl;

	point Afirst;
	point Cfirst;

	Afirst.first = -1;
	Afirst.second = -1;

	Cfirst.first = 6;
	Cfirst.second = 6;

	B.rangeElements(Afirst,Cfirst);
*/

	return 0;
}
