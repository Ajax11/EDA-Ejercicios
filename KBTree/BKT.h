#include <iostream>
#include <string>
#include <vector>
#include <utility>  /* std::pair */

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

//funcion de distancia compara cuantos caracteres diferentes hay en la palabra incial word y la palabra a compara wordDiff
int getDifference(string word, string wordDiff){
	int diff;
	diff = 0;
	diff = 	abs(word.length() - wordDiff.length());
	int count;
	count = ( word.length() <= wordDiff.length() )?word.length():wordDiff.length();
	for (int i = 0; i < count; ++i)
	{
		if (word[i] != wordDiff[i]){
			++diff;
		}
	}
	return diff;
}

struct node{
	node(){
		distance = 0;
	}
	node(string word){
		wordContent.push_back(word);
		distance = 0;
	}
	node(string word, int dist){
		wordContent.resize(1, word);
		distance = dist;
	}
	node(std::vector<string> words){
		for (int i = 0; i < words.size(); ++i){
			wordContent.push_back(words[i]);
		}
		distance = 0;
	}
	node(const node & nodeA){
		distance = nodeA.distance;
		for (int i = 0; i < nodeA.wordContent.size(); ++i)
		{
			wordContent.push_back(nodeA.wordContent[i]);
		}
		for (int i = 0; i < nodeA.leaf.size(); ++i)
		{
			leaf.push_back(nodeA.leaf[i]);
		}
	}
	virtual ~node(){
		for (int i = 0; i < leaf.size(); ++i)
		{
			delete leaf[i];
		}
	}

	void print(){
		for (int i = 0; i < wordContent.size(); ++i){
			cout<<endl<<"palabra: "<<'\t'<<wordContent[i]<<" distancia: "<<'\t'<<distance<<endl;
		}
	}

	void addWord(string word){
		wordContent.push_back(word);
	}

	std::vector<string> wordContent;
	int distance;

	std::vector<node*> leaf;
};

struct BKT{
	BKT(){
		root = 0;
	}
	BKT(string word){
		root = new node(word);
	}

	BKT(std::vector<string> & vectorWord){
		std::vector< pair<std::string, int> > cadWords;
		node* temp;
		temp = 0;
		
		srand (time(NULL));
		int dist, positionWord;
		dist = 0;

		positionWord = rand() % vectorWord.size();
		pair<std::string, int> point;

		root = new node(vectorWord[positionWord]);
		for (int i = ((positionWord + 1)%vectorWord.size()); i != positionWord; i = ((i+1) % vectorWord.size()) ){
			dist = getDifference(vectorWord[positionWord], vectorWord[i]);
			point.first = vectorWord[i];
			point.second = dist;
			
			int tempD;
			string tempW;
			tempD = 0;
			tempW = "";

			for (int j = 0; j < cadWords.size(); ++j){
				if (cadWords[j].second > point.second){
					tempW = point.first;
					tempD = point.second;

					point.first = cadWords[j].first;
					point.second = cadWords[j].second;

					cadWords[j].first = tempW;
					cadWords[j].second = tempD;
				}
			}
			cadWords.push_back(point);
		}
/*
		cout<<"palabra nodo: "<<'\t'<<vectorWord[positionWord]<<endl;
		for (int i = 0; i < cadWords.size(); ++i){
			cout<<endl<<"palabra: "<<'\t'<<cadWords[i].first<<'\t'<<"distancia: "<<'\t'<<cadWords[i].second<<endl;
		}

		cout<<endl<<"direccion root "<<'\t'<<root<<endl;
		cout<<endl<<"direccion nodoTemporal "<<'\t'<<temp<<endl;
*/
		node* refRoot;
		refRoot = root;

		bool flag;
		flag = 0;
		for (int i = 0; i < cadWords.size(); ++i){
			flag = 0;
			if(!refRoot->leaf.empty()){
				for (int j = 0; j < refRoot->leaf.size() && !flag; ++j){
					if(refRoot->leaf[j]->distance == cadWords[i].second){
						refRoot->leaf[j]->addWord(cadWords[i].first);
						flag = 1;
					}
				}
			}

			if (flag)
				continue;

//		cout<<endl<<"direccion nodoTemporal "<<'\t'<<temp<<endl;
			temp = new node(cadWords[i].first,cadWords[i].second);
//		cout<<endl<<"direccion nodoTemporal "<<'\t'<<temp<<endl;
			refRoot->leaf.push_back(temp);
		}
/*
		for (int i = 0; i < refRoot->leaf.size(); ++i)
		{
			cout<<endl<<"nodo "<<i<<endl;
			refRoot->leaf[i]->print();
		}
*/
		for (int i = 0; i < refRoot->leaf.size(); ++i)
		{
/*
			cout<<endl<<"nodo "<<i<<endl;
			refRoot->leaf[i]->print();
*/
			resizeNode( refRoot->leaf[i] );
		}
	}

