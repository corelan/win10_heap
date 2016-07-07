// LFH_Alloc3.cpp : Defines the entry point for the console application.
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


	// activate LFH for 0x4000 byte chunks ?

	for (int i = 1; i <= 20; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, 0x4000);
		printf("[%d] Allocated chunk of 0x4000 bytes at 0x%p\n", i, hChunk);
	}

	printf("Press return to continue\n");
	cin.ignore();

	// activate LFH for 0x4008 byte chunks ?

	for (int i = 1; i <= 20; i++)
	{
		hChunk = HeapAlloc(hDefaultHeap, 0, 0x4008);
		printf("[%d] Allocated chunk of 0x4008 bytes at 0x%p\n", i, hChunk);
	}

	printf("Press return to continue\n");
	cin.ignore();


	return 0;

}