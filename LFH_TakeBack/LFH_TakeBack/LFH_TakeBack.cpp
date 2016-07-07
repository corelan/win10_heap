// LFH_TakeBack.cpp : Defines the entry point for the console application.
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
	HANDLE hChunkFreed;
	HANDLE hDefaultHeap;

	double takenbacksum;
	double nrruns;
	double mintimes;
	double maxtimes;
	int nrtries;
	int nrnotfound;
	bool wasfound;

	takenbacksum = 0;
	nrruns = 0;
	nrnotfound = 0;
	mintimes = 0;
	maxtimes = 0;

	hDefaultHeap = GetProcessHeap();

	for (int nrtimes = 0; nrtimes < 2; nrtimes++)
	{
		for (int chunksize = 8; chunksize < 0x4000; chunksize += 8)
		{
			// activate LFH for this size (only in first run)
			if (nrtimes == 0)
			{
				for (int y = 0; y < 20; y++)
				{
					HeapAlloc(hDefaultHeap, 0, chunksize);
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
					break;
				}
			}
			if (wasfound)
			{
				printf("Chunksize 0x%08x : object at 0x%p taken back after %d tries\n", chunksize, hChunkFreed, nrtries);
				printf("  Average so far: %f\n", (takenbacksum / nrruns));
				printf("  Min: %f, max: %f\n", mintimes, maxtimes);
			}
			else
			{
				nrnotfound += 1;
			}
		}
		printf("Number of times object not taken back: %d\n", nrnotfound);
	}

	printf("Done, press return to quit\n");
	cin.ignore();


	return 0;

}