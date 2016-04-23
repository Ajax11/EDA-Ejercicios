//#include "Node.h"
#include "Tree.h"

using namespace std;

//hash ordenado de forma ascendente

int main()
{
    Tree THash(10);
/*
    for (int i = 0; i < 50 ; ++i)
    {
//    	cout<<endl<<"llamando funcion de insercion"<<endl;
    	THash.insertData(i);
    	//cout<<endl<<"insertando: "<<i<<'\t'<<"resultado: "<<THash.insertData(i)<<endl;
//    	cout<<endl<<"finalizando funcion de insercion"<<endl;
    }

*/

    for(int i = 55; i > 0; i-=1){
    	cout<<endl<<"insertando: "<<i<<'\t'<<"resultado: "<<THash.insertData(i)<<endl;
    }


    THash.print();

    for (int i = -20; i <= 0 ; ++i)
    {
    	cout<<endl<<"insertando: "<<i<<'\t'<<"resultado: "<<THash.insertData(i)<<endl;
    }

    THash.print();

/*
    for (int i = 0; i < 20 ; ++i)
    {
    	cout<<endl<<"llamando funcion de eliminacion"<<endl;
    	THash.deleteData(i);
		//cout<<endl<<"eliminando: "<<i<<'\t'<<"resultado: "<<THash.deleteData(i)<<endl;
    	cout<<endl<<"finalizando funcion de eliminacion"<<endl;
    }

*/
    for (int i = -10; i < 10; ++i)
    {
    	cout<<endl<<"eliminando: "<<i<<'\t'<<"resultado: "<<THash.deleteData(i)<<endl;
    }


    THash.print();

    for (int i = 20; i < 10; i-=1)
    {
    	cout<<endl<<"eliminando: "<<i<<'\t'<<"resultado: "<<THash.deleteData(i)<<endl;
    }

    THash.print();

    return 0;
}
