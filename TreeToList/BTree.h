#ifndef BTREE_H
#define BTREE_H

#include <vector>
#include <iostream>
using namespace std;

struct Node{
    Node(){
        data = 0;
        leaf[0] = 0;
        leaf[1] = 0;
    }

    Node(int tDat){
        data = tDat;
        leaf[0] = 0;
        leaf[1] = 0;
    }
    Node(const Node & A){
        data = A.data;
        leaf[0] = A.leaf[0];
        leaf[1] = A.leaf[1];
    }
    int data;
    Node* leaf[2];
};

struct BTree
{
    BTree(){
        root = 0;
    }
    //BTree(const BTree & tTree) {}

    virtual ~BTree() {

    }

    Node* root;

    bool findD(int dat, Node**& ptr){
        ptr = &root;
        bool val;
        val = 0;
        //cout<<endl<<*ptr<<" - "<<root<<endl;
        while((*ptr) && !val){
            val = ((*ptr)->data == dat)?1:0;
            if(!val){
                int flag;
                flag = ((*ptr)->data > dat)?0:1;
                ptr = &(*ptr)->leaf[flag];
            }
        }
        //cout<<endl<<*ptr<<" - "<<root<<endl;
        return val;
    }

    bool insertD(int Dat){
        Node** ptr;
        bool val;
        val = findD(Dat, ptr);
        if(val){
            return 0;
        }

        if(!root)
            root = new Node(Dat);
        else
            (*ptr) = new Node(Dat);
/*

        cout<<" "<<(*ptr)->data<<'\t';
        cout<<'\t'<<root<<endl;
*/
        return 1;
    }

    void printTree(){
        Node* ptr;
        ptr = root;
        inOrder(ptr);
        cout<<endl;

    }
    void inOrder(Node* ptr){
        if(!ptr)
            return;
        inOrder(ptr->leaf[0]);
        cout<<ptr->data<<" -> ";
        inOrder(ptr->leaf[1]);
    }

     void getElementsTree(Node* ptr, vector<int> & ptrVec){
        if(!ptr)
            return;
        getElementsTree(ptr->leaf[0], ptrVec);
        ptrVec.push_back(ptr->data);
        getElementsTree(ptr->leaf[1], ptrVec);
    }

    void deleteTree(Node* ptr){
        if(!ptr)
            return;
        deleteTree(ptr->leaf[0]);
        delete ptr;
        deleteTree(ptr->leaf[1]);
    }

    void bTreeToDLL(){
        vector <int> ptrVec;
        Node** ptr;
        ptr = &root;
        //getElementsTree((*ptr), ptrVec);
        getElementsTree(root, ptrVec);

        //Eliminar Arbol;
        deleteTree(root);

        root = new Node(ptrVec[0]);
        root->leaf[0] = 0;

        //cout<<endl<<" "<<ptrVec.size()<<"->"<<ptrVec[0]<<endl;

        Node** ptrT;
        ptrT = &(root->leaf[1]);
        Node** ptrTBefore;
        ptrTBefore = &root;
        /*

        cout<<" ->"<<root->data<<" ->"<<endl;
        cout<<" ->"<<*ptrT<<" ->"<<endl;
        cout<<" ->"<<root<<" ->"<<endl;
        */

        for(int i=1; i < ptrVec.size(); ++i){
            (*ptrT) = new Node(ptrVec[i]);
            (*ptrT)->leaf[0] = (*ptrTBefore);
            ptrTBefore = ptrT;
            ptrT = &((*ptrT)->leaf[1]);
        }
    }

    void printList(){
        Node* ptr;
        cout<<"imprimiendo Lista"<<endl;
        for(ptr = root; ptr; ptr = ptr->leaf[1]){
            //cout<<ptr->data<<'\t';
            cout<<ptr->data<<" -> ";
        }
        cout<<endl;
    }

    void changeTree(){
        if(!root)
            return;
        swapNodeTree(root);
        return;
    }

    void swapNodeTree(Node* ptr){
        if ( ptr->leaf[0] ){
            Node* ptrLeafMoved;
            for (ptrLeafMoved = ptr->leaf[1]; ptrLeafMoved; ptrLeafMoved = ptrLeafMoved->leaf[1]){}
            ptrLeafMoved = ptr->leaf[0];
            ptr->leaf[0] = 0;
        }
        if ( ptr->leaf[1] ){
            swapNodeTree(ptr->leaf[1]);
        }
        return;

    }






    
    void getArchiveDot(string archive){
        ofstream out( archive.c_str() );
        out<<makeArchiveDot();
        out.close;
    }

    string makeArchiveDot(){
        string Buffer;
        Buffer += "digraph unix {";
        Buffer += '\n';
        Buffer += "node [color=lightblue2, style=filled];";
        Buffer += '\n';

        Node** Ptr = &Root;
        string temp;
        GetNodeDot( temp, Ptr);
        Buffer += temp;
        Buffer += "}";
        return Buffer;
    }

    string getNodeDot(string & word, Node** Ptr){
        if( ! (*ptr) )
            return ;
        GetNodeDot( word, &( (*ptr)->leaf[0] ) );
            std::string tempWord="";
            if ( (*ptr)->leaf[0] ){
                std::stringstream stream;
                stream << (*ptr)->data;
                std::stringstream stream1;
                stream1 << (*ptr)->leaf[0]->data;

                tempWord += stream.c_str();
                tempWord += " -> ";
                tempWord += stream1.c_str();
                tempWord += ";";
                tempWord += '\n';
            }
            if ( (*ptr)->leaf[1] ){
                std::stringstream stream;
                stream << (*ptr)->data;
                std::stringstream stream1;
                stream1 << (*ptr)->leaf[1]->data;
                
                tempWord += stream.c_str();
                tempWord += " -> ";
                tempWord += stream1.c_str();
                tempWord += ";";
                tempWord += '\n';
            }
            word += tempWord;
        GetNodeDot( word, &(*ptr)->leaf[1] );
    }



};

#endif // BTREE_H
