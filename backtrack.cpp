#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void outputVectorInt(vector<int> vecInt)
{
    /*
	USING:
	Funtion to display a vector type Interger
	------------------------------------
	INPUT:
	@ Vector(vector<int>) : vector type int need to show
	OUTPUT:
	@ return: NOTHING - but print vector in screen.
	*/
    for (int i = 0; i < vecInt.size(); i++)
    {
        cout << vecInt[i];
        if (i < vecInt.size() - 1)
        {
            cout << "  ";
        }
    }
    cout << endl;
}
void outputVector2DInt(vector<vector<int> > vecInt2D)
{
    /*
	USING: Funtion to display a vector<int> 2D throughout function "outputVectorInt"
	------------------------------------
	INPUT:
	@ Vector(vector<vector<int>>) : vector 2D need to show
	OUTPUT:
	@ return: NOTHING - but print vector 2D in screen.
	*/
    for (int i = 0; i < vecInt2D.size(); i++)
    {
        outputVectorInt(vecInt2D[i]);
    }
}
bool a[100];
vector<vector<int> > result;

vector<int> getSubSet(int n)
{
    vector<int> subSet;
    for (int i = 1; i <= n; i++)
    {
        if (a[i])
        {
            subSet.push_back(i);
        }
    }
    return subSet;
}

void backtrack(int u, int n, vector<vector<int> > result)
{
    if (u == n + 1)
    {
        result.push_back(getSubSet(n));
        outputVector2DInt(result);
        return;
    }
    a[u] = 0;
    backtrack(u + 1, n, result);

    a[u] = 1;
    backtrack(u + 1, n, result);
}

main()
{   

    int n = 3;
    backtrack(1, n, result);
    
}
