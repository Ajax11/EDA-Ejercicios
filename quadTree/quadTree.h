//#ifdef QUADTREE_H
//#define QUADTREE_H

#include <utility>      // std::pair
#include <vector>
#include <iostream>
#include <math.h>       /* pow */  /* sqrt */
/*
  leafs
	0 -> NW Zone
	1 -> NE Zone
	2 -> SE Zone
	3 -> SW Zone
*/

#define NW 0
#define NE 1
#define SE 2
#define SW 3
using namespace std;

typedef std::pair<double,double> point;
typedef std::vector<point> vectorNode;

struct node{

	#define MAXLEAF 4

	node(){
		x = 0;
		y = 0;
		partOfSpace = 0;
		for (int i = 0; i < MAXLEAF; ++i){
			leaf[i] = 0;
		}
	}

	node(double xP, double yP){
		x = xP;
		y = yP;
		partOfSpace = 0;
		for (int i = 0; i < MAXLEAF; ++i){
			leaf[i] = 0;
		}
	}
	node(const node & tempNode){
		x = tempNode.x;
		y = tempNode.y;
		partOfSpace = tempNode.partOfSpace;
		for (int i = 0; i < MAXLEAF; ++i){
			leaf[i] = tempNode.leaf[i];
		}
	}
	virtual ~node(){}

	double x,y;
	bool partOfSpace;
	node* leaf[MAXLEAF];
};

struct quadTree{

	quadTree(){
		ptrRoot = 0;
	}
	~quadTree(){}
	
	node* ptrRoot;

	void insertField(vectorNode dataSpace){
		if (dataSpace.size() == 1){
			ptrRoot = new node(dataSpace[0].first, dataSpace[1].second);
			ptrRoot->partOfSpace = 1;
		}else{
			insertField(dataSpace, ptrRoot);
			return;
		}
	}

	void insertField(vectorNode dataSpace, node* & ptr){
		double farLow, farHigh;
		double pointM[2];
			farLow = farHigh = dataSpace[0].first;
			for (int i = 0; i < dataSpace.size(); ++i){
				if (dataSpace[i].first <= farLow){
					farLow = dataSpace[i].first;
				}
				if (dataSpace[i].first >= farHigh){
					farHigh = dataSpace[i].first;
				}
			}
			//cout<<"farLow-> "<<farLow<<" farHigh-> "<<farHigh<<endl;
			pointM[0] = ( farLow + ( ( farHigh - farLow ) / 2.0 ) );
			farLow = farHigh = dataSpace[0].second;
			for (int i = 0; i < dataSpace.size(); ++i){
				if (dataSpace[i].second <= farLow){
					farLow = dataSpace[i].second;
				}
				if (dataSpace[i].second >= farHigh){
					farHigh = dataSpace[i].second;
				}
			}
			//cout<<"farLow-> "<<farLow<<" farHigh-> "<<farHigh<<endl;
			pointM[1] = ( farLow + ( ( farHigh - farLow ) / 2.0 ) );
			//cout<<"Mpoint -> "<<pointM[0]<<" <-> "<<pointM[1]<<endl;

		std::vector< vectorNode > vec;
		vec.resize(4);
		if (!ptr){
			ptr = new node(pointM[0], pointM[1]);
		}
		for (int i = 0; i < dataSpace.size(); ++i){
			if (pointM[0] == dataSpace[i].first && pointM[1] == dataSpace[i].second){
				ptr->x = dataSpace[i].first;
				ptr->y = dataSpace[i].second;
				ptr->partOfSpace = 1;
				continue;
			}
			if (pointM[0] > dataSpace[i].first){
				if (pointM[1] < dataSpace[i].second){
					vec[NW].push_back(dataSpace[i]);
				}else{
					vec[SW].push_back(dataSpace[i]);
				}
			}else{
				if (pointM[1] < dataSpace[i].second){
					vec[NE].push_back(dataSpace[i]);
				}else{
					vec[SE].push_back(dataSpace[i]);
				}
			}
		}
/*
		for (int j = 0; j < vec.size(); ++j){
		
			cout<<"In "<<j<<" size: "<<vec[j].size()<<endl;

			for (int i = 0; i < vec[j].size(); ++i){
				cout<< vec[j][i].first <<" <-> "<< vec[j][i].second<<endl;
			}
		}
		cout<< "Root -> "<<ptr->x<<" <-> "<<ptr->y<<endl;
*/
		for (int i = 0; i < vec.size(); ++i){
			if (!vec[i].empty()){
				if (vec[i].size() == 1){
					ptr->leaf[i] = new node(vec[i][0].first, vec[i][0].second);
					ptr->leaf[i]->partOfSpace = 1;
				}else{
//					cout<<"In "<<i<<" size: "<<vec[i].size()<<" making recursion"<<endl;
					insertField(vec[i], (ptr->leaf[i]));
				}
			}
		}

	return;
	}

	void print(){
		inOrder(ptrRoot);
	}

	void inOrder(node* ptr){
		if (!ptr){
			cout<<"Sin elementos"<<endl<<endl;
			return;
		}

		cout<<"Root -> "<<ptr->x<<" <-> "<<ptr->y<<" in tree "<<ptr->partOfSpace<<endl;

		inOrder(ptr->leaf[0]);
		inOrder(ptr->leaf[1]);
		inOrder(ptr->leaf[2]);
		inOrder(ptr->leaf[3]);

	}

