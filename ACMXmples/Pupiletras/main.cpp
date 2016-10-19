//#include "quadPointTree.h"
#include <utility>      // std::pair
#include <vector>

#include <iostream>
#include <fstream>
#include <string>

#include <stdio.h>

using namespace std;
typedef pair<int,int> point;

void fillPupiletras(std::vector<string> & table){
    ifstream stream("test.txt");
    string buf;
    getline(stream, buf , '\n');
    while(stream)
    {
    	table.push_back(buf);
        getline(stream, buf , '\n');
    }
    stream.close();
}

bool findRestPupiWord(std::vector<string> & pupiLetra, string word, std::vector<point> & vecPosition){
	bool findWord;
	findWord = 0;
	bool val;
	std::vector<point> vec;

	int x,y;
	// x <-> i // y <-> j

	// East
	
	val = 0;
	vec.resize(0);
	x = vecPosition[0].first;
	y = vecPosition[0].second;

	for (int i = 0; !findWord && i < word.size() && !val && ( y <= pupiLetra[0].size() ); ++i){
		val = 1;
		// cout<<pupiLetra[x][y]<<" -> "<<endl;
		if (word[i] == pupiLetra[x][y]){
			point a;
			a.first = x;
			a.second = y;

			vec.push_back(a);
			val = 0;
		}
		y +=1;
	}

	if ( vec.size() == word.size() ){
		for (int i = 0; i < word.size() && !findWord; ++i){
			findWord=1;
			if ( pupiLetra[vec[i].first][vec[i].second] == word[i] ){
				findWord=0;
			}
		}
		if (!findWord){
			vecPosition = vec;
			return !findWord;
		}
		findWord = 0;
	}


	// SouthEast
	
	val = 0;
	vec.resize(0);
	x = vecPosition[0].first;
	y = vecPosition[0].second;

	for (int i = 0; !findWord && i < word.size() && !val && ( x < pupiLetra.size() && y <= pupiLetra[0].size() ); ++i){
		val = 1;
		// cout<<pupiLetra[x][y]<<" -> "<<endl;
		if (word[i] == pupiLetra[x][y]){
			point a;
			a.first = x;
			a.second = y;
			vec.push_back(a);
			val = 0;
		}
		y += 1;
		x += 1;
	}

	if ( vec.size() == word.size() ){
		for (int i = 0; i < word.size() && !findWord; ++i){
			findWord=1;
			if ( pupiLetra[vec[i].first][vec[i].second] == word[i] ){
				findWord=0;
			}
		}
		if (!findWord){
			vecPosition = vec;
			return !findWord;
		}
		findWord = 0;
	}

	// South
	
	val = 0;
	vec.resize(0);
	x = vecPosition[0].first;
	y = vecPosition[0].second;

	for (int i = 0; !findWord && i < word.size() && !val && ( x < pupiLetra.size() ); ++i){
		val = 1;
		// cout<<pupiLetra[x][y]<<" -> "<<endl;
		if (word[i] == pupiLetra[x][y]){
			point a;
			a.first = x;
			a.second = y;
			vec.push_back(a);
			val = 0;
		}
		x += 1;
	}

	if ( vec.size() == word.size() ){
		for (int i = 0; i < word.size() && !findWord; ++i){
			findWord=1;
			if ( pupiLetra[vec[i].first][vec[i].second] == word[i] ){
				findWord=0;
			}
		}
		if (!findWord){
			vecPosition = vec;
			return !findWord;
		}
		findWord = 0;
	}


	// SouthWest
	
	val = 0;
	vec.resize(0);
	x = vecPosition[0].first;
	y = vecPosition[0].second;

	for (int i = 0; !findWord && i < word.size() && !val && ( y>=0 && x < pupiLetra.size() ); ++i){
		val = 1;

		// cout<<pupiLetra[x][y]<<" -> "<<endl;
		if (word[i] == pupiLetra[x][y]){
			point a;
			a.first = x;
			a.second = y;
			vec.push_back(a);
			val = 0;
		}
		x += 1;
		y -= 1;
	}

	if ( vec.size() == word.size() ){
		for (int i = 0; i < word.size() && !findWord; ++i){
			findWord=1;
			if ( pupiLetra[vec[i].first][vec[i].second] == word[i] ){
				findWord=0;
			}
		}
		if (!findWord){
			vecPosition = vec;
			return !findWord;
		}
		findWord = 0;
	}

	// West
	
	val = 0;
	vec.resize(0);
	x = vecPosition[0].first;
	y = vecPosition[0].second;

	for (int i = 0; !findWord && i < word.size() && !val && ( y>=0 ); ++i){
		val = 1;
		// cout<<pupiLetra[x][y]<<" -> "<<endl;
		if (word[i] == pupiLetra[x][y]){
			point a;
			a.first = x;
			a.second = y;
			vec.push_back(a);
			val = 0;
		}
		y -= 1;
	}

	if ( vec.size() == word.size() ){
		for (int i = 0; i < word.size() && !findWord; ++i){
			findWord=1;
			if ( pupiLetra[vec[i].first][vec[i].second] == word[i] ){
				findWord=0;
			}
		}
		if (!findWord){
			vecPosition = vec;
			return !findWord;
		}
		findWord = 0;
	}

	// NorthWest
	
	val = 0;
	vec.resize(0);
	x = vecPosition[0].first;
	y = vecPosition[0].second;

	for (int i = 0; !findWord && i < word.size() && !val && ( x>=0 && y>=0 ); ++i){
		val = 1;
		// cout<<pupiLetra[x][y]<<" -> "<<endl;
		if (word[i] == pupiLetra[x][y]){
			point a;
			a.first = x;
			a.second = y;
			vec.push_back(a);
			val = 0;
		}
		x -= 1;
		y -= 1;
	}

	if ( vec.size() == word.size() ){
		for (int i = 0; i < word.size() && !findWord; ++i){
			findWord=1;
			if ( pupiLetra[vec[i].first][vec[i].second] == word[i] ){
				findWord=0;
			}
		}
		if (!findWord){
			vecPosition = vec;
			return !findWord;
		}
		findWord = 0;
	}

	// North
	
	val = 0;
	vec.resize(0);
	x = vecPosition[0].first;
	y = vecPosition[0].second;

	for (int i = 0; !findWord && i < word.size() && !val && ( x>=0 ); ++i){
		val = 1;
		// cout<<pupiLetra[x][y]<<" -> "<<endl;
		if (word[i] == pupiLetra[x][y]){
			point a;
			a.first = x;
			a.second = y;
			vec.push_back(a);
			val = 0;
		}
		x -= 1;
	}

	if ( vec.size() == word.size() ){
		for (int i = 0; i < word.size() && !findWord; ++i){
			findWord=1;
			if ( pupiLetra[vec[i].first][vec[i].second] == word[i] ){
				findWord=0;
			}
		}
		if (!findWord){
			vecPosition = vec;
			return !findWord;
		}
		findWord = 0;
	}

	// NorthEast
	
	val = 0;
	vec.resize(0);
	x = vecPosition[0].first;
	y = vecPosition[0].second;

	for (int i = 0; !findWord && i < word.size() && !val && ( x>=0 && y < pupiLetra[0].size() ); ++i){
		val = 1;
		// cout<<pupiLetra[x][y]<<" -> "<<endl;
		if (word[i] == pupiLetra[x][y]){
			point a;
			a.first = x;
			a.second = y;
			vec.push_back(a);
			val = 0;
		}
		x -= 1;
		y += 1;
	}

	if ( vec.size() == word.size() ){
		for (int i = 0; i < word.size() && !findWord; ++i){
			findWord=1;
			if ( pupiLetra[vec[i].first][vec[i].second] == word[i] ){
				findWord=0;
			}
		}
		if (!findWord){
			vecPosition = vec;
			return !findWord;
		}
		findWord = 0;
	}

	return 0;
}

