// BEA_Alloc3.cpp : Defines the entry point for the console application.
//
// www.corelan.be
//

#include "stdafx.h"
#include "windows.h"
#include<iostream>


using namespace std;

int main()
{
	HANDLE hChunk, hChunk58;
	HANDLE hDefaultHeap;

	hDefaultHeap = GetProcessHeap();

	printf("Default process heap found at 0x%p\n", hDefaultHeap);
	printf("Press a key to start...\n");
	cin.ignore();

	// try to exhaust freelist for 0x58 and 0x100
	for (int i = 0; i < 10; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, 0x58);
		printf("Allocated chunk of 0x58 bytes at 0x%p\n", hChunk);
		hChunk = HeapAlloc(hDefaultHeap, 0, 0x100);
		printf("Allocated chunk of 0x100 bytes at 0x%p\n", hChunk);
	}


	printf("Press return to continue\n");
	cin.ignore();
	

	// hopefully these 3 chunks will sit next to each other
	hChunk = HeapAlloc(hDefaultHeap, 0, 0x100);
	printf("Allocated chunk of 0x100 bytes at 0x%p\n", hChunk);
	hChunk58 = HeapAlloc(hDefaultHeap, 0, 0x58);
	memset(hChunk58, 'A', 0x58);
	printf("Allocated chunk of 0x58 bytes at 0x%p, filled with 'A'\n", hChunk58);
	hChunk = HeapAlloc(hDefaultHeap, 0, 0x100);
	printf("Allocated chunk of 0x100 bytes at 0x%p\n", hChunk);

	printf("Press return to continue\n");
	cin.ignore();

	// now free the 0x58 byte chunk
	HeapFree(hDefaultHeap, 0, hChunk58);
	printf("Free chunk of 0x58 bytes at 0x%p\n", hChunk58);

	// and cause a new allocation, hopefully taking its place
	hChunk58 = HeapAlloc(hDefaultHeap, 0, 0x58);
	memset(hChunk58, 'B', 0x58);
	printf("Allocated chunk of 0x58 bytes at 0x%p, filled with 'B'\n", hChunk58);

	printf("Done...\n");
	cin.ignore();

	return 0;

}