	bool findElement(double posX, double posY){
		
		cout<<endl<<endl<< "Buscando el punto: "<<posX<<" <-> "<<posY<<endl;

		node* ptr;
		ptr = ptrRoot;
		if (!ptr){
//			cout<<"No hay arbol. Nodo Nulo"<<endl;
			return 0;
		}
		bool valueOfFind;
		valueOfFind = 0;

		cout<<endl<<"Empezando, valores "<<!ptr<<" <-> "<< !valueOfFind <<endl;

		while( ptr && !valueOfFind ){
			valueOfFind = ( (ptr->x == posX) && (ptr->y == posY) );
			cout<<"Root -> "<<ptr->x<<" <-> "<<ptr->y<<endl;
			cout<<"Point -> " <<posX<<" <-> "<<posY<<endl; 

			if (valueOfFind)
				continue;
			if (ptr->x > posX){
				if (ptr->y < posY){
					cout<<"NextPoint in sector "<<NW<<endl;
					ptr = ptr->leaf[NW];
				}else{
					cout<<"NextPoint in sector "<<SW<<endl;
					ptr = ptr->leaf[SW];
				}
			}else{
				if (ptr->y < posY){
					cout<<"NextPoint in sector "<<NE<<endl;
					ptr = ptr->leaf[NE];
				}else{
					cout<<"NextPoint in sector "<<SE<<endl;
					ptr = ptr->leaf[SE];
				}
			}
		}
		return valueOfFind && ptr->partOfSpace;
	}

	std::vector<node*> rangeElements(point pointLow, point pointHigh){

		cout<<endl<<endl<<" Init the range query "<<endl;

		std::vector<node*> vecNodes;
		double distance;
		if (!ptrRoot){
			return vecNodes;
		}
		node* ptr;
		ptr = ptrRoot;

		//Seteo correcto de variables
		double m1;
		double m2;

		m1 = (pointHigh.first - pointLow.first); 
		m2 = (pointHigh.second - pointLow.second);
//		cout<<m1<<" <-> "<<m2<<endl<<endl;
//transform to a positive pendiente
		if ( m1*m2 < 0 ){
			cout<<"change to a positive pendiente"<<endl;
			m2 = pointHigh.second;
			pointHigh.second = pointLow.second;
			pointLow.second = m2;
		}

		m1 = (pointHigh.first - pointLow.first); 
		m2 = (pointHigh.second - pointLow.second);
//		cout<<m1<<" <-> "<<m2<<endl<<endl;

//TRansform the val of the plots
		if( ( m1 < 0 ) && ( m2 < 0 ) ){
			cout<<endl<<"change opposites plots "<<endl;

			m1 = pointLow.first;
			m2 = pointLow.second;

			pointLow.first = pointHigh.first;
			pointLow.second = pointHigh.second;

			pointHigh.first = m1;
			pointHigh.second = m2;
		}

		if ( ptr->partOfSpace ){
			//Las cuatro cotas implican que el punto esta dentro del cuadrado
			if ( ( pointLow.first <= ptr->x ) && ( pointLow.second <= ptr->y ) && ( pointHigh.first >= ptr->x ) && ( pointHigh.second >= ptr->y ) ){
				vecNodes.push_back(ptr);
			}
		}

		for (int i = 0; i < MAXLEAF; ++i){
			if (ptr->leaf[i]){
//				cout<<"Leaf -> "<< i << " Point: " <<ptr->leaf[i]->x<<" <-> "<<ptr->leaf[i]->y<<" Part of Space -> "<<ptr->leaf[i]->partOfSpace<<endl;
				range(ptr->leaf[i], vecNodes, pointHigh, pointLow);
			}
		}

		cout<<endl<<endl<<"vec size "<<vecNodes.size()<<endl<<endl;

		for (int i = 0; i < vecNodes.size(); ++i){
			cout<< "Point: " <<vecNodes[i]->x<<" <-> "<<vecNodes[i]->y<<" Part of Space -> "<<vecNodes[i]->partOfSpace<<endl;
		}
		cout<<endl<<endl;
		return vecNodes;
	}
	void range(node* & ptr, std::vector<node*> & vecNodes, point pointHigh, point pointLow){
//		cout<<"vectorNodes size "<<vecNodes.size()<<endl<<endl;
		if (!ptr)
			return;
		if ( ptr->partOfSpace ){
			if ( ( pointLow.first <= ptr->x ) && ( pointLow.second <= ptr->y ) && ( pointHigh.first >= ptr->x ) && ( pointHigh.second >= ptr->y ) ){
				//cout<< "Point: " <<ptr->x<<" <-> "<<ptr->y<<" Part of Space -> "<<ptr->partOfSpace<<endl;
				vecNodes.push_back(ptr);
			}
		}

		for (int i = 0; i < MAXLEAF; ++i){
			if (ptr->leaf[i]){
				range(ptr->leaf[i], vecNodes, pointHigh, pointLow);
			}
		}
	}
};


//#endif //QUADTREE_H

