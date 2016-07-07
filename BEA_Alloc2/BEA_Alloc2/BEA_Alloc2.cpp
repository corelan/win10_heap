// BEA_Alloc2.cpp : Defines the entry point for the console application.
//
// www.corelan.be
//

#include "stdafx.h"
#include "windows.h"
#include<iostream>


using namespace std;

int main()
{
	HANDLE hChunk;
	HANDLE hDefaultHeap;

	hDefaultHeap = GetProcessHeap();

	printf("Default process heap found at 0x%p\n", hDefaultHeap);
	printf("Press a key to start...\n");
	cin.ignore();

	// cause some allocations
	for (int i = 0; i < 10; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, 0x300);
		printf("Allocated chunk of 0x300 bytes at 0x%p\n", hChunk);
	}


	printf("Press return to continue\n");
	cin.ignore();

	HeapFree(hDefaultHeap,0, hChunk);
	printf("Free chunk at 0x%p\n", hChunk);

	printf("Press return to continue\n");
	cin.ignore();

	// let's see where these allocations will be taken from

	hChunk = HeapAlloc(hDefaultHeap, 0, 0x100);
	printf("Allocated chunk of 0x100 bytes at 0x%p\n", hChunk);

	hChunk = HeapAlloc(hDefaultHeap, 0, 0x100);
	printf("Allocated chunk of 0x100 bytes at 0x%p\n", hChunk);

	printf("Done...\n");
	cin.ignore();

	return 0;

}

