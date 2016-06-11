#include <iostream>
#include <vector>
using namespace std;


int main()
{
    int number;
    cin >> number;

    bool temp;
    std::vector<bool> bitsNumber;
    std::vector<bool> vectorSup;
    std::vector<bool>::reverse_iterator it;

    cout<<"numero inicial: "<<endl<< number<<" -> ";

    for (int i = 0; number > 0 ; ++i){
        temp = number & 1;
        bitsNumber.push_back(temp);
        number>>=1;
        cout<<temp<<" - ";
    }
    cout<<endl;

    vectorSup = bitsNumber;

    // encontrando menor
    // flag moveBit
    bool flagBit, flagBitNegative;
    flagBit = 0;
    flagBitNegative = 0;

    for (int i = 0; i < bitsNumber.size() && !flagBit; ++i)
    {
        if(!flagBitNegative)
            flagBitNegative = bitsNumber[i] == 0;
        
        if(bitsNumber[i] && i!=0){
            if (flagBitNegative){
                bitsNumber[i] = 0;
                for (int j = i - 1; j >= 0 && !flagBit; j--)
                {
                    if(!bitsNumber[j]){
                        bitsNumber[j]=1;
                        flagBit = 1;
                    }
                }
            }
        }
    }


    int infNum = 0;
    it = bitsNumber.rbegin();

    for (int i = 0; i < bitsNumber.size(); ++i){
        infNum |= (*it);
        ++it;
        infNum<<=1;
    }
    infNum>>=1;

    cout<<"numero anterior: "<<endl<< infNum<<" -> ";

    for (int i = 0; i < bitsNumber.size(); ++i){
        cout<<bitsNumber[i]<<" - ";
    }
    cout<<endl;



    flagBit = 0;
    flagBitNegative = 0;

    for (int i = 0; i < vectorSup.size() && !flagBit; ++i)
    {
        //Encontrando un 1
        if(!flagBitNegative)
            flagBitNegative = vectorSup[i] == 1;

        if(flagBitNegative && !vectorSup[i]){
                vectorSup[i] = 1;
                for (int j = 0; j < i && !flagBit; j++)
                {
                    if(vectorSup[j]){
                        vectorSup[j]=0;
                        flagBit = 1;
                    }
                }
        }
    }

    if (!flagBit){
        int countBitsOn;
        countBitsOn = 0;
        for (int i = 0; i < vectorSup.size(); ++i){
            if (vectorSup[i]){
                ++countBitsOn;
            }
        }

        countBitsOn--;

        for (int i = 0; i < vectorSup.size(); ++i){
            vectorSup[i] = (countBitsOn > 0)?1:0;
            countBitsOn--;
        }
        vectorSup.push_back(1);
    }


    int supNum;
    supNum = 0;


    it = vectorSup.rbegin();
    for (int i = 0; i < vectorSup.size(); ++i){
        supNum |= (*it);
        supNum <<=1;
        it++;
    }
    supNum >>= 1;

    cout<<"numero posterior: "<<endl<<supNum<<" -> ";

    for (int i = 0; i < vectorSup.size(); ++i){
        cout<<vectorSup[i]<<" - ";
    }
    cout<<endl;
/*
    cout<<endl<<endl;
    for (int i = 0; supNum > 0; ++i){
        temp = supNum & 1;
        bitsNumber.push_back(temp);
        number>>=1;
        cout<<temp<<" - ";
    }
*/
    cout<<endl;


/*
    int flagBitsOn;
    flagBitsOn=0;
    while(flagBitsOn)
*/





    return 0;
}