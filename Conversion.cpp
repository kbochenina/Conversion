// Conversion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include "time.h"
#include "ResourceGenerator.h"

using namespace std;

int main(int argc, char* argv[])
{
	srand(time(NULL));
	ResourceGenerator rg("resourceGeneratorInfo.txt");
	rg.GenerateBandwidthFiles();
	//rg.GenerateTestExamples();
	//system("pause");
	//int T = 43200;
	//// part of consequential code
	//float alpha = -1;
	//string filename;
	//if (argc==1) filename = "n-10_f-0.8_d-0.2_r-0.2_c-0_j-1.0";
	//else if (argc==2) filename=argv[1];
	//
	//string folderName = "workflowsTestExamples";
	//string mdErr = "Unable to create directory " + folderName;
	//string openErr = "No avaliable file with dag description " + filename;
	//
	//try {
	//	ifstream daggen(filename);
	//	if (!daggen) throw openErr;
	//	if (!dirExist(folderName)) {
	//		if( _mkdir( folderName.c_str() ) == 0 )
	//		{
	//			printf( "Directory %s was successfully created\n", folderName.c_str() );
	//			chdir(folderName.c_str());
	//		}
	//		else
	//			throw mdErr;
	//	}
	//	else chdir(folderName.c_str());
	//	
	//	vector <int> realNodeNumbers; // for each COMPUTATIONAL node - its number (with TRANSFER nodes) - from 1
	//	// filling realNodeNumbers vector
	//	string str;
	//	int compNodeIndex = 1;
	//	while (str.find("COMPUTATION")==-1) {
	//		getline(daggen, str);
	//	}
	//	realNodeNumbers.push_back(compNodeIndex);
	//	while (str.find("END")==-1){
	//		getline(daggen, str);
	//		compNodeIndex++;
	//		if (str.find("COMPUTATION")!=-1)
	//			realNodeNumbers.push_back(compNodeIndex);
	//	}

	//	daggen.seekg(0);

	//	// also with TRANSFER NODES
	//	vector <vector<int>> fullRelatedNumbers; // package1: (realNumber1, realNumber2), package2: (realNumber1, realNumber2), ...
	//	int maxRealNodeNum = 0;
	//	daggen.clear();
	//	string trim;
	//	
	//	// matrix of dependencies between packages
	//	vector<vector<int>> connectivityMatrix;
	//	
	//	size_t found = filename.find_last_of("/");
	//	if (found!=string::npos) filename.erase(0,found+1);
	//	// cout << filename << endl;
	//	// result file has the same name
	//	ofstream fileW(filename);

	//	fileW << "Workflows count = 1" << endl;
	//	daggen.seekg(0);
	//	for (int i = 0; i <= 3; i++) 
	//	getline(daggen,str);
	//	trim = "# ";
	//	str.erase(0,trim.size());
	//	int packagesCount = atoi(str.c_str());
	//	fileW << "Workflow 1 (" << packagesCount << " packages)" << endl;
	//	
	//	connectivityMatrix.resize(packagesCount);
	//		for (int i = 0; i < packagesCount; i++) 
	//			for (int j = 0; j < packagesCount; j++)
	//				connectivityMatrix[i].push_back(0);
	//	
	//	daggen.seekg(0);
	//		for (int i = 0; i <= 25; i++) 
	//	getline(daggen, str);
	//	trim = "NODE_COUNT ";
	//	str.erase(0, trim.size());
	//	maxRealNodeNum = atoi(str.c_str());
	//	maxRealNodeNum--;
	//	
	//	int currentIndex = 0;
	//	for (int j = 0; j < packagesCount; j++){
	//			
	//		if (j == 0) currentIndex = 27;
	//		daggen.seekg(0);
	//		for (int i = 0; i <= currentIndex; i++) 
	//			getline(daggen, str);
	//		
	//		// seeking for next line with computation task
	//		if (j == 0) {
	//			currentIndex++;
	//		}
	//		else{
	//			currentIndex++;
	//			while (str.find("COMPUTATION")==-1) {
	//				getline(daggen, str);
	//				currentIndex++;
	//			}
	//			
	//		}
	//			
	//		trim = "NODE ";
	//		str.erase(0, trim.size());
	//		istringstream iss(str);
	//		int nodeNum; string nodeType;
	//		iss >> nodeNum;
	//					
	//		//realNodeNumbers.push_back(nodeNum);

	//		vector <int> relatedNumbers;
	//		vector <pair<int, double>> transfer; // (2, 430.0), (4, 410.0) - (packageRecievet, dataAmount(Mb))
	//		int currentRelatedNum; char space;
	//		do{
	//			iss >> currentRelatedNum;
	//			if (currentRelatedNum!=maxRealNodeNum) relatedNumbers.push_back(currentRelatedNum);
	//			iss >> space;
	//		}
	//		while (space==',');
	//		iss >> nodeType;
	//		long int gflop;
	//		iss >> gflop;
	//		iss >> alpha;	
	//		vector <int> realRelated;
	//		// find related packages
	//		
	//		int relatedCount = relatedNumbers.size();
	//		while (relatedCount){
	//			getline(daggen, str);
	//			iss.clear();
	//			iss.str(str);
	//			if (str.find("COMPUTATION")!=-1) continue;
	//			else {
	//				iss >> nodeType;
	//				iss >> nodeNum;
	//				int relNum;
	//				iss >> relNum;
	//				vector<int>::iterator it = find(realNodeNumbers.begin(), realNodeNumbers.end(), relNum);
	//				int reciever = distance(realNodeNumbers.begin(), it) + 1;
	//				string add;
	//				iss >> add;
	//				double amount;
	//				iss >> amount;
	//				transfer.push_back(make_pair(reciever, amount));
	//				if (find(relatedNumbers.begin(), relatedNumbers.end(), nodeNum)!=relatedNumbers.end()){
	//					relatedCount--;
	//					realRelated.push_back(relNum);
	//				}
	//			}
	//		}
	//		fullRelatedNumbers.push_back(realRelated);
	//		



	//		fileW << "Package " << j+1 << endl;
	//		fileW << "Alpha: " << alpha << endl << "Resources types: -1" << endl << "Processors count: 1, 2, 4";
	//		fileW << endl << "GFlop: " << gflop << endl;
	//		fileW << "Transfer: ";
	//		for (int i = 0; i < transfer.size(); i++){
	//			fileW << "P" << transfer[i].first << " " << transfer[i].second << "Mb" << " ";
	//		}
	//		fileW << endl;
	//		
	//	}
	//	fileW << "Connectivity matrix: " << endl;
	//	for (int j = 0; j < packagesCount; j++){
	//			for (int k = 0; k < fullRelatedNumbers[j].size(); k++){
	//				int currNumber = fullRelatedNumbers[j][k];
	//				vector <int>::iterator it = find(realNodeNumbers.begin(), realNodeNumbers.end(), currNumber);
	//				int finNumber = distance(realNodeNumbers.begin(), it);
	//				connectivityMatrix[j][finNumber] = 1;
	//		}
	//	}
	//	for (int j = 0; j < packagesCount; j++){
	//		for (int k = 0; k < packagesCount; k++)
	//			fileW << connectivityMatrix[j][k] << " ";
	//		fileW << endl;
	//	}
	//	
	//	fileW.close();
	//}
	//catch (const string msg){
	//	cout << msg << endl;
	//	//system("pause");
	//	exit(EXIT_FAILURE);
	//}
	//
	//
	//if (argc > 2) cout << "Too much command line arguments,try Conversion filename\n";
	system("pause");
	return 0;
}

