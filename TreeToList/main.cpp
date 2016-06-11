
#include "BTree.h"
using namespace std;

int main()
{
    BTree A;
    for(int i=0; i<10; i++){
        A.insertD(i);
    }
    for(int i=-5; i<0; i++){
        A.insertD(i);
    }

    A.printTree();

    A.changeTree();

    A.printTree();


    //A.bTreeToDLL();
    //A.printList();
    cout << "Hello world!" << endl;
    return 0;
}
