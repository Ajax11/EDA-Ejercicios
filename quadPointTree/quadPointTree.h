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
		for (int i = 0; i < MAXLEAF; ++i){
			leaf[i] = 0;
		}
	}

	node(double xP, double yP){
		x = xP;
		y = yP;
		for (int i = 0; i < MAXLEAF; ++i){
			leaf[i] = 0;
		}
	}
	node(const node & tempNode){
		x = tempNode.x;
		y = tempNode.y;
		for (int i = 0; i < MAXLEAF; ++i){
			leaf[i] = tempNode.leaf[i];
		}
	}
	virtual ~node(){}

	double x,y;
	node* leaf[MAXLEAF];
};

struct quadPointTree{

	quadPointTree(){
		ptrRoot = 0;
	}
	~quadPointTree(){}
	
	node* ptrRoot;

	bool insert(point element){
		if (!ptrRoot){
			ptrRoot = new node(element.first, element.second);
			return 1;
		}

		node** ptr;
		ptr = &ptrRoot;

		while((*ptr)){
			if ( ((*ptr)->x) > element.first){
				if ( ((*ptr)->y) < element.second){
					ptr = &( (*ptr)->leaf[NW] );
				}else{
					ptr = &( (*ptr)->leaf[SW] );
				}
			}else{
				if ( ((*ptr)->y) < element.second){
					ptr = &( (*ptr)->leaf[NE] );
				}else{
					ptr = &( (*ptr)->leaf[SE] );
				}
			}
		}

		(*ptr) = new node(element.first, element.second);
		return 1;
	}

	void print(){
		string tag;
		order(ptrRoot, tag);
	}
	void order(node* ptr, string tag){
		if (!ptr){
//			cout<<"Sin elementos"<<endl<<endl;
			return;
		}
		string zone;
		for (int i = 0; i < MAXLEAF; ++i){
			if ( ptr->leaf[i] ){
				if (i == NW)
					zone = "NW";
				else if (i == SW)
					zone = "SW";
				else if (i == NE)
					zone = "NE";
				else if (i == SE)
					zone = "SE";
				cout<<tag<<"Root -> "<<ptr->x<<" <-> "<<ptr->y<<" in tree "<<"Moving to zone "<<zone<<" to child -> "<< ptr->leaf[i]->x<<" <-> "<<ptr->leaf[i]->y  <<endl;
				order( ptr->leaf[i], tag+"  " );
			}
		}
/*
		order(ptr->leaf[0]);
		cout<<"Root -> "<<ptr->x<<" <-> "<<ptr->y<<" in tree "<<"Moving to cuadrante NE"<<endl;
		order(ptr->leaf[1]);
		cout<<"Root -> "<<ptr->x<<" <-> "<<ptr->y<<" in tree "<<"Moving to cuadrante SE"<<endl;
		order(ptr->leaf[2]);
		cout<<"Root -> "<<ptr->x<<" <-> "<<ptr->y<<" in tree "<<"Moving to cuadrante SW"<<endl;
		order(ptr->leaf[3]);
*/
	}

	bool findElement(double posX, double posY){
		
		cout<<endl<<endl<< "Buscando el punto: "<<posX<<" <-> "<<posY<<endl;

		node* ptr;
		ptr = ptrRoot;
		if (!ptr){
			cout<<"No hay arbol. Nodo Nulo"<<endl;
			return 0;
		}
		bool valueOfFind;
		valueOfFind = 0;

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
		return valueOfFind;
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

//Transform the val of the plots
		if( ( m1 < 0 ) && ( m2 < 0 ) ){
			cout<<endl<<"change opposites plots "<<endl;

			m1 = pointLow.first;
			m2 = pointLow.second;

			pointLow.first = pointHigh.first;
			pointLow.second = pointHigh.second;

			pointHigh.first = m1;
			pointHigh.second = m2;
		}

		cout<<endl<<endl<<" The range query is from "<<pointLow.first<<" <-> "<<pointLow.second<< " to "<<pointHigh.first<<" <-> "<<pointHigh.second<<endl;

		//Las cuatro cotas implican que el punto esta dentro del cuadrado
		if ( ( pointLow.first <= ptr->x ) && ( pointLow.second <= ptr->y ) && ( pointHigh.first >= ptr->x ) && ( pointHigh.second >= ptr->y ) ){
			vecNodes.push_back(ptr);
		}

		for (int i = 0; i < MAXLEAF; ++i){
			// Llamar recursivamente a las hojas existentes
			if (ptr->leaf[i]){
				range(ptr->leaf[i], vecNodes, pointHigh, pointLow);
			}
		}

		cout<<endl<<endl<<"vec size "<<vecNodes.size()<<endl<<endl;

		for (int i = 0; i < vecNodes.size(); ++i){
			cout<< "Point: " <<vecNodes[i]->x<<" <-> "<<vecNodes[i]->y<<endl;
		}
		cout<<endl<<endl;
		return vecNodes;
	}
	void range(node* & ptr, std::vector<node*> & vecNodes, point pointHigh, point pointLow){
		if (!ptr)
			return;

		if ( ( pointLow.first <= ptr->x ) && ( pointLow.second <= ptr->y ) && ( pointHigh.first >= ptr->x ) && ( pointHigh.second >= ptr->y ) ){
			//cout<< "Point: " <<ptr->x<<" <-> "<<ptr->y<<" Part of Space -> "<<ptr->partOfSpace<<endl;
			vecNodes.push_back(ptr);
		}

		for (int i = 0; i < MAXLEAF; ++i){
			if (ptr->leaf[i]){
				range(ptr->leaf[i], vecNodes, pointHigh, pointLow);
			}
		}
	}
};

/*

Investigar como funciona el R - Tree
	construccion
	split
		casos en los q se hace el split
	coḿo funciona el bounding box
		MBR - minimo rectangulo

	MBB
	MBR

Avisar q tengo 2 puntos mas

*/
