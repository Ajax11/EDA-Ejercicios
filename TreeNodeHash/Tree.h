#ifndef TREE_H
#define TREE_H

#include "Node.h"

#define defaultLeaf 1

struct Tree
{
    Tree() {
        root = 0;
        sizeHash = 10;
    }

    Tree(int sizeH) {
        root = 0;
        sizeHash = sizeH;
    }
/*
        Tree(const Tree & treeHash){
            root = treeHash.root;
            sizeHash = treeHash.sizeHash;
        }
*/
    virtual ~Tree() {
        if( root ){
            Node** t;
            t = &root;
            deleteTree(t);
            root = 0;   
        }
    }

    void deleteTree(Node** t){
        if(!(*t))
            return;
        deleteTree( &( (*t) -> leaf[0] )  );
        deleteTree( &( (*t) -> leaf[1] )  );
        delete *t;
    }

    Node* root;
    int sizeHash;

    //fuincion de impresion de datos

    bool findRange(Node** pointerNode, int element){
        if( ((*pointerNode)->Hash[0] <= element) && (*((*pointerNode)->end) >= element) )
            return 1;
        return 0;
    }

    bool findData(int element, Node** & temp){
        temp = &root;
        bool val = 0;
        while( (*temp) && ((*temp) -> numHash == sizeHash) && !val ){
            val = findRange(temp, element);
            if ( !val && ((*temp) -> Hash[0] > element) ){
                temp = &((*temp) -> leaf[0]);
            }
            else{
                if ( !val && ((*temp) -> Hash[0] < element) )
                    temp = &((*temp) -> leaf[1]);
            }
        }
        return val;
    }

    bool insertData(int element){
        Node** ptrNode;
        findData(element, ptrNode);
       if(!(*ptrNode)){
            *ptrNode = new Node(sizeHash);
            (*ptrNode) -> insertElement(element);
            return 1;
        }
        if((*ptrNode) -> search(element))
            return 0;
        if( (*ptrNode)->numHash == sizeHash){
            int tmp = element;
            element = (*ptrNode)->Hash[sizeHash-1];
            (*ptrNode)->deleteElement(element);
            (*ptrNode)->insertElement(tmp);
            ptrNode = &( (*ptrNode) -> leaf[1] );
            (*ptrNode) = new Node(sizeHash);
        }
        (*ptrNode) -> insertElement(element);
        return 1; 
    }

    bool deleteData(int element){
        Node** ptrNode;
        ptrNode = &root;
        bool val = 0;
        while( (*ptrNode) && !val ){

            val = findRange(ptrNode, element);
            if ( !val && ((*ptrNode) -> Hash[0] > element) )
                ptrNode = &((*ptrNode) -> leaf[0]);
            if ( !val && ((*ptrNode) -> Hash[0] < element) )
                ptrNode = &((*ptrNode) -> leaf[1]);
        }

        if( (*ptrNode) && val)
            return (*ptrNode)->deleteElement(element);
        return 0;
    }

    void print(){
        Node** p;
        p = &root;
        inOrder(p);
    }

    void inOrder(Node** t){
        if( ! (*t) )
            return;

//        cout<<endl<<"hojaI"<<endl;
        inOrder( &( (*t) -> leaf[0] ) );

//        cout<<endl<<"Raiz"<<endl;
        (*t) -> print();

//        cout<<endl<<"hojaD"<<endl;
        inOrder(  & ( (*t) -> leaf[1] ) );
    }

    void preOrder(Node** t){
        if( ! (*t) )
            return;

//        cout<<endl<<"Raiz"<<endl;
        (*t) -> print();

//        cout<<endl<<"hojaI"<<endl;
        inOrder( &( (*t) -> leaf[0] ) );

//        cout<<endl<<"hojaD"<<endl;
        inOrder(  & ( (*t) -> leaf[1] ) );
    }
};

#endif // TREE_H


