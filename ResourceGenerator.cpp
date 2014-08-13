#include "StdAfx.h"
#include "ResourceGenerator.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <direct.h>
#include <math.h>
#include <time.h>
using namespace std;



ResourceGenerator::ResourceGenerator(char * filename)
{
	string errOpen = "File with resourceGeneratorInfo was not open";
	string issFail = "Error while reading data";
	try{
		ifstream f(filename);
		if (f.fail()) throw errOpen;
		string s;
		getline(f,s);
		getline(f,s);
		istringstream iss(s);
		string addErrorData = ", line 2";
		while (!iss.eof()){
			int x;
			iss >> x;
			if (iss.fail()) throw issFail + addErrorData;
			typesCount.push_back(x);
		}
		iss.clear();
		getline(f,s);
		getline(f,s);
		iss.str(s);
		addErrorData = ", line 4";
		while (!iss.eof()){
			float x;
			iss >> x;
			if (iss.fail()) throw issFail + addErrorData;
			avaliableParts.push_back(x);
		}
		iss.clear();
		getline(f,s);
		getline(f,s);
		iss.str(s);
		addErrorData = ", line 6";
		while (!iss.eof()){
			int x;
			iss >> x;
			if (iss.fail()) throw issFail + addErrorData;
			resourceCount.push_back(x);
		}

		iss.clear();
		getline(f,s);
		getline(f,s);
		iss.str(s);
		addErrorData = ", line 8";
		iss >> minBusyIntervals;
		if (iss.fail()) throw issFail + addErrorData;
		iss >> maxBusyIntervals;
		if (iss.fail()) throw issFail + addErrorData;
		
		/*iss.clear();
		getline(f,s);
		getline(f,s);
		iss.str(s);
		addErrorData = ", line 10";
		iss >> minPerf;
		if (iss.fail()) throw issFail + addErrorData;
		iss >> maxPerf;
		if (iss.fail()) throw issFail + addErrorData;*/

		iss.clear();
		getline(f,s);
		getline(f,s);
		iss.str(s);
		addErrorData = ", line 12";
		iss >> testCount;
		if (iss.fail()) throw issFail + addErrorData;

		iss.clear();
		getline(f,s);
		getline(f,s);
		iss.str(s);
		addErrorData = ", line 14";
		iss >> T;
		if (iss.fail()) throw issFail + addErrorData;

		iss.clear();
		getline(f,s);
		getline(f,s);
		iss.str(s);
		addErrorData = ", line 16";
		iss >> bmin;
		if (iss.fail()) throw issFail + addErrorData;

		iss.clear();
		getline(f,s);
		getline(f,s);
		iss.str(s);
		addErrorData = ", line 18";
		iss >> bmax;
		if (iss.fail()) throw issFail + addErrorData;

		iss.clear();
		getline(f,s);
		getline(f,s);
		iss.str(s);
		addErrorData = ", line 20";
		while (!iss.eof()){
			double x;
			iss >> x;
			if (iss.fail()) throw issFail + addErrorData;
			balance.push_back(x);
		}
		if (iss.fail()) throw issFail + addErrorData;

		iss.clear();
		getline(f,s);
		getline(f,s);
		iss.str(s);
		addErrorData = ", line 22";
		iss >> bcount;
		if (iss.fail()) throw issFail + addErrorData;
	}
	catch (const string msg){
		cout << msg << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
}

void ResourceGenerator::GenerateTestExamples(){
	srand(unsigned(time(NULL)));
	// create directory with test examples
	string folderName = "resourcesTestExamples";
	string mdErr = "Unable to create directory " + folderName;
	string errCreate = "Error while creating file";
	string chDirErr = "Unable to change directory to " + folderName;
	string rmDirErr = "Unable to remove directory " + folderName;
	try {
		if (dirExist(folderName)) {
			int result = chdir(folderName.c_str());
			if (result !=0 )
				throw chDirErr;
			system("del /q *");
			result = chdir("..");
			if (result !=0 )
				throw chDirErr;
			result = _rmdir(folderName.c_str());
			if (result != 0 )
				throw rmDirErr;
		}
		if( _mkdir( folderName.c_str() ) == 0 )
		{
			printf( "Directory %s was successfully created\n", folderName.c_str() );
			chdir(folderName.c_str());
		}
	    else
		  throw mdErr;
	
		vector<int>::iterator typesIt = typesCount.begin();
		// for all types count
		for (; typesIt!=typesCount.end(); typesIt++){
			vector<float>::iterator partIt = avaliableParts.begin();
			// for all avaliableParts count
			for (; partIt!=avaliableParts.end(); partIt++){
				vector<int>::iterator resIt = resourceCount.begin();
				// for all resource count
				for (; resIt!=resourceCount.end(); resIt++){
					// for all test examples
					for (int i = 0; i < testCount; i++){
						// filename: res_c[typesCount]_f[avaliablePart]_p[processorsPerTypeCount]_[testCount]
						string filename = "res_t";
						int types = *typesIt, res = *resIt;
						float part = *partIt;
						filename+=to_string((long long )types) + "_p" + to_string((long double)part) + "_r" +
							to_string((long long )res) +  "_" + to_string((long long )i) + ".resfile";
						ofstream f(filename);						
						if (f.fail()) throw errCreate;

						f << "Processors count = " << res * types<< endl;
						f << "Types count = " << types << endl;
						for (int j = 0; j < types; j++){
							f << "Type " << j+1 << " (" << res <<" processors)" << endl;
							//f << "Performance (GFlops): " << rand()%maxPerf + minPerf << endl;
							for (int k = 0; k < res; k++){
								int diap = rand()%maxBusyIntervals + minBusyIntervals;
								f << "Processor " << k+1 << " " << diap << endl;
								int lengthDiap = 0; vector<pair<int,int>> diaps;
								//cout << (float)T*(1-part) << endl;
								do{
									int diapBegin = 0, diapEnd = 0;
									lengthDiap = 0;
									diaps.clear();
									for (int l = 0; l < diap; l++){
										if (diapBegin > T || diapEnd == T) continue;
										diapBegin = diapEnd + rand()%(T-diapEnd);
										diapEnd = diapBegin + rand()%(T-diapBegin);
										if (diapEnd > T) diapEnd = T;
										lengthDiap += diapEnd - diapBegin;
												
										diaps.push_back(make_pair(diapBegin, diapEnd));
									}
											
								}
								while (lengthDiap >(float)T*(1-part));
								for (int l = 0; l < diap; l++)
									f << diaps[l].first<< "  " << diaps[l].second << endl;
								
							}// typeResCount
						} // types

					}
					
				}
			}
		}
	}
	catch (const string msg){
		cout << msg << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}

}


double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


void ResourceGenerator::GenerateBandwidthFiles(){
	string folderName = "bandwidthTestExamples";
	string mdErr = "Unable to create directory " + folderName;
	string errCreate = "Error while creating file";
	try {
		if (dirExist(folderName)) {
			chdir(folderName.c_str());
			system("del /q *");
			chdir("..");
			_rmdir(folderName.c_str());
		}
		if( _mkdir( folderName.c_str() ) == 0 )
		{
			printf( "Directory %s was successfully created\n", folderName.c_str() );
			chdir(folderName.c_str());
		}
	    else
		  throw mdErr;
		
		string filename;
		
		for (size_t i = 0; i < typesCount.size(); i++){
			int typeCount = typesCount[i];
			filename = "b" + to_string((long long)typeCount) + "_";
			for (size_t j = 0; j < balance.size(); j++){
				string secondname = filename + to_string(static_cast<long double>(static_cast<int>(balance[j]*1000)/1000.0)) + "_";;
				for (int k = 0; k < bcount; k++){
					string realname = secondname + to_string((long long)k+1);
					realname += ".txt";
					ofstream f(realname);
					
					double b = balance[j];
					f << "Types count: " << typeCount << endl;
					f << "Min bandwidth: " << bmin << endl;
					f << "Max bandwidth: " << bmax << endl;
					f << "Koeff value: " << b << endl;
					
					if (typeCount == 1){
						f << 0;
						f.close();
						continue;
					}

					vector <vector<double>> res;
					res.resize(typeCount);
					for (int i = 0; i < typeCount; i++) res[i].resize(typeCount);

					if (b == 1){
						double val = fRand(bmin, bmax);
						for (int i = 0; i < typeCount; i++)
							for (int j = 0; j < typeCount; j++){
								if (i == j) res[i][j] = 0.0;
								else res[i][j] = val;
							}

					}
					else {
						for (int i = 0; i < typeCount; i++){
							for (int j = 0; j < typeCount; j++){
								if (i > j) continue;
								if (i == j) res[i][j] = 0;
								if (i < j) {
									if (b == 0) res[i][j] = res[j][i] = fRand(bmin, bmax);
									// if b is between 0 and 1
									else {
										double first = fRand(bmin, bmax);
										double length = (1 - b)*(bmax - bmin);
										double second = (first + length) < bmax? first + length : bmin + (first + length - bmax);										if (first < second) res[i][j] = res[j][i] = fRand(first, second);
										else {
											double rand1 = fRand(bmin, second),
												rand2 = fRand(first, bmax);
											int choice = rand()%2;
											if (choice) res[i][j] = res[j][i] = rand1;
											else res[i][j] = res[j][i] = rand2;
										}
									}
								}
							}
						}
					}
					

					f << "Matrix of connection speed: " << endl;
					// write to file
					for (int i = 0; i < typeCount; i++){
							for (int j = 0; j < typeCount; j++)
								f << res[i][j] << " ";
							f << endl;
						}
					f.close();
				}
			}
		}
	}
	catch (const string msg){
		cout << msg << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
}


ResourceGenerator::~ResourceGenerator(void)
{
}
