#include <iostream>		/* cout - cin */
#include <vector>		/* structure - vector */
#include <stdlib.h>     /* abs */
#include <utility>      /* std::pair */

using namespace std;

void makeWord(string word, std::vector< std::vector<char> > keyboard){
	int distanceWay;
	distanceWay = 0;

	pair<int,int> initPos;
	initPos.first = 0;
	initPos.second = 0;

	for (int w = 0; w < word.length(); ++w){
		std::vector< pair<int,int> > possibleKeys;
		//find the position of the keys

		pair<int,int> position;
					
		for (int i = 0; i < keyboard.size(); ++i){
			for (int j = 0; j < keyboard[i].size(); ++j){
				if (word[w] == keyboard[i][j]){
					cout<<"require letter "<<word[w]<<" finded key "<<keyboard[i][j]<<" in position "<<i<<" - "<<j<<endl;
					position.first = i;
					position.second = j;
					possibleKeys.push_back(position);
				}
			}
		}

		//find the near key
			// la variable position indicara la tecla más cercana
		position.first = possibleKeys[0].first;
		position.second = possibleKeys[0].second;

		int distance;
		distance = abs(initPos.first - position.first) + abs(initPos.second - position.second);

		for (int i = 1; i < possibleKeys.size(); ++i){
			int dist;

			dist = abs(initPos.first - possibleKeys[i].first) + abs(initPos.second - possibleKeys[i].second);

			if ( dist < distance ){
				position.first = possibleKeys[i].first;
				position.second = possibleKeys[i].second;
				distance = dist;
			}
		}

		cout<< "To find "<<word[w]<<" require: "<<abs(initPos.first - position.first)<<" x-moves & "<<abs(initPos.second - position.second)<<" y-moves - Enter key -"<<endl;
		distanceWay += (distance + 1);

		initPos.first = position.first;
		initPos.second = position.second;

		cout<< "total distance "<<distanceWay<<endl;
	}

	return;
}


int main(int argc, char const *argv[]){
	
	std::vector< std::vector<char> > keyboard;

	keyboard.resize(3);

	for (int i = 0; i < keyboard.size(); ++i){
		keyboard[i].resize(5);
	}

	keyboard[0][0] = 'q';
	keyboard[0][1] = 'f';
	keyboard[0][2] = 'f';
	keyboard[0][3] = 'f';
	keyboard[0][4] = 'f';

	keyboard[1][0] = 'f';
	keyboard[1][1] = 'f';
	keyboard[1][2] = 'f';
	keyboard[1][3] = 'f';
	keyboard[1][4] = 'f';


	keyboard[2][0] = 'f';
	keyboard[2][1] = 'f';
	keyboard[2][2] = 'f';
	keyboard[2][3] = 'f';
	keyboard[2][4] = 'f';

	keyboard[2][0] = 'f';
	keyboard[2][1] = 'f';
	keyboard[2][2] = 'f';
	keyboard[2][3] = 'f';
	keyboard[2][4] = 'f';

	keyboard[2][0] = 'f';
	keyboard[2][1] = 'f';
	keyboard[2][2] = 'a';
	keyboard[2][3] = 'a';
	keyboard[2][4] = '*';

	for (int i = 0; i < keyboard.size(); ++i){
		for (int j = 0; j < keyboard[i].size(); ++j){
			cout<<keyboard[i][j]<<'\t';
		}

		cout<<endl;
	}

	makeWord("qaq", keyboard);

	return 0;
}