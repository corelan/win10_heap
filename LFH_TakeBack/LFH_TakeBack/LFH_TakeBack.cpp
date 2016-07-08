// LFH_TakeBack.cpp : Defines the entry point for the console application.
//


// www.corelan.be
//

#include "stdafx.h"
#include "windows.h"
#include<iostream>
#include<vector>
#include<map>

using namespace std;

std::map<int, int> mapAllocData;

void updateMap(int nrtimes)
{
	int curtimes;
	map<int, int>::iterator it = mapAllocData.find(nrtimes);
	if (it != mapAllocData.end())
	{
		// key exists, so increment its value
		curtimes = (it->second) + 1;
		mapAllocData[nrtimes] = curtimes;
	}
	else
	{
		mapAllocData[nrtimes] = 1;
	}
}

void printMap()
{
	printf("\n");
	printf("Nr allocs needed   |  Nr times\n");
	printf("-------------------------------\n");
	for (std::map<int, int>::iterator it = mapAllocData.begin(); it != mapAllocData.end(); ++it)
	{
		printf("       %d               %d \n", it->first, it->second);
	}
	printf("\n");
}


int main()
{
	HANDLE hChunk;
	HANDLE hChunkFreed;
	HANDLE hDefaultHeap;

	vector<HANDLE> arrChunks;


	double takenbacksum;
	double nrruns;
	double mintimes;
	double maxtimes;
	int nrtries;
	int nrnotfound;
	int maxruns;
	bool wasfound;

	takenbacksum = 0;
	nrruns = 0;
	nrnotfound = 0;
	mintimes = 0;
	maxtimes = 0;

	hDefaultHeap = GetProcessHeap();

	maxruns = 100;

	for (int nrtimes = 0; nrtimes < maxruns; nrtimes++)
	{
		printf("\nStarting run %d of %d\n", nrtimes + 1, maxruns);
		// free chunks first
		printf("1. Free allocations...\n");
		for (unsigned chunkindex = 0; chunkindex < arrChunks.size(); chunkindex++)
		{
			HeapFree(hDefaultHeap, 0, arrChunks[chunkindex]);
		}
		arrChunks.clear();
		printf("2. Cause new allocations...\n");
		for (int chunksize = 8; chunksize < 0x4000; chunksize += 8)
		{
			// activate LFH for this size (only in first run)
			if (nrtimes == 0)
			{
				for (int y = 0; y < 20; y++)
				{
					hChunk = HeapAlloc(hDefaultHeap, 0, chunksize);
					arrChunks.push_back(hChunk);
				}
			}
			// cause an allocation and free it again
			hChunkFreed = HeapAlloc(hDefaultHeap, 0, chunksize);
			HeapFree(hDefaultHeap, 0, hChunkFreed);
			wasfound = false;
			nrtries = 0;
			// now try to get it back
			for (int z = 1; z < 2000; z++)
			{
				hChunk = HeapAlloc(hDefaultHeap, 0, chunksize);
				arrChunks.push_back(hChunk);
				if (hChunk == hChunkFreed)
				{
					takenbacksum = takenbacksum + z;
					nrruns = nrruns + 1;
					nrtries = z;
					if (mintimes == 0)
					{
						mintimes = z;
					}
					if (maxtimes == 0)
					{
						maxtimes = z;
					}
					if (z < mintimes)
					{
						mintimes = z;
					}
					if (z > maxtimes)
					{
						maxtimes = z;
					}
					wasfound = true;
					updateMap(z);
					break;
				}
			}
			if (!wasfound)
			{
				nrnotfound += 1;
			}
			/*
			if (wasfound)
			{
				printf("%d/%d - Chunksize 0x%08x : object at 0x%p taken back after %d tries\n", nrtimes+1, maxruns, chunksize, hChunkFreed, nrtries);
				printf("  Average so far: %f\n", (takenbacksum / nrruns));
				printf("  Min: %f, max: %f\n", mintimes, maxtimes);
			}
			else
			{
				nrnotfound += 1;
			}
			*/
		}
		printf("\n  Number of times object not taken back: %d\n", nrnotfound);
		printf("  GlobalAverage so far: %f\n", (takenbacksum / nrruns));
		printf("  Min: %f, max: %f\n", mintimes, maxtimes);
	}

	printMap();

	return 0;

}