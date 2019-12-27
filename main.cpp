/*
* THUC HANH TOAN ROI RAC : DAI SO BOOLEAN
* DEADLINE: 23h59 Fri, 10, May, 2019
* Compile and execute by terminal: 
	+ Using: g++ [file .cpp] [option] [executed file]
	+ After that, executes this file.
	Example: 
		+ Run in terminal: g++ main.cpp -o run.exe
		+ Execute file run.exe: ./run.exe
* Note:
	1. Find completely minterms.
	2. Find completely prime implicants.
	3. Find completely Prerequisite Covers. (mandotary prime implicant)
	4. Find completely mintersm are not covered by prerequisite covers.

	
*/

#include "boolean.h"
#include "boolean.cpp"

using namespace std;

int main() {
	string roughExp = readFromFile("input.txt");
	cout << "Boolean Expression: " << roughExp << endl;

	vector<string> listVar = getVars(roughExp);
	cout << "Variables: (Sorted by Alphabet)  ";
	outputVectorStr(listVar, " - ");

	vector<string> monomialsExp = getMonomials(roughExp);
	cout << "Monomials: ";
	outputVectorStr(monomialsExp, " - ");

	cout << "Encoded Monomials: " << endl;
	vector<vector<int> > matrixMinterm = getMinterm(monomialsExp, listVar);

	cout << "Minterm Table: " << endl;
	outputVector2DInt(matrixMinterm);
	
	vector<vector<int> > bigCellule;
	cout << "Prime Implicant: " << endl;
	findPrimeImplicant(matrixMinterm, bigCellule, listVar.size());
	outputVector2DInt(bigCellule);
	vector<string> primeImplicant = decodedCovers(bigCellule, listVar);
	writeFile(primeImplicant);

	cout << "Prerequisite/Mandatory Covers: " << endl;
	vector<vector<int> > table = creatCoveredTable(matrixMinterm, bigCellule);
	vector<vector<int> > prereCovers = findPrerequisiteCovered(table, bigCellule);
	outputVector2DInt(prereCovers);

	cout << "Un Prerequisite/Mandatory Covers: " << endl;
	vector<vector<int> > unPrereCovers = findUnPrerequisiteCovered(prereCovers, bigCellule);
	outputVector2DInt(unPrereCovers);

    backTrackSet(1, unPrereCovers.size());

	cout << "CANDICATES:" << endl;
	vector<vector<int> > candidates = listAllCoverCandidates(prereCovers,unPrereCovers, matrixMinterm);
	outputVector2DInt(candidates);


	return 0;
}
// A~B+A~D+~AB~C~D+A~D+ABCD
// ~A~B+~AB~C+AB~C+ABC
// ~AB~C~D+A~B~C~D+A~B~CD+A~BC~D+A~BCD+AB~C~D+ABCD+ABC~D
// AC+A~B+A~D+B~C~D+~A~BCD+~AB~CD
// AC+A~B+A~D+B~C~D+~AB~CD+~A~BCD
// XYZ+~X~Z+XY~Z+~X~YZ+~XY~Z
// XZ+X~Z~T+Y~ZT+~X~Y~Z~T+~X~YZ
// AC+A~C~D+B~CD+~A~B~C~D+~A~BC