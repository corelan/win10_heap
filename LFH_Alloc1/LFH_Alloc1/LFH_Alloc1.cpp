// LFH_Alloc1.cpp : Defines the entry point for the console application.
//
// www.corelan.be
//

#include "stdafx.h"
#include "windows.h"
#include<iostream>


using namespace std;

int main()
{
	HANDLE hChunk, hChunkf1, hChunkf2;
	HANDLE hDefaultHeap;

	hDefaultHeap = GetProcessHeap();

	printf("Default process heap found at 0x%p\n", hDefaultHeap);
	printf("Press a key to start...\n");
	cin.ignore();

	
	// part 1: how many consecutive allocations are needed to trigger LFH ?
	
	for (int i = 1; i <= 30; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, 0x1500);
		printf("[%d] Allocated chunk of 0x1500 bytes at 0x%p\n",i, hChunk);
	}

	printf("Press return to continue\n");
	cin.ignore();


	// part 2: is the trigger influenced by allocations of different bucket sizes ?

	for (int i = 1; i <= 10; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, 0x2100);
		printf("[%d] Allocated chunk of 0x2100 bytes at 0x%p\n",i, hChunk);
	}
	hChunk = HeapAlloc(hDefaultHeap, 0, 0x300);
	printf("Allocated chunk of 0x300 bytes at 0x%p\n", hChunk);
	for (int i = 11; i <= 20; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, 0x2100);
		printf("[%d] Allocated chunk of 0x2100 bytes at 0x%p\n", i, hChunk);
	}

	printf("Press return to continue\n");
	cin.ignore();

	// part 3: is the trigger influenced by frees ?
	hChunkf1 = HeapAlloc(hDefaultHeap, 0, 0x500);
	hChunkf2 = HeapAlloc(hDefaultHeap, 0, 0x500);


	for (int i = 1; i <= 10; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, 0x3000);
		printf("[%d] Allocated chunk of 0x3000 bytes at 0x%p\n", i, hChunk);
	}
	HeapFree(hDefaultHeap, 0, hChunkf1);
	printf("Freed chunk at 0x%p\n", hChunkf1);

	HeapFree(hDefaultHeap, 0, hChunkf2);
	printf("Freed chunk at 0x%p\n", hChunkf2);

	for (int i = 11; i <= 20; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, 0x3000);
		printf("[%d] Allocated chunk of 0x3000 bytes at 0x%p\n", i, hChunk);
	}


	printf("Press return to continue\n");
	cin.ignore();


	// part 4: is the trigger influenced by frees from the same bucket ?
	for (int i = 1; i <= 10; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, 0x800);
		printf("[%d] Allocated chunk of 0x800 bytes at 0x%p\n", i, hChunk);
	}
	HeapFree(hDefaultHeap, 0, hChunk);
	printf("Freed chunk at 0x%p\n", hChunk);
	for (int i = 11; i <= 20; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, 0x800);
		printf("[%d] Allocated chunk of 0x800 bytes at 0x%p\n", i, hChunk);
	}


	printf("Done...\n");
	cin.ignore();

	return 0;

}