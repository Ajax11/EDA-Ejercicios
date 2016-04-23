#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

struct Node
{

    Node() {
        sizeHash = 10;
        leaf[0] = 0;
        leaf[1] = 0;
        Hash = new int[sizeHash];
        numHash = 0;
        end = &Hash[numHash];
    }

    Node(int sizeH) {
        sizeHash = sizeH;
        leaf[0] = 0;
        leaf[1] = 0;
        Hash = new int[sizeHash];
        numHash = 0;
        end = &Hash[numHash];
    }

    Node(const Node & NodeH) {
        sizeHash = NodeH.sizeHash;
        leaf[0] = NodeH.leaf[0];
        leaf[1] = NodeH.leaf[1];
        numHash = NodeH.numHash;

        Hash = new int[sizeHash];
        for (int i = 0; i < numHash; ++i){
            Hash[i] = NodeH.Hash[i];
        }

        end = &Hash[numHash-1];
    }
    virtual ~Node() {
        delete Hash;
    }
    int* Hash;
    int sizeHash; //capacidad del hash
    int numHash; //numero de elementos
    Node* leaf[2];
    int* end;

    void print(){
        string temp;
        for (int i=0; i < numHash; ++i){
            cout<<" "<<Hash[i]<<" ";
        }
        cout<<endl;
    }

    bool search(int x){
        bool val;
        val = 0;
        for (int i = 0; i < numHash; ++i){
            val = (Hash[i] == x)?1:0;
        }
        return val;
    }

    bool insertElement(int x){
        
        if(numHash == sizeHash)
            return 0;
        for (int i = 0; i < numHash; ++i){
            if(x < Hash[i]){
                int temp;
                temp = x;
                x = Hash[i];
                Hash[i]=temp;
            }
        }
        Hash[numHash] = x;
        end = &Hash[numHash];
        ++numHash;
        return 1;
    }

    bool deleteElement(int x){
        if (numHash == 0){
            return 0;
        }
        bool flag;
        flag = 0;
        int i;
        for (i = 0; !flag && i < numHash; ++i){
            flag = (Hash[i] == x)?1:0;
        }
        if (flag){
            numHash-=1;
            i-=1;
            for (; i < numHash; ++i){
                Hash[i] = Hash[i+1];
            }
            end = (Hash + numHash - 1);
            Hash[numHash] = 0;
            return 1;
        }
        return 0;
    }

};

#endif // NODE_H

