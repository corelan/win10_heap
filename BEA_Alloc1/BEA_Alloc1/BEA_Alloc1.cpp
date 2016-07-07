// BEA_Alloc1.cpp : Defines the entry point for the console application.
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

	// first, cause 2 allocations of 0x300 bytes
	hChunk = HeapAlloc(hDefaultHeap, 0, 0x300);
	printf("Allocated chunk of 0x300 bytes at 0x%p\n", hChunk);
	hChunk = HeapAlloc(hDefaultHeap, 0, 0x300);
	printf("Allocated chunk of 0x300 bytes at 0x%p\n", hChunk);

	printf("Press return to continue\n");
	cin.ignore();


	printf("Done...\n");
	cin.ignore();

	return 0;

}

