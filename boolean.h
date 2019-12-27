#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <bitset>


using namespace std;

bool a[100];

vector<vector<int> > set;

void outputVectorInt(vector<int> vecInt);

void outputVector2DInt(vector<vector<int> > vecInt2D);

void outputVectorStr(vector<string> vecStr, string space);

void outputVector2DStr(vector<vector<string> > vecStr2D, string space);

string readFromFile(const char *fileName);

void writeFile(vector<string> candicates);

vector<string> getVars(string roughExp);

vector<string> getMonomial(string roughExp);

int getIndexVar (string area, char key);

vector<int> encodeMonomial(string monomial, vector<string> listVar);

vector<int> assignValue(string binaryLine);

vector<vector<int> > generateVar(vector<string> listVar);

int isMatching(vector<int> geneMono, vector<int> encodedMono);

vector<vector<int> > getMinterm(vector<int> encodedMono, vector<string> listVar);

int countDifferentBit(vector<int> cell, vector<int> nextCell, int lengthVar);

vector<int> joinMinterm(vector<int> cell, vector<int> nextCell, int lengthVar);

void markMinterm(vector<int> &cell, int lengthVar);

vector<vector<int> > findPrimeImplicant(vector<vector<int> > minterm, vector<vector<int> > &primeCell, int lengthVar);

vector<vector<int> > creatCoveredTable(vector<vector<int> > minterm, vector<vector<int> > primeCell);

int countCover(vector<int> line);

int getIndexCover(vector<int> line);

vector<vector<int> > findPrerequisiteCovered(vector<vector<int> >coverTable, vector<vector<int> > primeCell);

vector<vector<int> > findUnPrerequisiteCovered(vector<vector<int> >prereCovers, vector<vector<int> > primeCell);

int isFullyCovered(vector<vector<int> > primeCell, vector<vector<int> > minterm);

vector<int> getSubSet(int n);

void backTrackSet(int u, int n);

vector<vector<int> > combineCovers(vector<vector<int> >prereCovers, vector<int> indexSubSet, vector<vector<int> > unPrereCovers);

vector<vector<int> > listAllCoverCandidates(vector<vector<int> >prereCovers, vector<vector<int> > unPrereCovers, vector<vector<int> > minterm);

vector<string> decodedCovers(vector<vector<int> > candicates, vector<string> listVar);