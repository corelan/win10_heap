// LFH_TakeBack2.cpp : Defines the entry point for the console application.
//



// www.corelan.be
//

#include "stdafx.h"
#include "windows.h"
#include<iostream>
#include<vector>

using namespace std;


int main()
{
	HANDLE hChunk;
	HANDLE hvulnChunk;
	HANDLE hDefaultHeap;
	int vulnchunksize;
	int newchunksize;

	vector<HANDLE> arrChunks;

	vulnchunksize = 0x58;

	// LFH should not be active for the bucket of this size yet
	newchunksize = 0x88;

	hDefaultHeap = GetProcessHeap();

	// Phase 1 : allocations
	// ---------------------

	// enable LFH
	for (int i = 0; i < 0x12; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, vulnchunksize);
		arrChunks.push_back(hChunk);
	}

	// create a series of allocations
	// try to increase chances that last allocations end up
	// in a subsegment together with vulnerable object
	for (int i = 0; i < 0x2000; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, vulnchunksize);
		arrChunks.push_back(hChunk);
	}

	// vulnerable chunk
	hvulnChunk = HeapAlloc(hDefaultHeap, 0, vulnchunksize);
	memset(hvulnChunk, 'A', vulnchunksize);
	printf("Vulnerable object of 0x%08x bytes at 0x%p, filled with 'A'\n", vulnchunksize, hvulnChunk);

	// more allocations
	for (int i = 0; i < 0x1000; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, vulnchunksize);
		arrChunks.push_back(hChunk);
	}

	printf("Allocations done. Press return to start free process\n");
	cin.ignore();


	// Phase 2 : free
	// --------------
	// vulnerable object gets freed
	HeapFree(hDefaultHeap, 0, hvulnChunk);
	printf("Vulnerable object at 0x%p was freed\n", hvulnChunk);

	// free the other ones
	// hopefully freeing the entire bucket
	// and releasing pages used in the subsegment
	for (unsigned chunkindex = 0; chunkindex < arrChunks.size(); chunkindex++)
	{
		HeapFree(hDefaultHeap, 0, arrChunks[chunkindex]);
	}

	printf("Free done. Press return to start new allocations (size 0x%08x)\n", newchunksize);
	cin.ignore();

	// Phase 3 : try to take object space back
	// ---------------------------------------

	// activate LFH for new bucket
	// and cause allocations
	// hopefully taking subsegment of different bucket back
	for (int i = 0; i < 0x2000; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, newchunksize);
		memset(hChunk, 'B', newchunksize);
	}

	printf("Allocations done.   Check if 0x%p contains 'B' now\n", hvulnChunk);
	cin.ignore();


	return 0;

}