// LFH_Alloc2.cpp : Defines the entry point for the console application.
//

// www.corelan.be
//

#include "stdafx.h"
#include "windows.h"
#include<iostream>


using namespace std;

int main()
{
	HANDLE hChunk, hChunkf, hChunkn;
	HANDLE hDefaultHeap;

	hDefaultHeap = GetProcessHeap();

	printf("Default process heap found at 0x%p\n", hDefaultHeap);
	printf("Press a key to start...\n");
	cin.ignore();


	// activate LFH for 0x500 byte chunks

	for (int i = 1; i <= 20; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, 0x500);
		printf("[%d] Allocated chunk of 0x500 bytes at 0x%p\n", i, hChunk);
	}

	printf("Press return to continue\n");
	cin.ignore();

	HeapFree(hDefaultHeap, 0, hChunk);
	printf("Freed chunk at 0x%p\n", hChunk);
	hChunkf = hChunk;

	printf("Press return to continue\n");
	cin.ignore();
	
	hChunk = HeapAlloc(hDefaultHeap, 0, 0x500);
	printf("Allocated chunk of 0x500 bytes at 0x%p\n", hChunk);


	printf("Press return to continue\n");
	cin.ignore();

	for (int i = 1; i <= 20; i++)
	{
		hChunkn = HeapAlloc(hDefaultHeap, 0, 0x500);
		printf("[%d] Allocated chunk of 0x500 bytes at 0x%p\n", i, hChunkn);
		if (hChunkf == hChunkn)
		{
			printf(" --- got it back --- \n");
		}
	}


	printf("Press return to continue\n");
	cin.ignore();
	

	return 0;

}