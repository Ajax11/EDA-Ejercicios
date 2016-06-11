#include "quadTree.h"
#include <utility>      // std::pair
#include <vector>

#include <iostream>
#include <fstream>
#include <string>

#include <stdio.h>

using namespace std;

void field(std::vector<point> & vec){

    ifstream stream("test.txt");
    string buf;
    while(stream)
    {
        point tempPoint;
        getline(stream, buf , '\n');
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
        vec.push_back(tempPoint);
    }
    stream.close();

    vec.pop_back();

/*
	point A;

	A.first = 10;
	A.second = 10;
	vec.push_back(A);


	A.first = 11;
	A.second = 11;
	vec.push_back(A);


	A.first = 9;
	A.second = 9;
	vec.push_back(A);


	A.first = 10.5;
	A.second = 11.5;
	vec.push_back(A);


	A.first = 10;
	A.second = 10.5;
	vec.push_back(A);


	A.first = 9;
	A.second = 10.5;
	vec.push_back(A);




	A.first = -10;
	A.second = -10;
	vec.push_back(A);


	A.first = -9;
	A.second = -9;
	vec.push_back(A);

	A.first = -11;
	A.second = -11;
	vec.push_back(A);

	A.first = 2;
	A.second = -6;
	vec.push_back(A);

	A.first = -10;
	A.second = -11;
	vec.push_back(A);


	A.first = -11;
	A.second = -10;
	vec.push_back(A);

	A.first = -9;
	A.second = -11;
	vec.push_back(A);

	A.first = -11;
	A.second = -9;
	vec.push_back(A);
*/
}


int main(int argc, char const *argv[])
{

	std::vector<point> vec;

	field(vec);
/*
	cout<<endl<<"Field"<<endl;

	for (int i = 0; i < vec.size(); ++i)
	{
		cout<<vec[i].first<<" <-> "<<vec[i].second<<endl;
	}

	for (int i = 0; i < vec.size(); ++i){
		cout<< vec[i].first <<" <-> "<< vec[i].second<<endl;
	}

*/

	quadTree B;
	B.insertField(vec);
/*
	B.print();

	cout<<endl<<B.findElement(2,-6)<<endl;
*/

	point A;
	point C;

	A.first = -111001;
	A.second = -111111;

	C.first = 0;
	C.second = 0;

	B.rangeElements(A,C);
	return 0;
}
