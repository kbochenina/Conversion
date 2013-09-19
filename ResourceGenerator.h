#pragma once
#include <vector>
#include "DirExist.h"

class ResourceGenerator
{
	// possible values of types count
	std::vector <int> typesCount;
	// possible parts of avaliable time
	std::vector <float> avaliableParts;
	// possible values of resource count for one type
	std::vector <int> resourceCount;
	// possible values for cores count
	std::vector <int> coresCount;
	// min and max count of busy intervals
	int minBusyIntervals, maxBusyIntervals;
	// min and max performance in GFlops
	int minPerf, maxPerf;
	// count of test examples for one variant
	int testCount;
	// second count
	int T;
public:
	ResourceGenerator(char * fileName);
	void GenerateTestExamples();
	~ResourceGenerator(void);
};

