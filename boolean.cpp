#include "boolean.h"

using namespace std;

void outputVectorStr(vector<string> vecStr, string space)
{
	/*
	USING:
	Funtion to display a vector type String
	------------------------------------
	INPUT:
	@ Vector(vector<string>) : vector type string need to show
	OUTPUT:
	@ return: NOTHING - but print vector in screen.
	*/
	for (int i = 0; i < vecStr.size(); i++)
	{	
		cout << vecStr[i];
		if (i < vecStr.size()-1)
		{
			cout << space;
		}
	}
	cout << endl;
}

void outputVector2DStr(vector<vector<string> > vecStr2D, string space)
{
	/*
	USING: Funtion to display a vector<string> 2D throughout function "outputVectorStr"
	------------------------------------
	INPUT:
	@ Vector(vector<vector<string>>) : vector 2D need to show
	OUTPUT:
	@ return: NOTHING - but print vector 2D in screen.
	*/
	for (int i = 0; i < vecStr2D.size(); i++)
	{
		outputVectorStr(vecStr2D[i], space);
	}
}

void outputVectorInt(vector<int> vecInt){
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
		if (i < vecInt.size()-1)
		{
			cout << "  ";
		}
	}
	cout << endl;
}

void outputVector2DInt(vector<vector<int> > vecInt2D){
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


string readFromFile(const char *fileName)
{
	/*
	USING: reading boolean expression from file
	------------------------------------
	INPUT:
	@ fileName(char) : link of file
	OUTPUT:
	@ return(string):  expression
	*/

	string roughExp;
	ifstream expFile;

	expFile.open(fileName, ifstream::in);

	if (expFile.is_open())
	{
		expFile >> roughExp;
		cout << "Read file successfully" << endl;
		expFile.close();
	}
	else
		cout << "Can not open file" << endl;

	return roughExp;
}

vector<string> getVars(string roughExp)
{
	/*
	USING: get list variables and sort it in alphabel
	------------------------------------
	INPUT:
	@ roughExpression(string): rough expression 
	OUTPUT:
	@ return(vector<string>):  list variables
	*/
	vector<string> listVar;
	string element;

	for (int i = 0; i < roughExp.length(); i++)
	{
		if (roughExp[i] != '+' and roughExp[i] != '~')
		{
			element.push_back(roughExp[i]);
			// check if any variable is duplicated
			if (find(listVar.begin(), listVar.end(), element) == listVar.end())
			{
				listVar.push_back(element);
			}
			// clear to make sure only 1 character will be pushed back once time 
			element.clear();
		}
	}
	// sort list variale in alphabet
	sort(listVar.begin(), listVar.end());

	return listVar;
}

vector<string> getMonomials(string roughExp)
{
	/*
	USING: split monomial by "+" and save it into vector string
	------------------------------------
	INPUT:
	@ roughExp(string): rough boolean expression 
	OUTPUT:
	@ return(vector<string>)
	*/
	vector<string> monomialsExp;
	string monomial;

	for (int i = 0; i < roughExp.length(); i++)
	{
		if (roughExp[i] != '+')
		{
			monomial.push_back(roughExp[i]);
		}
		else
		{
			monomialsExp.push_back(monomial);
			monomial.clear();
		}
	}
	// add the last monomial
	monomialsExp.push_back(monomial);
	monomial.clear();

	return monomialsExp;
}

int getIndexVar (string area, char key){
	/*
	USING: get index of variable
	------------------------------------
	INPUT:
	@ area(tring): string 
	@ key(char): key needs to find index
	OUTPUT:
	@ return(int): index of key
	*/
	for (int i = 0; i < area.length(); i++)
	{
		if (area[i] == key)
		{
			return i;
		}
	}
	return -1;
}

vector<int> encodeMonomial(string monomial, vector<string> listVar){
	/*
	USING: encode string monomials and convert to int
	0. negative (~)
	1. positive
	2. variable is hidden.
	------------------------------------
	INPUT:
	@ monomial(string): monomial string
	@ listVar(vector<string>) list of variables
	OUTPUT:
	@ return(vector<int>) encoded monomial
	*/
	vector<int> encodedMono;

	// take the variable list as a standard, to identify the value(0-1-2) for each variable
	for (int k = 0; k < listVar.size(); k++)
	{	
		int index = getIndexVar(monomial, listVar[k][0]);
		// found variable
		if (index != -1)
		{
			if (index > 0 and monomial[index-1] == '~')
			{
				encodedMono.push_back(0);
			}else
			{
				encodedMono.push_back(1);
			}
		}
		// not found variables
		else 
		{
			encodedMono.push_back(2);
		}	
	}
	return encodedMono;
}

vector<int> assignValue(string binaryLine)
{
	/*
	USING:
	Assign value 0/1 (type int) for each variable 
	------------------------------------
	INPUT:
	@ line(string): string includes only '0' and '1' 
	@ Var(vector<int>): vector of all variables
	OUTPUT:
	@ return(vector<int>): vector value 0 - 1 
	*/
	vector<int> varAssign;

	for (int i = 0; i < binaryLine.length(); i++)
	{
		if (binaryLine.at(i) == '1')
		{
			varAssign.push_back(1);
		}
		else
		{
			varAssign.push_back(0);
		}
	}
	return varAssign; 
}

vector<vector<int> > generateVar(vector<string> listVar){
	/*
	USING: generate the true table
	------------------------------------
	INPUT:
	@ listVar(vector<string>) list of variables 
	OUTPUT:
	@ return(matrix) true table 
	*/
	vector<vector<int> > table;
	vector<int> varAssign;
	string line;

	for (int i = 0; i < pow(2, listVar.size()); i++)
	{
		// convert i to 8-bit binary number
		bitset<16> binary(i);
		// print the current binary number
		line = binary.to_string().substr(16 - listVar.size(), 16);
		// convert string to int
		varAssign = assignValue(line);
		table.push_back(varAssign);
	}
	return table;
}

int isMatching(vector<int> geneMono, vector<int> encodedMono){
	/*
	USING: 2 monomials are matching, means:
		+ each element is similar.
		+ if it is different: it must different from 2.
	------------------------------------
	INPUT:
	@ geneMono(vector<int>) vector monomial is generated by list variables
	@ encodedMoni(vector<int>) vector monomial is encoded by user input
	OUTPUT:
	@ return(int) 0/1 => match or not match
	*/
	for (int i = 0; i < encodedMono.size(); i++)
	{
		if (encodedMono[i] != geneMono[i] and encodedMono[i] != 2)
		{
			return 0;
		}
	}
	return 1;
}

vector<vector<int> > getMinterm(vector<string> monomialsExp, vector<string> listVar){
	/*
	USING:

	------------------------------------
	INPUT:
	@ 
	OUTPUT:
	@ return
	*/

	vector<vector<int> > matrixMinterm;
	vector<vector<int> > encodedMinterm;
	vector<int> encodedMono;

	vector<vector<int> > table = generateVar(listVar);
	
	// go through each monomials 
	for (int i = 0; i < monomialsExp.size(); i++)
	{	
		encodedMono = encodeMonomial(monomialsExp[i], listVar);

		for (int i = 0; i < table.size(); i++)
		{
			if (isMatching(table[i], encodedMono) == 1)
			{
				if (find(matrixMinterm.begin(), matrixMinterm.end(), table[i]) == matrixMinterm.end())
				{
					matrixMinterm.push_back(table[i]);
				}
			}
		}
		encodedMinterm.push_back(encodedMono);
		encodedMono.clear();
	}
	sort(encodedMinterm.begin(), encodedMinterm.end());
	outputVector2DInt(encodedMinterm);
	sort(matrixMinterm.begin(), matrixMinterm.end());
	return matrixMinterm;
}

int countDifferentBit(vector<int> cell, vector<int> nextCell, int lengthVar){
	/*
	USING: 
	------------------------------------
	INPUT:
	@ 
	OUTPUT:
	@ return
	*/
	int count = 0;
	for (int i = 0; i < lengthVar; i++)
		if (cell[i] != nextCell[i])
			count++;
	return count;
}

vector<int> joinMinterm(vector<int> cell, vector<int> nextCell, int lengthVar){
	/*
	USING: 
	------------------------------------
	INPUT:
	@ 
	OUTPUT:
	@ return
	*/
	vector<int> cellResult;
	for (int i = 0; i < lengthVar; i++)
		if (cell[i] != nextCell[i])
			cellResult.push_back(2);
		else
			cellResult.push_back(cell[i]);
	return cellResult;
}

void markMinterm(vector<int> &cell, int lengthVar){
	/*
	USING: 
	------------------------------------
	INPUT:
	@ 
	OUTPUT:
	@ return
	*/
	if (cell.size() <= lengthVar)
		cell.push_back(-1);
	return;
}

vector<vector<int> > findPrimeImplicant(vector<vector<int> > minterm, vector<vector<int> > &primeCell, int lengthVar)
{
	/*
	USING: 
	------------------------------------
	INPUT:
	@ 
	OUTPUT:
	@ return
	*/
	vector<vector<int> > result;
	for (int i = 0; i < minterm.size() - 1; i++)
	{
		for (int j = i + 1; j < minterm.size(); j++)
		{
			if (countDifferentBit(minterm[i], minterm[j], lengthVar) == 1)
			{
				vector<int> temp = joinMinterm(minterm[i], minterm[j], lengthVar);
				markMinterm(minterm[i], lengthVar);
				markMinterm(minterm[j], lengthVar);
				if (find(result.begin(), result.end(), temp) == result.end())
					result.push_back(temp);
			}
		}
	}
	for (int i = 0; i < minterm.size(); i++)
	{
		if (minterm[i].size() == lengthVar)
			primeCell.push_back(minterm[i]);
	}
	if (!result.empty())
		findPrimeImplicant(result, primeCell, lengthVar);
	sort(primeCell.begin(), primeCell.end());	
	return primeCell;
}

vector<vector<int> > creatCoveredTable(vector<vector<int> > minterm, vector<vector<int> > primeCell){
	/*
	USING: 
	------------------------------------
	INPUT:
	@ 
	OUTPUT:
	@ return
	*/
	vector<vector<int> > table;
	vector<int> line;
	
	for (int k = 0; k < minterm.size(); k++)
	{
		for (int i = 0; i < primeCell.size(); i++)
		{
			if (isMatching(minterm[k], primeCell[i]) == 1)
			{
				line.push_back(1);
			}else
			{
				line.push_back(0);
			}
		}
		table.push_back(line);
		line.clear();
	}
	return table;
}

int countCover(vector<int> line){
	int count = 0;
	for (int i = 0; i < line.size(); i++)
	{
		if(line[i] == 1){
			count++;
		}
	}
	return count;
}

int getIndexCover(vector<int> line){
	for (int i = 0; i < line.size(); i++)
	{
		if(line[i] == 1){
			return i;
		}
	}
	return -1;
}

vector<vector<int> > findPrerequisiteCovered(vector<vector<int> >coverTable, vector<vector<int> > primeCell){
	/*
	USING: 
	------------------------------------
	INPUT:
	@ 
	OUTPUT:
	@ return
	*/
	vector<vector<int> > prerequisiteCovered;
	for (int i = 0; i < coverTable.size(); i++)
	{
		if(countCover(coverTable[i]) == 1){
			int index = getIndexCover(coverTable[i]);
			if ( index != -1)
			{
				prerequisiteCovered.push_back(primeCell[index]);
			}
		}
	}
	sort(prerequisiteCovered.begin(), prerequisiteCovered.end());
	return prerequisiteCovered;
}

vector<vector<int> > findUnPrerequisiteCovered(vector<vector<int> >prereCovers, vector<vector<int> > primeCell){
	vector<vector<int> > unPrereCovers;
	for (int i = 0; i < primeCell.size(); i++)
	{
		if(find(prereCovers.begin(), prereCovers.end(), primeCell[i]) == prereCovers.end()){
			unPrereCovers.push_back(primeCell[i]);
		}
	}
	return unPrereCovers;
}

int isFullyCovered(vector<vector<int> > primeCell, vector<vector<int> > minterm){
	for (int k = 0; k < minterm.size(); k++)
	{
		int found = 0;
		for (int i = 0; i < primeCell.size(); i++)
		{	
			if (isMatching(minterm[k], primeCell[i]) == 1)
			{	
				found = 1;
				// outputVectorInt(primeCell[i]);
				break;

			}
		}
		if (found == 0)
		{
			return 0;
		}
		
	}
	return 1;
}

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

vector<vector<int> > combineCovers(vector<vector<int> >prereCovers, vector<int> subSet, vector<vector<int> > unPrereCovers){
	vector<vector<int> > covers = prereCovers;
	for (int i = 0; i < subSet.size(); i++)
	{ 
		covers.push_back(unPrereCovers.at(subSet[i]-1));
	}
	return covers;
}


void backTrackSet(int u, int n)
{
    if (u == n + 1)
    {
		vector<int> subSet = getSubSet(n);
		set.push_back(subSet);
        return;
    }
    a[u] = 0;
    backTrackSet(u + 1, n);

    a[u] = 1;
    backTrackSet(u + 1, n);
}

vector<vector<int> > listAllCoverCandidates(vector<vector<int> >prereCovers, vector<vector<int> > unPrereCovers, vector<vector<int> > minterm){
	vector<vector<int> > candidates;
	vector<vector<int> > primeCell = prereCovers;
	if (isFullyCovered(prereCovers, minterm) == 1)
	{
		return prereCovers;
	}
	
	for (int i = 0; i < set.size(); i++)
	{
		primeCell = combineCovers(prereCovers, set[i], unPrereCovers);
		
		if (isFullyCovered(primeCell, minterm) == 1){
			
			candidates.push_back(set[i]);
		}
		primeCell.pop_back();
	}
	return candidates;
	
}

vector<string> decodedCovers(vector<vector<int> > candicates, vector<string> listVar){
	vector<string> candidate;

	for (int i = 0; i < candicates.size(); i++)
	{
		for (int j = 0; j < candicates[i].size(); j++)
		{	
			if(candicates[i][j] == 0){
				candidate.push_back("~");
				candidate.push_back(listVar[j]);
			}
			if(candicates[i][j] == 1){
				candidate.push_back(listVar[j]);
			}	
		}
		candidate.push_back(", ");
	}
	candidate.pop_back();
	return candidate;
}

void writeFile(vector<string> candicates)
{
	ofstream myfile;
	myfile.open("output.txt");
	for (int i = 0; i < candicates.size(); i++)
	{
		myfile << candicates[i];
	}
	cout << endl;
	myfile.close();
}