bool findWordPupi(std::vector<string> & pupiLetra, string word){
	bool findWord;
	findWord = 0;
	std::vector<point> vec;
	
	for (int i = 0; i < pupiLetra.size() && !findWord; ++i){
		for (int j = 0; j < pupiLetra[i].size() && !findWord; ++j){
			if (pupiLetra[i][j] == word[0]){
				point a;
				a.first = i;
				a.second = j;
				vec.push_back(a);
				bool val;
				val = findRestPupiWord(pupiLetra, word, vec);
				if (val){
					findWord = 1;
				}else{
					findWord = 0;
					vec.resize(0);
				}
			}
		}
	}

	if (findWord){
		for (int i = 0; i < vec.size(); ++i){
			cout<< word[i] << " -> " << vec[i].first << " <-> "<< vec[i].second<<endl;
		}
	}else
		cout<<"Palabra no encontrada"<<endl;

	return findWord;
}

int main(int argc, char const *argv[])
{
	std::vector< vector<point> > vecPosition;

	std::vector<string> vec;

	fillPupiletras(vec);

	cout<<endl<<"Pupiletras:"<<endl<<endl<<endl;

	for (int i = 0; i < vec.size(); ++i){
		cout<<vec[i]<<endl;
	}

	cout<<endl<<endl;

	string pupiWord;
	cin>>pupiWord;

	cout<<endl<<"Palabra para buscar: "<<pupiWord<<endl<<endl;

	findWordPupi(vec, pupiWord);


	return 0;
}