	~BKT(){

	}

	void resizeNode(node* tempNode){
		if (!tempNode)
			return;
		if (tempNode && tempNode->wordContent.size() == 1)
			return;

		std::vector< pair<std::string, int> > cadWords;
		node* temp;
		int dist, positionWord;
		dist = 0;
		temp = 0;

		srand (time(NULL));
/*
		cout<<endl<<" -H- "<<endl;
		for (int i = 0; i < tempNode->wordContent.size(); ++i){
			cout<<endl<<" -H "<<tempNode->wordContent[i]<<" H-"<<endl;
		}
		cout<<endl<<" -H- "<<endl;
*/
		positionWord = (rand() % tempNode->wordContent.size());
		pair<std::string, int> point;

		string wordNode;
		wordNode = tempNode->wordContent[positionWord];

		for (int i = ((positionWord + 1)%tempNode->wordContent.size()); i != positionWord ; i = ((i+1) % tempNode->wordContent.size()) ){
			dist = getDifference(wordNode, tempNode->wordContent[i]);
			point.first = tempNode->wordContent[i];
			point.second = dist;

			int tempD;
			string tempW;
			tempD = 0;
			tempW = "";

			for (int j = 0; j < cadWords.size(); ++j){
				if (cadWords[j].second > point.second){	
					tempW = point.first;
					tempD = point.second;

					point.second = cadWords[j].second;
					point.first = cadWords[j].first;

					cadWords[j].first = tempW;
					cadWords[j].second = tempD;
				}
			}
			cadWords.push_back(point);
		}

/*
		cout<<endl<<endl<<wordNode<<endl<<endl;
		for (int i = 0; i < cadWords.size(); ++i){
			cout<<endl<<"palabra: "<<'\t'<<cadWords[i].first<<'\t'<<"distancia: "<<'\t'<<cadWords[i].second<<endl;
		}

		cout<<"palabra nodo: "<<'\t'<<vectorWord[positionWord]<<endl;
		cout<<endl<<"direccion root "<<'\t'<<root<<endl;
		cout<<endl<<"direccion nodoTemporal "<<'\t'<<temp<<endl;
		

*/
		node* refRoot;
		refRoot = tempNode;

		bool flag;
		flag = 0;
		for (int i = 0; i < cadWords.size(); ++i){
			flag = 0;
			if(!refRoot->leaf.empty()){
				for (int j = 0; j < refRoot->leaf.size() && !flag; ++j){
					if(refRoot->leaf[j]->distance == cadWords[i].second){
						refRoot->leaf[j]->addWord(cadWords[i].first);
						flag = 1;
					}
				}
			}

			if (flag)
				continue;
//		cout<<endl<<"direccion nodoTemporal "<<'\t'<<temp<<endl;
			temp = new node(cadWords[i].first,cadWords[i].second);
//		cout<<endl<<"direccion nodoTemporal "<<'\t'<<temp<<endl;
			refRoot->leaf.push_back(temp);
		}

		tempNode->wordContent.resize(1, wordNode);

		for (int i = 0; i < refRoot->leaf.size(); ++i)
		{
			//cout<<endl<<"nodo "<<i<<endl;
			resizeNode( refRoot->leaf[i] );
		}
	}

	node* root;

	void print(){
		findEmpty(root);
	}
	void findEmpty(node* ptrNode){
		
		for (int i = 0; i < ptrNode->wordContent.size(); ++i)
		{
			cout<<endl<<"entrando con "<<ptrNode->wordContent[i]<<endl;
		}

		if (ptrNode && ptrNode->leaf.size() == 0){
			cout<<endl<<"Sin hijos"<<endl;
			return;
		}
		cout<<"El padre es: "<<'\t'<<ptrNode->wordContent[0]<<endl;
		for (int i = 0; i < ptrNode->leaf.size(); ++i)
		{
			cout<<endl<<"la distancia del padre: "<<ptrNode->wordContent[0]<< " con el hijo: "<<ptrNode->leaf[i]->wordContent[0]<<" con una distancia de "<<ptrNode->leaf[i]->distance<<endl;
			findEmpty(ptrNode->leaf[i]);
		}
	}


};

